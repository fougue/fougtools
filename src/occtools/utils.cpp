/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language, the Qt and Open Cascade toolkits.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "occtools/utils.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepLProp_SLProps.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <IFSelect_ReturnStatus.hxx> // For status reading
#include <IGESControl_Controller.hxx>
#include <IGESControl_Reader.hxx> // For IGES files reading
#include <IGESControl_Writer.hxx>
#include <Interface_Static.hxx>
#include <Message_ProgressIndicator.hxx>
#include <Poly_Triangle.hxx>
#include <STEPControl_Reader.hxx> // For STEP files reading
#include <STEPControl_Writer.hxx>
#include <SelectMgr_SelectionManager.hxx>
#include <StlAPI_Writer.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopoDS.hxx>
#include <Transfer_TransientProcess.hxx>
#include <XSControl_WorkSession.hxx>
#include <cassert>
#include <gp_Trsf.hxx>

#include <Transfer_FinderProcess.hxx>

namespace {

const double kMaxRgbComponent = 255.;

template<typename _READER_>
TopoDS_Shape shapeFromFile(
    const QString& fileName, Handle_Message_ProgressIndicator indicator)
{
  TopoDS_Shape result;

  if (!indicator.IsNull())
    indicator->NewScope(30, "Loading file");
  _READER_ reader;
  const int status =
      reader.ReadFile(const_cast<Standard_CString>(qPrintable(fileName)));
  if (!indicator.IsNull())
    indicator->EndScope();
  if (status == IFSelect_RetDone) {
    if (!indicator.IsNull()) {
      reader.WS()->MapReader()->SetProgress(indicator);
      indicator->NewScope(70, "Translating file");
    }
    reader.NbRootsForTransfer();
    reader.TransferRoots();
    result = reader.OneShape();
    if (!indicator.IsNull()) {
      indicator->EndScope();
      reader.WS()->MapReader()->SetProgress(0);
    }
  }
  return result;
}
} // Anonymous namespace


namespace occ {

// --- Geometry

gp_Pnt geomCurveD0(const Handle_Geom_Curve& curve, double u)
{
  gp_Pnt pnt;
  curve->D0(u, pnt);
  return pnt;
}

double curveLength(const Handle_Geom_Curve& curve)
{
  try {
    GeomAdaptor_Curve adaptor(curve);
    return GCPnts_AbscissaPoint::Length(adaptor);
  }
  catch(...) {
    return 0.;
  }
}

double curveLengthBetweenParams(const Handle_Geom_Curve& curve,
                                double firstU, double lastU)
{
  try {
    GeomAdaptor_Curve adaptor(curve);
    return GCPnts_AbscissaPoint::Length(adaptor, firstU, lastU);
  }
  catch(...) {
    return 0.;
  }
}

gp_Vec normalToFaceAtUV(const TopoDS_Face& face, double u, double v)
{
  BRepLProp_SLProps localSurfaceProps(1, 1e-6);
  localSurfaceProps.SetSurface(BRepAdaptor_Surface(face));
  localSurfaceProps.SetParameters(u, v);
  if (localSurfaceProps.IsNormalDefined()) {
    const gp_Dir& nc = localSurfaceProps.Normal();
    if (face.Orientation() == TopAbs_REVERSED)
      return gp_Vec(-nc.X(), -nc.Y(), -nc.Z());
    else
      return gp_Vec(nc.X(), nc.Y(), nc.Z());
  }
  return gp_Vec(0., 0., 1.);
  //return normalToSurfaceAtUV(BRep_Tool::Surface(face), u, v);
}

gp_Vec normalToSurfaceAtUV(const Handle_Geom_Surface& surface,
                           double u, double v)
{
  gp_Pnt point;
  gp_Vec d1u, d1v;
  surface->D1(u, v, point, d1u, d1v);
  return d1u ^ d1v;
}

// --- Color conversion

//! Conversion of the Quantity_Color \p c to a QColor
QColor toQtColor(const Quantity_Color& c)
{
  return QColor(c.Red() * kMaxRgbComponent,
                c.Green() * kMaxRgbComponent,
                c.Blue() * kMaxRgbComponent);
}

//! Conversion of the Quantity_NameOfColor \p c to a QColor
QColor toQtColor(const Quantity_NameOfColor c)
{
  Quantity_Color qc(c);
  return toQtColor(qc);
}

//! Conversion of the QColor \p c to a Quantity_Color
Quantity_Color toOccColor(const QColor& c)
{
  return Quantity_Color(c.red() / kMaxRgbComponent,
                        c.green() / kMaxRgbComponent,
                        c.blue() / kMaxRgbComponent,
                        Quantity_TOC_RGB);
}

//! Conversion of the QColor object \p c to a Quantity_NameOfColor
Quantity_NameOfColor toNamedOccColor(const QColor& c)
{
  return toOccColor(c).Name();
}

// --- Type conversion

//! Conversion of the Qt string \p str to an OCC CString
Standard_CString toOccCstring(const QString& str)
{
  return const_cast<char*>(qPrintable(str));
}

// --- Import / export

/*! \brief Topologic shape read from a file (OCC's internal BREP format)
   *  \param fileName Path to the file to read
   *  \param indicator Indicator to notify the loading progress
   *  \return The part as a whole topologic shape
   */
TopoDS_Shape shapeFromBrepFile(
    const QString& fileName, Handle_Message_ProgressIndicator indicator)
{
  TopoDS_Shape result;
  BRep_Builder brepBuilder;
  BRepTools::Read(result, fileName.toAscii().data(), brepBuilder, indicator);
  return result;
}

/*! \brief Topologic shape read from a file (IGES format)
   *  \param fileName Path to the file to read
   *  \param indicator Indicator to notify the loading progress
   *  \return The part as a whole topologic shape
   */
TopoDS_Shape shapeFromIgesFile(
    const QString& fileName, Handle_Message_ProgressIndicator indicator)
{
  return ::shapeFromFile<IGESControl_Reader>(fileName, indicator);
}

/*! \brief Topologic shape read from a file (STEP format)
   *  \param fileName Path to the file to read
   *  \param indicator Indicator to notify the loading progress
   *  \return The part as a whole topologic shape
   */
TopoDS_Shape shapeFromStepFile(
    const QString& fileName, Handle_Message_ProgressIndicator indicator)
{
  return ::shapeFromFile<STEPControl_Reader>(fileName, indicator);
}

/*! \brief Write a topologic shape to a file (OCC's internal BREP format)
   *  \param shape Topologic shape to write
   *  \param fileName Path to the file to write
   *  \param indicator Indicator to notify the writing progress
   */
void writeShapeToBrepFile(const TopoDS_Shape& shape,
                          const QString& fileName,
                          Handle_Message_ProgressIndicator indicator)
{
  BRepTools::Write(shape, fileName.toAscii().data(), indicator);
}

/*! \brief Write a topologic shape to a file (IGES format)
   *  \param shape Topologic shape to write
   *  \param fileName Path to the file to write
   *  \param indicator Indicator to notify the writing progress
   */
void writeShapeToIgesFile(const TopoDS_Shape& shape,
                          const QString& fileName,
                          Handle_Message_ProgressIndicator indicator)
{
  IGESControl_Controller::Init();
  IGESControl_Writer writer(Interface_Static::CVal("XSTEP.iges.unit"),
                            Interface_Static::IVal("XSTEP.iges.writebrep.mode"));
  if (!indicator.IsNull())
    writer.TransferProcess()->SetProgress(indicator);
  writer.AddShape(shape);
  writer.ComputeModel();
  writer.Write(fileName.toAscii().data());
  writer.TransferProcess()->SetProgress(0);
}

/*! \brief Write a topologic shape to a file (STEP format)
   *  \param shape Topologic shape to write
   *  \param fileName Path to the file to write
   *  \param indicator Indicator to notify the writing progress
   */
void writeShapeToStepFile(const TopoDS_Shape& shape,
                          const QString& fileName,
                          Handle_Message_ProgressIndicator indicator)
{
  IFSelect_ReturnStatus status;
  STEPControl_Writer writer;
  if (!indicator.IsNull())
    writer.WS()->MapReader()->SetProgress(indicator);
  status = writer.Transfer(shape, STEPControl_AsIs);
  status = writer.Write(fileName.toAscii().data());
  writer.WS()->MapReader()->SetProgress(0);
}

/*! \brief Write a topologic shape to a file (ASCII STL format)
   *  \param shape Topologic shape to write
   *  \param fileName Path to the file to write
   */
void writeShapeToAsciiStlFile(const TopoDS_Shape& shape,
                              const QString& fileName)
{
  StlAPI_Writer writer;
  writer.ASCIIMode() = Standard_True;
  writer.Write(shape, fileName.toAscii().data());
}

/*! \brief Write a topologic shape to a file (binary STL format)
   *  \param shape Topologic shape to write
   *  \param fileName Path to the file to write
   */
void writeShapeToBinaryStlFile(const TopoDS_Shape& shape,
                               const QString& fileName)
{
  StlAPI_Writer writer;
  writer.ASCIIMode() = Standard_False;
  writer.Write(shape, fileName.toAscii().data());
}

// --- Visualization

void eraseObjectFromContext(Handle_AIS_InteractiveObject object,
                            Handle_AIS_InteractiveContext context)
{
  if (!object.IsNull()) {
    context->Erase(object, false);
    context->Remove(object, false);
    context->Clear(object, false); // Remove() can be used too.
    context->SelectionManager()->Remove(object);
    while (!object.IsNull())
      object.Nullify();
  }
}

// --- Triangulation tools

/*! \brief Non-normalized vector to a triangle
   *  \param nodes
   *         Vertices of the triangulation that \p triangle belongs to
   *  \param triangle
   *         Triangle whose normal has to be computed
   *  \param ori
   *         Orientation of the triangle (generally inherited from the
   *         triangulated face)
   */
gp_Vec triangleNormal(const TColgp_Array1OfPnt& nodes,
                      const Poly_Triangle& triangle,
                      TopAbs_Orientation ori)
{
  int n1, n2, n3;
  if (ori == TopAbs_REVERSED)
    triangle.Get(n1, n3, n2);
  else
    triangle.Get(n1, n2, n3);
  assert(nodes.Lower() <= n1 && n1 <= nodes.Upper());
  assert(nodes.Lower() <= n2 && n2 <= nodes.Upper());
  assert(nodes.Lower() <= n3 && n3 <= nodes.Upper());
  const gp_Vec v1(nodes(n1), nodes(n2)); // V1=(P1,P2)
  const gp_Vec v2(nodes(n2), nodes(n3)); // V2=(P2,P3)
  const gp_Vec v3(nodes(n3), nodes(n1)); // V3=(P3,P1)

  if ((v1.SquareMagnitude() > 1.e-10) &&
      (v2.SquareMagnitude() > 1.e-10) &&
      (v3.SquareMagnitude() > 1.e-10))
    return v1.Crossed(v2);
  return v1;
}

//
// --- Conversion functors
//

const TopoDS_Edge& topo_edge_convert::operator()(const TopoDS_Shape& shape) const
{
  return TopoDS::Edge(shape);
}

const TopoDS_Face& topo_face_convert::operator()(const TopoDS_Shape& shape) const
{
  return TopoDS::Face(shape);
}

//
// --- AIS functors
//

/*! \struct ais_object_unary_function
   *  \brief
   */
ais_object_unary_function::
ais_object_unary_function(const Handle_AIS_InteractiveContext& context) :
  _context(context)
{ }

/*! \struct ais_object_location_set
   *  \brief
   */
ais_object_location_set::
ais_object_location_set(const Handle_AIS_InteractiveContext& context,
                        const gp_Trsf& trsf) :
  _context(context),
  _trsf(trsf)
{ }

void ais_object_location_set::operator()(first_argument_type aisObject,
                                         second_argument_type objectTrsf) const
{
  _context->SetLocation(aisObject, _trsf * objectTrsf);
}

/*! \struct ais_object_display
   *  \brief Functor that displays a given interactive object.
   */
ais_object_display::
ais_object_display(const Handle_AIS_InteractiveContext& context,
                   Standard_Boolean updateViewer) :
  ais_object_unary_function(context),
  _updateViewer(updateViewer)
{ }

void ais_object_display::operator()(argument_type aisObject) const
{
  _context->Display(aisObject, _updateViewer);
}

/*! \struct ais_object_redisplay
   *  \brief Functor that redisplays a given interactive object.
   */
ais_object_redisplay::
ais_object_redisplay(const Handle_AIS_InteractiveContext& context,
                     Standard_Boolean updateViewer,
                     Standard_Boolean allModes) :
  ais_object_unary_function(context),
  _updateViewer(updateViewer),
  _allModes(allModes)
{ }

void ais_object_redisplay::operator()(argument_type aisObject) const
{
  _context->Redisplay(aisObject,
                            _updateViewer, _allModes);
}

/*! \struct ais_object_hide
   *  \brief Functor that hides a given interactive object.
   */
ais_object_hide::ais_object_hide(const Handle_AIS_InteractiveContext& context,
                                 Standard_Boolean updateViewer,
                                 Standard_Boolean putInCollector) :
  ais_object_unary_function(context),
  _updateViewer(updateViewer),
  _putInCollector(putInCollector)
{ }

void ais_object_hide::operator()(argument_type aisObject) const
{
  _context->Erase(aisObject,
                        _updateViewer, _putInCollector);
}

} // namespace occ

// --- Related functions

gp_Vec operator-(const gp_Pnt& p1, const gp_Pnt& p2)
{
  return gp_Vec(p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z());
}

gp_Pnt operator-(const gp_Pnt& p, const gp_Vec& v)
{
  return gp_Pnt(p.X() - v.X(), p.Y() - v.Y(), p.Z() - v.Z());
}

gp_Pnt operator+(const gp_Pnt& p, const gp_Vec& v)
{
  return gp_Pnt(p.X() + v.X(), p.Y() + v.Y(), p.Z() + v.Z());
}

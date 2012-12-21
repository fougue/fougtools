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

#ifndef OCC_UTILS_H
#define OCC_UTILS_H

#include "occtools.h"

#include "../mathtools/point_vector_fwd.h"

#include <BRep_Builder.hxx>
#include <Handle_AIS_InteractiveContext.hxx>
#include <Handle_AIS_InteractiveObject.hxx>
#include <Handle_Geom_Curve.hxx>
#include <Handle_Geom_Surface.hxx>
#include <Handle_Message_ProgressIndicator.hxx>
#include <QtGui/QColor>
#include <QtCore/QString>
#include <Quantity_Color.hxx>
#include <Quantity_NameOfColor.hxx>
#include <Standard_CString.hxx>
#include <TopAbs_Orientation.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec.hxx>
class Poly_Triangle;
class gp_Trsf;
class TColgp_Array1OfPnt;

namespace occ {

// --- Creation
template<typename FWD_ITERATOR>
TopoDS_Compound makeCompound(FWD_ITERATOR iBegin, FWD_ITERATOR iEnd);
template<typename CONTAINER>
TopoDS_Compound makeCompound(CONTAINER cnter);

// --- Geometry
OCCTOOLS_EXPORT gp_Pnt geomCurveD0(const Handle_Geom_Curve& curve, double u);
OCCTOOLS_EXPORT double curveLength(const Handle_Geom_Curve& curve);
OCCTOOLS_EXPORT double curveLengthBetweenParams(const Handle_Geom_Curve& curve,
                                                double firstU, double lastU);
OCCTOOLS_EXPORT gp_Vec normalToFaceAtUV(const TopoDS_Face& face, double u, double v);
OCCTOOLS_EXPORT gp_Vec normalToSurfaceAtUV(const Handle_Geom_Surface& surface, double u, double v);

// --- Color conversion
OCCTOOLS_EXPORT QColor toQtColor(const Quantity_Color& c);
OCCTOOLS_EXPORT QColor toQtColor(const Quantity_NameOfColor c);
OCCTOOLS_EXPORT Quantity_Color toOccColor(const QColor& c);
OCCTOOLS_EXPORT Quantity_NameOfColor toNamedOccColor(const QColor& c);

// --- Geometry conversion
template<typename T>
gp_Pnt toOccPoint3d(const geom::Point3<T>& p);
template<typename T>
gp_Vec toOccVector3d(const geom::Vector3<T>& p);

// --- Type conversion
OCCTOOLS_EXPORT Standard_CString toOccCstring(const QString& str);

// --- String conversion
template<typename OCC_PNT_VEC>
QString toString(const OCC_PNT_VEC& pv,
                 const QString& format = QLatin1String("(%x, %y, %z)"),
                 char realFormat = 'g', unsigned prec = 6);

// --- Visualization
OCCTOOLS_EXPORT void eraseObjectFromContext(Handle_AIS_InteractiveObject object,
                                            Handle_AIS_InteractiveContext context);

// --- Triangulation tools
OCCTOOLS_EXPORT gp_Vec triangleNormal(const TColgp_Array1OfPnt& nodes,
                                      const Poly_Triangle& triangle,
                                      TopAbs_Orientation ori = TopAbs_FORWARD);

// --- Classes
template<typename TYPE>
class down_cast
{
public:
  typedef Handle_Standard_Transient TransientHandle_t;
  explicit down_cast<TYPE>(const TransientHandle_t& handle);
  operator TYPE() const;
  const TYPE operator->() const;
private:
  const TransientHandle_t& m_handle;
}; // class down_cast<>

// --- Constants
const gp_Pnt2d origin2d(0., 0.);
const gp_Dir2d xDir2d(1., 0.);
const gp_Dir2d yDir2d(0., 1.);

const gp_Pnt origin3d(0., 0., 0.);
const gp_Dir xDir3d(1., 0., 0.);
const gp_Dir yDir3d(0., 1., 0.);
const gp_Dir zDir3d(0., 0., 1.);

} // namespace occ

// --- Related functions
OCCTOOLS_EXPORT gp_Vec operator-(const gp_Pnt& p1, const gp_Pnt& p2);
OCCTOOLS_EXPORT gp_Pnt operator-(const gp_Pnt& p, const gp_Vec& v);
OCCTOOLS_EXPORT gp_Pnt operator+(const gp_Pnt& p, const gp_Vec& v);

template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Pnt& p);
template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Vec& v);
template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Dir& d);

#include "utils.impl.h"

#endif // OCC_UTILS_H

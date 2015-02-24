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

#include "topods_utils.h"

#include <BRepAdaptor_Surface.hxx>
#include <BRepLProp_SLProps.hxx>
#include <BRepTools.hxx>
#include <ShapeExtend_WireData.hxx>
#include <ShapeFix_Wire.hxx>
#include <TopAbs_Orientation.hxx>

#include <sstream>

namespace occ {

/*! \class TopoDsUtils
 *  \brief Collection of tools for the TopoDS package
 *
 *  \headerfile topods_utils.h <occtools/topods_utils.h>
 *  \ingroup occtools
 */

/*! \brief Returns the oriented normal of \p face at parametric coords (\p u, \p v )
 *
 *  \note This function is slow if called many successive times on the same face (because it
 *        constructs internally a BRepLProp_SLProps and BRepAdaptor_Surface instance)
 */
gp_Vec TopoDsUtils::normalToFaceAtUV(const TopoDS_Face &face, Standard_Real u, Standard_Real v)
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
    return gp_Vec(0, 0, 1);
}

/*! \brief Returns the string representation of a TopoDS_Shape
 *
 *  Uses BRepTools::Write() internally
 */
std::string TopoDsUtils::shapeToString(const TopoDS_Shape &shape)
{
    std::ostringstream oss(std::ios_base::out);
    BRepTools::Write(shape, oss);
    return oss.str();
}

/*! \brief Constructs the TopoDS_Shape from the string representation \p str (previously generated
 *         with shapeToString())
 *
 *  Uses BRepTools::Read() internally
 */
TopoDS_Shape TopoDsUtils::shapeFromString(const std::string &str)
{
    TopoDS_Shape shape;
    BRep_Builder brepBuilder;

    std::istringstream iss(str, std::ios_base::in);
    BRepTools::Read(shape, iss, brepBuilder);
    return shape;
}

Handle_ShapeExtend_WireData TopoDsUtils::createShapeExtendWireData()
{
    return new ShapeExtend_WireData;
}

void TopoDsUtils::addEdge(const Handle_ShapeExtend_WireData &wireData, const TopoDS_Edge &edge)
{
    wireData->Add(edge);
}

TopoDS_Wire TopoDsUtils::fixedWire(const Handle_ShapeExtend_WireData &wireData)
{
    ShapeFix_Wire fix;
    fix.Load(wireData);
    fix.Perform();
    fix.FixReorder();
    fix.FixConnected();
    return fix.WireAPIMake();
}

} // namespace occ

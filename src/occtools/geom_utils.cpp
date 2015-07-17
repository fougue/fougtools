/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
****************************************************************************/

#include "geom_utils.h"

#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GCPnts_AbscissaPoint.hxx>

namespace occ {

/*! \class GeomUtils
 *  \brief Collection of tools for the Geom package
 *
 *  \headerfile geom_utils.h <occtools/geom_utils.h>
 *  \ingroup occtools
 */

gp_Pnt GeomUtils::geomCurveD0(const Handle_Geom_Curve& curve, Standard_Real u)
{
    gp_Pnt pnt;
    curve->D0(u, pnt);
    return pnt;
}

Standard_Real GeomUtils::curveLength(const Handle_Geom_Curve& curve)
{
    if (!curve.IsNull()) {
        GeomAdaptor_Curve adaptor(curve);
        return GCPnts_AbscissaPoint::Length(adaptor);
    }
    return 0;
}

Standard_Real GeomUtils::curveLengthBetweenParams(
        const Handle_Geom_Curve& curve, Standard_Real firstU, Standard_Real lastU)
{
    if (!curve.IsNull()) {
        GeomAdaptor_Curve adaptor(curve);
        return GCPnts_AbscissaPoint::Length(adaptor, firstU, lastU);
    }
    return 0;
}

gp_Vec GeomUtils::normalToSurfaceAtUV(
        const Handle_Geom_Surface& surface, Standard_Real u, Standard_Real v)
{
    gp_Pnt point;
    gp_Vec d1u, d1v;
    surface->D1(u, v, point, d1u, d1v);
    return d1u ^ d1v;
}

} // namespace occ

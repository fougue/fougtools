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

#pragma once

#include "occtools.h"

#include <Handle_Geom_Curve.hxx>
#include <Handle_Geom_Surface.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

namespace occ {

class OCCTOOLS_EXPORT GeomUtils
{
public:
    static gp_Pnt geomCurveD0(const Handle_Geom_Curve& curve, Standard_Real u);
    static Standard_Real curveLength(const Handle_Geom_Curve& curve);
    static Standard_Real curveLengthBetweenParams(
            const Handle_Geom_Curve& curve,
            Standard_Real firstU,
            Standard_Real lastU);
    static gp_Vec normalToSurfaceAtUV(
            const Handle_Geom_Surface& surface,
            Standard_Real u,
            Standard_Real v);
};

} // namespace occ

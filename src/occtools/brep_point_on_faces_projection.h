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
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <utility>

namespace occ {

class OCCTOOLS_EXPORT BRepPointOnFacesProjection
{
public:
    BRepPointOnFacesProjection();
    BRepPointOnFacesProjection(const TopoDS_Shape& faces);
    ~BRepPointOnFacesProjection();
    void releaseMemory();

    void prepare(const TopoDS_Shape& faces);
    BRepPointOnFacesProjection& compute(const gp_Pnt& point);
    bool isDone() const;

    const TopoDS_Face& solutionFace() const;
    gp_Pnt solutionPoint() const;
    std::pair<double, double> solutionUV() const;
    gp_Vec solutionNormal() const;

private:
    class Private;
    Private* const d;
};

} // namespace occ

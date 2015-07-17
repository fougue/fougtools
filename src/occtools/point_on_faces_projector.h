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
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Face.hxx>
class TopoDS_Shape;

namespace occ {

class OCCTOOLS_EXPORT PointOnFacesProjector
{
public:
    struct OCCTOOLS_EXPORT Result
    {
        Result();
        Result(const TopoDS_Face& sFace,
               const gp_Pnt& sPoint,
               const gp_Vec& sNormal);
        const bool isValid;
        const TopoDS_Face face;
        const gp_Pnt point;
        const gp_Vec normal;
    };

    PointOnFacesProjector();
    PointOnFacesProjector(const TopoDS_Shape& faces);
    ~PointOnFacesProjector();

    void prepare(const TopoDS_Shape& faces);
    const TopoDS_Face* faceOfProjection(const gp_Pnt& point) const;
    Result projected(const gp_Pnt& point) const;
    Result operator()(const gp_Pnt& point) const;

private:
    class Private;
    Private* const d;
};

} // namespace occ

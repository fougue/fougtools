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

#include "brep_point_on_faces_projection.h"

#include "math_utils.h"
#include "topods_utils.h"

#include <BRep_Tool.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom_Surface.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <algorithm>
#include <functional>
#include <cassert>
#include <limits>
#include <vector>

namespace occ {

class BRepPointOnFacesProjection::Private
{
public:
    typedef std::pair<GeomAPI_ProjectPointOnSurf*, TopoDS_Face> ProjectorInfo;
    struct ProjectorCompare
    {
        bool operator()(
                const ProjectorInfo& lhs, const ProjectorInfo& rhs) const;
    };

    Private();

    std::vector<ProjectorInfo> m_projectors;
    ProjectorInfo m_solProjector;
};

BRepPointOnFacesProjection::Private::Private()
    : m_solProjector(static_cast<GeomAPI_ProjectPointOnSurf*>(NULL), TopoDS_Face())
{
}

bool BRepPointOnFacesProjection::Private::ProjectorCompare::operator()(
        const ProjectorInfo &lhs,
        const ProjectorInfo &rhs) const
{
    double p1Dist = std::numeric_limits<double>::max();
    double p2Dist = std::numeric_limits<double>::max();
    if (lhs.first->IsDone() && lhs.first->NbPoints() > 0)
        p1Dist = lhs.first->LowerDistance();
    if (rhs.first->IsDone() && rhs.first->NbPoints() > 0)
        p2Dist = rhs.first->LowerDistance();
    return p1Dist < p2Dist;
}

/*! \class BRepPointOnFacesProjection
 *  \brief Framework to perform normal point projection on a soup of topologic faces
 *
 *  Internally, the utility class GeomAPI_ProjectPointOnSurf is heavily used.
 *  \n The algorithmics are pretty slow : for a point to be projected, the
 *  projection of that point is performed on each loaded TopoDS_Face with the
 *  help of GeomAPI_ProjectPointOnSurf.\n
 *  The minimal distance amongst all the projection candidates is computed to
 *  get the final projected point
 *
 *  \headerfile brep_point_on_faces_projection.h <occtools/brep_point_on_faces_projection.h>
 *  \ingroup occtools
 */

//! Construct an uninitialized BRepPointOnFacesProjection
BRepPointOnFacesProjection::BRepPointOnFacesProjection()
    : d(new Private)
{
}

//! Construct a BRepPointOnFacesProjection and call prepare() on \p faces
BRepPointOnFacesProjection::BRepPointOnFacesProjection(const TopoDS_Shape& faces)
    : d(new Private)
{
    this->prepare(faces);
}

BRepPointOnFacesProjection::~BRepPointOnFacesProjection()
{
    this->releaseMemory();
    delete d;
}

/*! \brief Setup the algorithm to project points on \p faces
 *  \param faces A soup of topologic faces
 */
void BRepPointOnFacesProjection::prepare(const TopoDS_Shape& faces)
{
    this->releaseMemory();

    // Allocate a projector for each face
    for (TopExp_Explorer exp(faces, TopAbs_FACE); exp.More(); exp.Next()) {
        const TopoDS_Face& iFace = TopoDS::Face(exp.Current());
        const Handle_Geom_Surface& iSurf = BRep_Tool::Surface(iFace);
        auto projector = new GeomAPI_ProjectPointOnSurf(occ::origin3d, iSurf);
        d->m_projectors.push_back(Private::ProjectorInfo(projector, iFace));
    }
}

void BRepPointOnFacesProjection::releaseMemory()
{
    // Destroy allocated projectors
    for (auto proj : d->m_projectors)
        delete proj.first;
    d->m_projectors.clear();
}

BRepPointOnFacesProjection& BRepPointOnFacesProjection::compute(const gp_Pnt& point)
{
    for (auto proj : d->m_projectors)
        proj.first->Perform(point);

    auto iResult = std::min_element(
                d->m_projectors.begin(),
                d->m_projectors.end(),
                Private::ProjectorCompare());
    assert(iResult != d->m_projectors.end() && "always_a_minimum");
    d->m_solProjector = *iResult;
    return *this;
}

bool BRepPointOnFacesProjection::isDone() const
{
    const GeomAPI_ProjectPointOnSurf* projector = d->m_solProjector.first;
    if (projector != NULL)
        return projector->IsDone() && projector->NbPoints() > 0;
    return false;
}

const TopoDS_Face& BRepPointOnFacesProjection::solutionFace() const
{
    static TopoDS_Face emptyFace;
    if (this->isDone())
        return d->m_solProjector.second;
    return emptyFace;
}

gp_Pnt BRepPointOnFacesProjection::solutionPoint() const
{
    if (this->isDone())
        return d->m_solProjector.first->NearestPoint();
    return occ::origin3d;
}

std::pair<double, double> BRepPointOnFacesProjection::solutionUV() const
{
    if (this->isDone()) {
        double u, v;
        d->m_solProjector.first->LowerDistanceParameters(u, v);
        return std::make_pair(u, v);
    }
    return std::make_pair(0., 0.);
}

gp_Vec BRepPointOnFacesProjection::solutionNormal() const
{
    if (this->isDone()) {
        double u, v;
        d->m_solProjector.first->LowerDistanceParameters(u, v);
        return occ::TopoDsUtils::normalToFaceAtUV(d->m_solProjector.second, u, v);
    }
    return gp_Vec(0., 0., 1.);
}

} // namespace occ

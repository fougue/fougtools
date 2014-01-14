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

#include "brep_point_on_faces_projection.h"

#include "math_tools.h"
#include "topods_tools.h"

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
    bool operator()(const ProjectorInfo& lhs, const ProjectorInfo& rhs) const;
  };

  Private();

  std::vector<ProjectorInfo> m_projectors;
  ProjectorInfo m_solProjector;
};

BRepPointOnFacesProjection::Private::Private()
  : m_solProjector(static_cast<GeomAPI_ProjectPointOnSurf*>(NULL), TopoDS_Face())
{
}

bool BRepPointOnFacesProjection::Private::ProjectorCompare::operator()(const ProjectorInfo &lhs,
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
 *  \n The algorithmics are pretty slow : for a point to be projected, the projection of that point
 *  is performed on each loaded TopoDS_Face with the help of GeomAPI_ProjectPointOnSurf.\n
 *  The minimal distance amongst all the projection candidates is computed to get the final
 *  projected point
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
    d->m_projectors.push_back(
          Private::ProjectorInfo(new GeomAPI_ProjectPointOnSurf(occ::origin3d, iSurf), iFace));
  }
}

void BRepPointOnFacesProjection::releaseMemory()
{
  // Destroy allocated projectors
  for (unsigned i = 0; i < d->m_projectors.size(); ++i) {
    if (d->m_projectors.at(i).first != NULL)
      delete d->m_projectors.at(i).first;
  }
  d->m_projectors.clear();
}

BRepPointOnFacesProjection& BRepPointOnFacesProjection::compute(const gp_Pnt& point)
{
  //QtConcurrent::map(m_projectors, projection_perform(point));
  /*        QFutureWatcher<void> futureWatcher;
            futureWatcher.setFuture(
              QtConcurrent::map(m_projectors,
                          boost::bind(&Projector::Perform,
                                 boost::bind(&ProjectorInfo::first, _1), point)));
            futureWatcher.waitForFinished();*/
  for (unsigned i = 0; i < d->m_projectors.size(); ++i)
    d->m_projectors.at(i).first->Perform(point);

  std::vector<Private::ProjectorInfo>::const_iterator iResult =
      std::min_element(d->m_projectors.begin(), d->m_projectors.end(), Private::ProjectorCompare());
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
    return occ::TopoDsTools::normalToFaceAtUV(d->m_solProjector.second, u, v);
  }
  return gp_Vec(0., 0., 1.);
}

} // namespace occ

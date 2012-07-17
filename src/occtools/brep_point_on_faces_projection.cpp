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

#include "utils.h"

#include <BRep_Tool.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom_Surface.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <limits>

namespace {

typedef GeomAPI_ProjectPointOnSurf Projector;
struct projector_compare :
    public std::binary_function<const GeomAPI_ProjectPointOnSurf*,const GeomAPI_ProjectPointOnSurf*, bool>
{
  bool operator()(const GeomAPI_ProjectPointOnSurf* p1,
                  const GeomAPI_ProjectPointOnSurf* p2) const
  {
    double p1Dist = std::numeric_limits<double>::max();
    double p2Dist = std::numeric_limits<double>::max();
    if (p1->IsDone() && p1->NbPoints() > 0)
      p1Dist = p1->LowerDistance();
    if (p2->IsDone() && p2->NbPoints() > 0)
      p2Dist = p2->LowerDistance();
    return p1Dist < p2Dist;
  }
};

} // Anonymous namespace

namespace occ {

/*! \class BRepPointOnFacesProjection
 *  \brief Framework to perform normal point projection on a soup of topologic
 *         faces
 *
 *  Internally, the utility class GeomAPI_ProjectPointOnSurf is heavily used.
 *  \n The algorithmics are pretty slow : for a point to be projected, the
 *  projection of that point is performed on each loaded TopoDS_Face with the
 *  help of GeomAPI_ProjectPointOnSurf.\n The minimal distance amongst all
 *  the projection candidates is computed to get the final projected point
 */

//! Construct an uninitialized BRepPointOnFacesProjection
BRepPointOnFacesProjection::BRepPointOnFacesProjection()
  : m_solProjector(static_cast<Projector*>(0), TopoDS_Face())
{
}

//! Construct a BRepPointOnFacesProjection and call prepare() on \p faces
BRepPointOnFacesProjection::BRepPointOnFacesProjection(const TopoDS_Shape& faces)
  : m_solProjector(static_cast<Projector*>(0), TopoDS_Face())
{
  this->prepare(faces);
}

BRepPointOnFacesProjection::~BRepPointOnFacesProjection()
{
  this->releaseMemory();
}

/*! \brief Setup the algorithm to project points on \p faces
 *  \param faces A soup of topologic faces
 */
void BRepPointOnFacesProjection::prepare(const TopoDS_Shape& faces)
{
  this->releaseMemory();
  // Allocate a projector for each face
  for (TopExp_Explorer exp(faces, TopAbs_FACE); exp.More(); exp.Next()) {
    TopoDS_Face iFace = TopoDS::Face(exp.Current());
    Handle_Geom_Surface iSurf = BRep_Tool::Surface(iFace);
    m_projectors.push_back(ProjectorInfo(new Projector(occ::origin3d, iSurf), iFace));
  }
}

void BRepPointOnFacesProjection::releaseMemory()
{
  // Destroy allocated projectors
  BOOST_FOREACH(const ProjectorInfo& projector, m_projectors) {
    if (projector.first != 0)
      delete projector.first;
  }
  m_projectors.clear();
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
  std::for_each(m_projectors.begin(), m_projectors.end(),
                boost::bind(&Projector::Perform,
                            boost::bind(&ProjectorInfo::first, _1), point));
  std::vector<ProjectorInfo>::const_iterator iResult =
      std::min_element(m_projectors.begin(), m_projectors.end(),
                       boost::bind(::projector_compare(),
                                   boost::bind(&ProjectorInfo::first, _1),
                                   boost::bind(&ProjectorInfo::first, _2)));
  assert(iResult != m_projectors.end() && "always_a_minimum");
  m_solProjector = *iResult;
  return *this;
}

bool BRepPointOnFacesProjection::isDone() const
{
  const Projector* projector = m_solProjector.first;
  if (projector != 0)
    return projector->IsDone() && projector->NbPoints() > 0;
  return false;
}

const TopoDS_Face& BRepPointOnFacesProjection::solutionFace() const
{
  static TopoDS_Face emptyFace;
  if (this->isDone())
    return m_solProjector.second;
  return emptyFace;
}

gp_Pnt BRepPointOnFacesProjection::solutionPoint() const
{
  if (this->isDone())
    return m_solProjector.first->NearestPoint();
  return occ::origin3d;
}

std::pair<double, double> BRepPointOnFacesProjection::solutionUV() const
{
  if (this->isDone()) {
    double u, v;
    m_solProjector.first->LowerDistanceParameters(u, v);
    return std::make_pair(u, v);
  }
  return std::make_pair(0., 0.);
}

gp_Vec BRepPointOnFacesProjection::solutionNormal() const
{
  if (this->isDone()) {
    double u, v;
    m_solProjector.first->LowerDistanceParameters(u, v);
    return occ::normalToFaceAtUV(m_solProjector.second, u, v);
  }
  return gp_Vec(0., 0., 1.);
}

} // namespace occ

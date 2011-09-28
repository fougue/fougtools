#ifndef OCC_BREP_POINT_ON_FACES_PROJECTION_H
#define OCC_BREP_POINT_ON_FACES_PROJECTION_H

#include "occtools/occtools.h"
#include <TopoDS_Face.hxx>
#include <gp_Vec.hxx>
#include <utility>
#include <vector>
class gp_Pnt;
class GeomAPI_ProjectPointOnSurf;

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
  typedef GeomAPI_ProjectPointOnSurf Projector_t;
  typedef std::pair<Projector_t*, TopoDS_Face> ProjectorInfo_t;
  std::vector<ProjectorInfo_t> _projectors;
  ProjectorInfo_t _solProjector;
};

} // namespace occ

#endif // OCC_BREP_POINT_ON_FACES_PROJECTION_H

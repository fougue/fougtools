#ifndef OCC_POINT_ON_FACES_PROJECTOR_H
#define OCC_POINT_ON_FACES_PROJECTOR_H

#include "occtools/occtools.h"
#include <TopoDS_Face.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>

namespace occ {

class OCCTOOLS_EXPORT PointOnFacesProjector
{
public:
  struct Result
  {
    Result();
    Result(const TopoDS_Face& sFace, const gp_Pnt& sPoint, const gp_Vec& sNormal);
    const bool isValid;
    const TopoDS_Face& face;
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
  struct PointOnFacesProjector_Impl* _d;
};

} // namespace occ

#endif // OCC_POINT_ON_FACES_PROJECTOR_H

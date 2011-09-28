#ifndef GEOM_PROJECT_POINT_ON_TRIANGLE_H
#define GEOM_PROJECT_POINT_ON_TRIANGLE_H

#include <utility>

namespace geom {

template<typename _PNT_VEC_TRAITS_>
const std::pair<typename _PNT_VEC_TRAITS_::Pnt_t, bool>
projectPointOnTriangle(const typename _PNT_VEC_TRAITS_::Pnt_t& p,
                       const typename _PNT_VEC_TRAITS_::Pnt_t& v0,
                       const typename _PNT_VEC_TRAITS_::Pnt_t& v1,
                       const typename _PNT_VEC_TRAITS_::Pnt_t& v2);

template<typename _PNT_VEC_TRAITS_>
struct project_point_on_triangle
{
  project_point_on_triangle(const typename _PNT_VEC_TRAITS_::Pnt_t& v0,
                            const typename _PNT_VEC_TRAITS_::Pnt_t& v1,
                            const typename _PNT_VEC_TRAITS_::Pnt_t& v2);
  const std::pair<typename _PNT_VEC_TRAITS_::Pnt_t, bool>
  operator()(const typename _PNT_VEC_TRAITS_::Pnt_t pnt);

private:
  const typename _PNT_VEC_TRAITS_::Pnt_t& _v0;
  const typename _PNT_VEC_TRAITS_::Pnt_t& _v1;
  const typename _PNT_VEC_TRAITS_::Pnt_t& _v2;
}; // struct project_point_on_triangle

} // namespace geom

#include "mathtools/project_point_on_triangle.impl.h"

#endif // GEOM_PROJECT_POINT_ON_TRIANGLE_H

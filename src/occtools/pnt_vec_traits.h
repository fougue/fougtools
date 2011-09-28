#ifndef OCC_PNT_VEC_TRAITS_H
#define OCC_PNT_VEC_TRAITS_H

#include <cassert>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include "mathtools/pnt_vec_traits_def.h"

namespace geom {

template<>
struct PntVecTraits<gp_Pnt, gp_Vec>
{
  typedef gp_Pnt Pnt_t;
  typedef gp_Vec Vec_t;
  typedef Standard_Real Value_t;

  static void normalize(Vec_t* v)
  {
    assert(v != 0);
    v->Normalize();
  }

  static Vec_t cross(const Vec_t& u, const Vec_t& v)
  {
    return u.Crossed(v);
  }

  static Value_t dot(const Vec_t& u, const Vec_t& v)
  {
    return u.Dot(v);
  }

  static Pnt_t translate(const Pnt_t& p, const Vec_t& v)
  {
    return p.Translated(v);
  }

  static Vec_t vector(const Pnt_t& p1, const Pnt_t& p2)
  {
    return Vec_t(p1, p2);
  }

  static Vec_t vector(const Pnt_t& p)
  {
    return Vec_t(p.X(), p.Y(), p.Z());
  }

  static Vec_t mult(Value_t k, const Vec_t& v)
  {
    return k * v;
  }
};

} // namespace geom

namespace occ {

typedef geom::PntVecTraits<gp_Pnt, gp_Vec> PntVecTraits_t;

} // namespace occ

#endif // OCC_PNT_VEC_TRAITS_H

#ifndef GEOM_PNT_VEC_TRAITS_DEF_H
# define GEOM_PNT_VEC_TRAITS_DEF_H

namespace geom {

template<typename _POINT_, typename _VECTOR_>
struct PntVecTraits
{
# ifndef _MSC_VER
  typedef _POINT_ Pnt_t;
  typedef _VECTOR_ Vec_t;
  typedef double Value_t;

  static void normalize(Vec_t* v);
  static Vec_t cross(const Vec_t& u, const Vec_t& v);
  static Value_t dot(const Vec_t& u, const Vec_t& v);
  static Pnt_t translate(const Pnt_t& p, const Vec_t& v);
  static Vec_t vector(const Pnt_t& p1, const Pnt_t& p2);
  static Vec_t vector(const Pnt_t& p);
  static Vec_t mult(Value_t k, const Vec_t& v);
# endif // _MSC_VER
};

} // namespace geom

#endif // GEOM_PNT_VEC_TRAITS_DEF_H

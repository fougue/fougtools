#ifndef GEOM_POINT_VECTOR_FWD_H
# define GEOM_POINT_VECTOR_FWD_H

# include "pnt_vec_traits_def.h"

namespace geom {

template<typename _T_, unsigned _S_>
class Point;

template<typename _T_>
class Point2;

typedef Point2<int>         Point2i_t;
typedef Point2<long>        Point2l_t;
typedef Point2<float>       Point2f_t;
typedef Point2<double>      Point2d_t;
typedef Point2<long double> Point2ld_t;

template<typename _T_>
class Point3;

typedef Point3<int>         Point3i_t;
typedef Point3<long>        Point3l_t;
typedef Point3<float>       Point3f_t;
typedef Point3<double>      Point3d_t;
typedef Point3<long double> Point3ld_t;

template<typename _T_, unsigned _S_>
class Vector;

template<typename _T_>
class Vector2;

typedef Vector2<int>         Vector2i_t;
typedef Vector2<long>        Vector2l_t;
typedef Vector2<float>       Vector2f_t;
typedef Vector2<double>      Vector2d_t;
typedef Vector2<long double> Vector2ld_t;

template<typename _T_>
class Vector3;

typedef Vector3<int>         Vector3i_t;
typedef Vector3<long>        Vector3l_t;
typedef Vector3<float>       Vector3f_t;
typedef Vector3<double>      Vector3d_t;
typedef Vector3<long double> Vector3ld_t;

template<typename _T_>
struct PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >;

typedef PntVecTraits< geom::Point3<int>, geom::Vector3<int> >
NaturalPntVecTraitsi_t;
typedef PntVecTraits< geom::Point3<long>, geom::Vector3<long> >
NaturalPntVecTraitsl_t;
typedef PntVecTraits< geom::Point3<float>, geom::Vector3<float> >
NaturalPntVecTraitsf_t;
typedef PntVecTraits< geom::Point3<double>, geom::Vector3<double> >
NaturalPntVecTraitsd_t;
typedef PntVecTraits< geom::Point3<long double>, geom::Vector3<long double> >
NaturalPntVecTraitsld_t;

} // namespace geom

#endif // GEOM_POINT_VECTOR_FWD_H

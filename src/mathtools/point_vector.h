#ifndef BITS_GEOM_POINT_VECTOR_H
# define BITS_GEOM_POINT_VECTOR_H

# include "mathtools/consts.h"
# include "mathtools/point_vector_fwd.h"
# include "mathtools/pnt_vec_traits_def.h"
# include "mathtools/fixed_array.h"
# include <cassert>
# include <cmath>

namespace geom {

// ---
// --- class Point<>
// ---
template<typename _T_, unsigned _S_>
class Point : public structs::FixedArray<_T_, _S_>
{
private:
  typedef Point<_T_, _S_> Self_t;
  typedef structs::FixedArray<_T_, _S_> Super_t;

public:
  Point<_T_, _S_>();
  Point<_T_, _S_>(const Self_t& other);

  Self_t& operator=(const Self_t& other);

  _T_ dist(const Self_t& other) const;
  _T_ distSquare(const Self_t& other) const;
  _T_ distL2(const Self_t& other) const;
  _T_ distL2Square(const Self_t& other) const;
};

template<typename _T_, unsigned _S_>
Point<_T_, _S_> operator-(const Point<_T_, _S_>& p);

// ---
// --- class Point2<>
// ---
template<typename _T_>
class Point2 : public Point<_T_, 2>
{
private:
  typedef Point2<_T_>   Self_t;
  typedef Point<_T_, 2> Super_t;

public:
  Point2<_T_>();
  Point2<_T_>(const _T_& vx, const _T_& vy);
  Point2<_T_>(const Super_t& other);

  const _T_& x() const;
  const _T_& y() const;
  const _T_& theta() const;

  Self_t& operator=(const Self_t& other);
  void setX(const _T_& v);
  void setY(const _T_& v);
  void setTheta(const _T_& v);
  void setXy(const _T_& vx, const _T_& vy);
};

// ---
// --- class Point3<>
// ---
template<typename _T_>
class Point3 : public Point<_T_, 3>
{
private:
  typedef Point3<_T_>   Self_t;
  typedef Point<_T_, 3> Super_t;

public:
  Point3<_T_>();
  Point3<_T_>(const _T_& vx, const _T_& vy, const _T_& vz);
  Point3<_T_>(const Super_t& other);

  const _T_& x() const;
  const _T_& y() const;
  const _T_& z() const;

  Self_t& operator=(const Self_t& other);
  void setX(const _T_& v);
  void setY(const _T_& v);
  void setZ(const _T_& v);
  void setXyz(const _T_& vx, const _T_& vy, const _T_& vz);
};

// ---
// --- class Vector<>
// ---
template<typename _T_, unsigned _S_>
class Vector : public structs::FixedArray<_T_, _S_>
{
private:
  typedef Vector<_T_, _S_> Self_t;
  typedef structs::FixedArray<_T_, _S_> Super_t;

public:
  Vector<_T_, _S_>();
  Vector<_T_, _S_>(const Self_t& other);

  bool isNull(const _T_& tol = static_cast<_T_>(1e-6)) const;
  _T_ norm() const;
  _T_ squareNorm() const;

  Self_t& operator=(const Self_t& other);

  void normalize();
  const Vector<_T_, _S_> normalized() const;

  void reverse();
};

template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator*(const Vector<_T_, _S_>& u, const _T_& k);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator*(const _T_& k, const Vector<_T_, _S_>& u);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator/(const Vector<_T_, _S_>& u, const _T_& k);

template<typename _T_, unsigned _S_>
_T_ operator*(const Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator+(const Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v);

template<typename _T_, unsigned _S_>
Point<_T_, _S_> operator+(const Point<_T_, _S_>& p, const Vector<_T_, _S_>& v);

template<typename _T_, unsigned _S_>
Point<_T_, _S_> operator-(const Point<_T_, _S_>& p, const Vector<_T_, _S_>& v);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator-(const Vector<_T_, _S_>& u);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator-(const Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator-(const Point<_T_, _S_>& p1, const Point<_T_, _S_>& p2);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& operator+=(Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& operator-=(Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& operator*=(Vector<_T_, _S_>& u, const _T_& k);

template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& operator/=(Vector<_T_, _S_>& u, const _T_& k);

// ---
// --- class Vector2<>
// ---
template<typename _T_>
class Vector2 : public Vector<_T_, 2>
{
private:
  typedef Vector2<_T_>   Self_t;
  typedef Vector<_T_, 2> Super_t;

public:
  Vector2<_T_>();
  Vector2<_T_>(const _T_& vx, const _T_& vy);
  Vector2<_T_>(const Super_t& other);

  const _T_& x() const;
  const _T_& y() const;
  const _T_& theta() const;

  Self_t& operator=(const Self_t& other);
  void setX(const _T_& v);
  void setY(const _T_& v);
  void setTheta(const _T_& v);
  void setXy(const _T_& vx, const _T_& vy);
};

template<typename _T_>
_T_ angle2(const Vector<_T_, 2>& v1, const Vector<_T_, 2>& v2);

// ---
// --- class Vector3<>
// ---
template<typename _T_>
class Vector3 : public Vector<_T_, 3>
{
private:
  typedef Vector3<_T_>   Self_t;
  typedef Vector<_T_, 3> Super_t;

public:
  Vector3<_T_>();
  Vector3<_T_>(const _T_& vx, const _T_& vy, const _T_& vz);
  Vector3<_T_>(const Super_t& other);

  const _T_& x() const;
  const _T_& y() const;
  const _T_& z() const;

  Self_t& operator=(const Self_t& other);
  void setX(const _T_& v);
  void setY(const _T_& v);
  void setZ(const _T_& v);
  void setXyz(const _T_& vx, const _T_& vy, const _T_& vz);
};

template<typename _T_>
_T_ angle3(const Vector<_T_, 3>& v1, const Vector<_T_, 3>& v2);
template<typename _T_, unsigned _S_>
Vector<_T_, 3> operator^(const Vector<_T_, 3>& v1,
                         const Vector<_T_, 3>& v2);

// ---
// --- PntVecTraits
// ---
template<typename _T_>
struct PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >
{
  typedef geom::Point3<_T_>  Pnt_t;
  typedef geom::Vector3<_T_> Vec_t;
  typedef _T_ Value_t;

  static void normalize(Vec_t* v);
  static Vec_t cross(const Vec_t& u, const Vec_t& v);
  static Value_t dot(const Vec_t& u, const Vec_t& v);
  static Pnt_t translate(const Pnt_t& p, const Vec_t& v);
  static Vec_t vector(const Pnt_t& p1, const Pnt_t& p2);
  static Vec_t vector(const Pnt_t& p);
  static Vec_t mult(Value_t k, const Vec_t& v);
}; // struct PntVecTraits

#include "mathtools/point_vector.impl.h"

// ---
// --- Constants
// ---
const geom::Point2f_t  origin2f(0.f, 0.f);
const geom::Point2d_t  origin2d(0., 0.);
const geom::Point2ld_t origin2ld(0., 0.);
const geom::Point3f_t  origin3f(0.f, 0.f, 0.f);
const geom::Point3d_t  origin3d(0., 0., 0.);
const geom::Point3ld_t origin3ld(0., 0., 0.);

const geom::Vector2f_t  xDir2f(1.f, 0.f);
const geom::Vector2d_t  xDir2d(1., 0.);
const geom::Vector2ld_t xDir2ld(1., 0.);
const geom::Vector3f_t  xDir3f(1.f, 0.f, 0.f);
const geom::Vector3d_t  xDir3d(1., 0., 0.);
const geom::Vector3ld_t xDir3ld(1., 0., 0.);

const geom::Vector2f_t  yDir2f(0.f, 1.f);
const geom::Vector2d_t  yDir2d(0., 1.);
const geom::Vector2ld_t yDir2ld(0., 1.);
const geom::Vector3f_t  yDir3f(0.f, 1.f, 0.f);
const geom::Vector3d_t  yDir3d(0., 1., 0.);
const geom::Vector3ld_t yDir3ld(0., 1., 0.);

const geom::Vector3f_t  zDir3f(0.f, 0.f, 1.f);
const geom::Vector3d_t  zDir3d(0., 0., 1.);
const geom::Vector3ld_t zDir3ld(0., 0., 1.);

} // namespace geom

#endif // BITS_GEOM_POINT_VECTOR_H

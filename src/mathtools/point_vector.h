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

#ifndef BITS_GEOM_POINT_VECTOR_H
#define BITS_GEOM_POINT_VECTOR_H

#include "consts.h"
#include "point_vector_fwd.h"
#include "pnt_vec_traits_def.h"
#include "fixed_array.h"
#include <cassert>
#include <cmath>

namespace geom {

// ---
// --- class Point<>
// ---
template<typename T, unsigned S>
class Point : public structs::FixedArray<T, S>
{
private:
  typedef Point<T, S> Self_t;
  typedef structs::FixedArray<T, S> Super_t;

public:
  Point<T, S>();
  Point<T, S>(const Self_t& other);

  Self_t& operator=(const Self_t& other);

  T dist(const Self_t& other) const;
  T distSquare(const Self_t& other) const;
  T distL2(const Self_t& other) const;
  T distL2Square(const Self_t& other) const;
};

template<typename T, unsigned S>
Point<T, S> operator-(const Point<T, S>& p);

// ---
// --- class Point2<>
// ---
template<typename T>
class Point2 : public Point<T, 2>
{
private:
  typedef Point2<T>   Self_t;
  typedef Point<T, 2> Super_t;

public:
  Point2<T>();
  Point2<T>(const T& vx, const T& vy);
  Point2<T>(const Super_t& other);

  const T& x() const;
  const T& y() const;
  const T& theta() const;

  Self_t& operator=(const Self_t& other);
  void setX(const T& v);
  void setY(const T& v);
  void setTheta(const T& v);
  void setXy(const T& vx, const T& vy);
};

// ---
// --- class Point3<>
// ---
template<typename T>
class Point3 : public Point<T, 3>
{
private:
  typedef Point3<T>   Self_t;
  typedef Point<T, 3> Super_t;

public:
  Point3<T>();
  Point3<T>(const T& vx, const T& vy, const T& vz);
  Point3<T>(const Super_t& other);

  const T& x() const;
  const T& y() const;
  const T& z() const;

  Self_t& operator=(const Self_t& other);
  void setX(const T& v);
  void setY(const T& v);
  void setZ(const T& v);
  void setXyz(const T& vx, const T& vy, const T& vz);
};

// ---
// --- class Vector<>
// ---
template<typename T, unsigned S>
class Vector : public structs::FixedArray<T, S>
{
private:
  typedef Vector<T, S> Self_t;
  typedef structs::FixedArray<T, S> Super_t;

public:
  Vector<T, S>();
  Vector<T, S>(const Self_t& other);

  bool isNull(const T& tol = static_cast<T>(1e-6)) const;
  T norm() const;
  T squareNorm() const;

  Self_t& operator=(const Self_t& other);

  void normalize();
  const Vector<T, S> normalized() const;

  void reverse();
};

template<typename T, unsigned S>
Vector<T, S> operator*(const Vector<T, S>& u, const T& k);

template<typename T, unsigned S>
Vector<T, S> operator*(const T& k, const Vector<T, S>& u);

template<typename T, unsigned S>
Vector<T, S> operator/(const Vector<T, S>& u, const T& k);

template<typename T, unsigned S>
T operator*(const Vector<T, S>& u, const Vector<T, S>& v);

template<typename T, unsigned S>
Vector<T, S> operator+(const Vector<T, S>& u, const Vector<T, S>& v);

template<typename T, unsigned S>
Point<T, S> operator+(const Point<T, S>& p, const Vector<T, S>& v);

template<typename T, unsigned S>
Point<T, S> operator-(const Point<T, S>& p, const Vector<T, S>& v);

template<typename T, unsigned S>
Vector<T, S> operator-(const Vector<T, S>& u);

template<typename T, unsigned S>
Vector<T, S> operator-(const Vector<T, S>& u, const Vector<T, S>& v);

template<typename T, unsigned S>
Vector<T, S> operator-(const Point<T, S>& p1, const Point<T, S>& p2);

template<typename T, unsigned S>
Vector<T, S>& operator+=(Vector<T, S>& u, const Vector<T, S>& v);

template<typename T, unsigned S>
Vector<T, S>& operator-=(Vector<T, S>& u, const Vector<T, S>& v);

template<typename T, unsigned S>
Vector<T, S>& operator*=(Vector<T, S>& u, const T& k);

template<typename T, unsigned S>
Vector<T, S>& operator/=(Vector<T, S>& u, const T& k);

// ---
// --- class Vector2<>
// ---
template<typename T>
class Vector2 : public Vector<T, 2>
{
private:
  typedef Vector2<T>   Self_t;
  typedef Vector<T, 2> Super_t;

public:
  Vector2<T>();
  Vector2<T>(const T& vx, const T& vy);
  Vector2<T>(const Super_t& other);

  const T& x() const;
  const T& y() const;
  const T& theta() const;

  Self_t& operator=(const Self_t& other);
  void setX(const T& v);
  void setY(const T& v);
  void setTheta(const T& v);
  void setXy(const T& vx, const T& vy);
};

template<typename T>
T angle2(const Vector<T, 2>& v1, const Vector<T, 2>& v2);

// ---
// --- class Vector3<>
// ---
template<typename T>
class Vector3 : public Vector<T, 3>
{
private:
  typedef Vector3<T>   Self_t;
  typedef Vector<T, 3> Super_t;

public:
  Vector3<T>();
  Vector3<T>(const T& vx, const T& vy, const T& vz);
  Vector3<T>(const Super_t& other);

  const T& x() const;
  const T& y() const;
  const T& z() const;

  Self_t& operator=(const Self_t& other);
  void setX(const T& v);
  void setY(const T& v);
  void setZ(const T& v);
  void setXyz(const T& vx, const T& vy, const T& vz);
};

template<typename T>
T angle3(const Vector<T, 3>& v1, const Vector<T, 3>& v2);
template<typename T, unsigned S>
Vector<T, 3> operator^(const Vector<T, 3>& v1, const Vector<T, 3>& v2);

// ---
// --- PntVecTraits
// ---
template<typename T>
struct PntVecTraits< geom::Point3<T>, geom::Vector3<T> >
{
  typedef geom::Point3<T>  Pnt_t;
  typedef geom::Vector3<T> Vec_t;
  typedef T Value_t;

  static void normalize(Vec_t* v);
  static Vec_t cross(const Vec_t& u, const Vec_t& v);
  static Value_t dot(const Vec_t& u, const Vec_t& v);
  static Pnt_t translate(const Pnt_t& p, const Vec_t& v);
  static Vec_t vector(const Pnt_t& p1, const Pnt_t& p2);
  static Vec_t vector(const Pnt_t& p);
  static Vec_t mult(Value_t k, const Vec_t& v);
}; // struct PntVecTraits

#include "point_vector.impl.h"

// ---
// --- Constants
// ---
const geom::Point2f_t  origin2f(0.f, 0.f);
const geom::Point2d_t  origin2d(0., 0.);
const geom::Point2ld_t origin2ld(0., 0.);
const geom::Point3f_t  origin3f(0.f, 0.f, 0.f);
const geom::Point3d_t  origin3d(0., 0., 0.);
const geom::Point3ld_t origin3ld(0., 0., 0.);

const geom::Vector2f_t  nullVec2f(0.f, 0.f);
const geom::Vector2d_t  nullVec2d(0., 0.);
const geom::Vector2ld_t nullVec2ld(0., 0.);
const geom::Vector3f_t  nullVec3f(0.f, 0.f, 0.f);
const geom::Vector3d_t  nullVec3d(0., 0., 0.);
const geom::Vector3ld_t nullVec3ld(0., 0., 0.);

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

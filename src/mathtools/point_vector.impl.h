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

#ifdef BITS_GEOM_POINT_VECTOR_H

// --- Construction

template<typename T, unsigned S>
Point<T, S>::Point()
{
}

template<typename T, unsigned S>
Point<T, S>::Point(const Self_t& other)
  : Super_t(other)
{
}

// --- Element change

template<typename T, unsigned S>
Point<T, S>& Point<T, S>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

//! Synonym to distL2()
template<typename T, unsigned S>
T Point<T, S>::dist(const Self_t& other) const
{
  return this->distL2(other);
}

//! Synonym to distL2Square()
template<typename T, unsigned S>
T Point<T, S>::distSquare(const Self_t& other) const
{
  return this->distL2Square(other);
}

//! Euclidian distance
template<typename T, unsigned S>
T Point<T, S>::distL2(const Self_t& other) const
{
  return static_cast<T>(std::sqrt(this->distL2Square(other)));
}

//! Squared euclidian distance
template<typename T, unsigned S>
T Point<T, S>::distL2Square(const Self_t& other) const
{
  T result = static_cast<T>(0);
  for (unsigned i = 0; i < S; i++) {
    T d = Super_t::m_vector[i] - other[i];
    result += d * d;
  }
  assert(result >= 0 && "positive_distance");
  return result;
}

/*! \brief
 *  \relates Point
 */
template<typename T, unsigned S>
Point<T, S> operator-(const Point<T, S>& p)
{
  Point<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = -p[i];
  return result;
}

/*! \class Point2
 *  \brief
 */

// --- Construction

template<typename T>
Point2<T>::Point2()
{
}

template<typename T>
Point2<T>::Point2(const T& vx, const T& vy)
{
  Super_t::m_vector[0] = vx;
  Super_t::m_vector[1] = vy;
}

template<typename T>
Point2<T>::Point2(const Super_t& other)
  : Super_t(other)
{
}

// --- Access

template<typename T>
const T& Point2<T>::x() const
{
  return Super_t::m_vector[0];
}


template<typename T>
const T& Point2<T>::y() const
{
  return Super_t::m_vector[1];
}

template<typename T>
const T& Point2<T>::theta() const
{
  return Super_t::m_vector[1];
}

// --- Element change

template<typename T>
Point2<T>& Point2<T>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename T>
void Point2<T>::setX(const T& v)
{
  Super_t::m_vector[0] = v;
}

template<typename T>
void Point2<T>::setY(const T& v)
{
  Super_t::m_vector[1] = v;
}

template<typename T>
void Point2<T>::setTheta(const T& v)
{
  Super_t::m_vector[1] = v;
}

template<typename T>
void Point2<T>::setXy(const T& vx, const T& vy)
{
  Super_t::m_vector[0] = vx;
  Super_t::m_vector[1] = vy;
}

/*! \class Point3
 *  \brief
 */

// --- Construction

template<typename T>
Point3<T>::Point3()
{
}

template<typename T>
Point3<T>::Point3(const T& vx, const T& vy, const T& vz)
{
  Super_t::m_vector[0] = vx;
  Super_t::m_vector[1] = vy;
  Super_t::m_vector[2] = vz;
}

template<typename T>
Point3<T>::Point3(const Super_t& other)
  : Super_t(other)
{
}

// --- Access

template<typename T>
const T& Point3<T>::x() const
{
  return Super_t::m_vector[0];
}

template<typename T>
const T& Point3<T>::y() const
{
  return Super_t::m_vector[1];
}

template<typename T>
const T& Point3<T>::z() const
{
  return Super_t::m_vector[2];
}

// --- Element change

template<typename T>
Point3<T>& Point3<T>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename T>
void Point3<T>::setX(const T& v)
{
  Super_t::m_vector[0] = v;
}

template<typename T>
void Point3<T>::setY(const T& v)
{
  Super_t::m_vector[1] = v;
}

template<typename T>
void Point3<T>::setZ(const T& v)
{
  Super_t::m_vector[2] = v;
}

template<typename T>
void Point3<T>::setXyz(const T& vx, const T& vy, const T& vz)
{
  Super_t::m_vector[0] = vx;
  Super_t::m_vector[1] = vy;
  Super_t::m_vector[2] = vz;
}

/*! \class Vector
 *  \brief
 */

// --- Construction

template<typename T, unsigned S>
Vector<T, S>::Vector()
{
}

template<typename T, unsigned S>
Vector<T, S>::Vector(const Self_t& other)
  : Super_t(other)
{
}

template<typename T, unsigned S>
const Vector<T, S> Vector<T, S>::normalized() const
{
  return *this / this->norm();
}

// --- Measurement

template<typename T, unsigned S>
bool Vector<T, S>::isNull(const T& tol) const
{
  return this->squareNorm() < tol;
}

template<typename T, unsigned S>
T Vector<T, S>::norm() const
{
  return std::sqrt(this->squareNorm());
}

template<typename T, unsigned S>
T Vector<T, S>::squareNorm() const
{
  T result = static_cast<T>(0);
  for (unsigned i = 0; i < S; ++i)
    result += Super_t::m_vector[i] * Super_t::m_vector[i];
  return result;
}

// --- Element change

template<typename T, unsigned S>
Vector<T, S>& Vector<T, S>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename T, unsigned S>
void Vector<T, S>::normalize()
{
  const T n = this->norm();
  for (unsigned i = 0; i < S; ++i)
    Super_t::m_vector[i] /= n;
}

template<typename T, unsigned S>
void Vector<T, S>::reverse()
{
  for (unsigned i = 0; i < S; ++i)
    Super_t::m_vector[i] = -Super_t::m_vector[i];
}


/*! \brief Vector \p u multiplied by scalar \p k
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S> operator*(const Vector<T, S>& u, const T& k)
{
  Vector<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = k * u[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S> operator*(const T& k, const Vector<T, S>& u)
{
  return u * k;
}

/*! \brief Vector \p u divided by scalar \p k
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S> operator/(const Vector<T, S>& u, const T& k)
{
  Vector<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = u[i] / k;
  return result;
}

/*! \brief Scalar product of vectors \p u and \p v i.e. <u|v>
 *  \relates Vector
 */
template<typename T, unsigned S>
T operator*(const Vector<T, S>& u, const Vector<T, S>& v)
{
  T result = static_cast<T>(0);
  for (unsigned i = 0; i < S; ++i)
    result += u[i] * v[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S> operator+(const Vector<T, S>& u, const Vector<T, S>& v)
{
  Vector<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = u[i] + v[i];
  return result;
}

/*! \brief Point \p p translated by vector \p v
 *  \relates Point
 */
template<typename T, unsigned S>
Point<T, S> operator+(const Point<T, S>& p, const Vector<T, S>& v)
{
  Point<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = p[i] + v[i];
  return result;
}

/*! \brief Point \p p translated by vector \p v
 *  \relates Point
 */
template<typename T, unsigned S>
Point<T, S> operator-(const Point<T, S>& p, const Vector<T, S>& v)
{
  Point<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = p[i] - v[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S> operator-(const Vector<T, S>& u)
{
  Vector<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = -u[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S> operator-(const Vector<T, S>& u, const Vector<T, S>& v)
{
  Vector<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = u[i] - v[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S> operator-(const Point<T, S>& p1, const Point<T, S>& p2)
{
  Vector<T, S> result;
  for (unsigned i = 0; i < S; ++i)
    result[i] = p1[i] - p2[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S>& operator+=(Vector<T, S>& u, const Vector<T, S>& v)
{
  for (unsigned i = 0; i < S; ++i)
    u[i] += v[i];
  return u;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S>& operator-=(Vector<T, S>& u, const Vector<T, S>& v)
{
  for (unsigned i = 0; i < S; ++i)
    u[i] -= v[i];
  return u;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S>& operator*=(Vector<T, S>& u, const T& k)
{
  for (unsigned i = 0; i < S; ++i)
    u[i] *= k;
  return u;
}

/*! \brief
 *  \relates Vector
 */
template<typename T, unsigned S>
Vector<T, S>& operator/=(Vector<T, S>& u, const T& k)
{
  for (unsigned i = 0; i < S; ++i)
    u[i] /= k;
  return u;
}

/*! \class Vector2
 *  \brief
 */

// --- Construction

template<typename T>
Vector2<T>::Vector2()
{
}

template<typename T>
Vector2<T>::Vector2(const T& vx, const T& vy)
{
  Super_t::m_vector[0] = vx;
  Super_t::m_vector[1] = vy;
}

template<typename T>
Vector2<T>::Vector2(const Super_t& other)
  : Super_t(other)
{
}

// --- Access

template<typename T>
const T& Vector2<T>::x() const
{
  return Super_t::m_vector[0];
}


template<typename T>
const T& Vector2<T>::y() const
{
  return Super_t::m_vector[1];
}

template<typename T>
const T& Vector2<T>::theta() const
{
  return Super_t::m_vector[1];
}

// --- Element change

template<typename T>
Vector2<T>& Vector2<T>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename T>
void Vector2<T>::setX(const T& v)
{
  Super_t::m_vector[0] = v;
}

template<typename T>
void Vector2<T>::setY(const T& v)
{
  Super_t::m_vector[1] = v;
}

template<typename T>
void Vector2<T>::setTheta(const T& v)
{
  Super_t::m_vector[1] = v;
}

template<typename T>
void Vector2<T>::setXy(const T& vx, const T& vy)
{
  Super_t::m_vector[0] = vx;
  Super_t::m_vector[1] = vy;
}

template<typename T>
T angle2(const Vector<T, 2>& v1, const Vector<T, 2>& v2)
{
  const Vector<T, 2> nv1(v1.normalized());
  const Vector<T, 2> nv2(v2.normalized());
  const double cosinus = nv1 * nv2;
  const double sinus = nv1[0] * nv2[1] - nv1[1] * nv2[0];
  if (cosinus > -math::pi / 4. && cosinus < math::pi / 4.) {
    return sinus > 0. ? std::acos(cosinus) : -std::acos(cosinus);
  }
  else {
    if (cosinus > 0.) {
      return std::asin(sinus);
    }
    else {
      if (sinus > 0.)
        return math::pi - std::asin(sinus);
      else
        return -math::pi - std::asin(sinus);
    }
  }
}

/*! \class Vector3
 *  \brief
 */

// --- Construction

template<typename T>
Vector3<T>::Vector3()
{
}

template<typename T>
Vector3<T>::Vector3(const T& vx, const T& vy, const T& vz)
{
  Super_t::m_vector[0] = vx;
  Super_t::m_vector[1] = vy;
  Super_t::m_vector[2] = vz;
}

template<typename T>
Vector3<T>::Vector3(const Super_t& other)
  : Super_t(other)
{
}

// --- Access

template<typename T>
const T& Vector3<T>::x() const
{
  return Super_t::m_vector[0];
}

template<typename T>
const T& Vector3<T>::y() const
{
  return Super_t::m_vector[1];
}

template<typename T>
const T& Vector3<T>::z() const
{
  return Super_t::m_vector[2];
}

// --- Element change

template<typename T>
Vector3<T>& Vector3<T>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename T>
void Vector3<T>::setX(const T& v)
{
  Super_t::m_vector[0] = v;
}

template<typename T>
void Vector3<T>::setY(const T& v)
{
  Super_t::m_vector[1] = v;
}

template<typename T>
void Vector3<T>::setZ(const T& v)
{
  Super_t::m_vector[2] = v;
}

template<typename T>
void Vector3<T>::setXyz(const T& vx, const T& vy, const T& vz)
{
  Super_t::m_vector[0] = vx;
  Super_t::m_vector[1] = vy;
  Super_t::m_vector[2] = vz;
}

template<typename T>
T angle3(const Vector<T, 3>& v1, const Vector<T, 3>& v2)
{
  const Vector<T, 3> nv1(v1.normalized());
  const Vector<T, 3> nv2(v2.normalized());
  const double cosinus = nv1 * nv2;
  if (cosinus > -math::pi / 4. && cosinus < math::pi / 4.) {
    return std::acos(cosinus);
  }
  else {
    const double sinus = (nv1 ^ nv2).norm();
    if (cosinus < 0.)
      return math::pi - std::asin(sinus);
    else
      return std::asin(sinus);
  }
}

/*! \brief Cross product of vectors \p v1 and \p v2 i.e. v1 ^ v2.
 *  \relates Vector3
 */
template<typename T>
Vector<T, 3> operator^(const Vector<T, 3>& v1, const Vector<T, 3>& v2)
{
  Vector<T, 3> result;
  result[0] = v1[1] * v2[2] - v1[2] * v2[1];
  result[1] = v1[2] * v2[0] - v1[0] * v2[2];
  result[2] = v1[0] * v2[1] - v1[1] * v2[0];
  return result;
}

// ---
// --- PntVecTraits
// ---

template<typename T>
void PntVecTraits< geom::Point3<T>, geom::Vector3<T> >::normalize(geom::Vector3<T>* v)
{
  assert(v != 0);
  v->normalize();
}

template<typename T>
geom::Vector3<T> PntVecTraits< geom::Point3<T>, geom::Vector3<T> >::cross(const geom::Vector3<T>& u,
                                                                          const geom::Vector3<T>& v)
{
  return u ^ v;
}

template<typename T>
T PntVecTraits< geom::Point3<T>, geom::Vector3<T> >::dot(const geom::Vector3<T>& u,
                                                         const geom::Vector3<T>& v)
{
  return u * v;
}

template<typename T>
geom::Point3<T> PntVecTraits< geom::Point3<T>, geom::Vector3<T> >::translate(const geom::Point3<T>& p,
                                                                             const geom::Vector3<T>& v)
{
  return p + v;
}

template<typename T>
geom::Vector3<T> PntVecTraits< geom::Point3<T>, geom::Vector3<T> >::vector(const geom::Point3<T>& p1,
                                                                           const geom::Point3<T>& p2)
{
  return Vec_t(p2.x() - p1.x(), p2.y() - p1.y(), p2.z() - p1.z());
}

template<typename T>
geom::Vector3<T> PntVecTraits< geom::Point3<T>, geom::Vector3<T> >::vector(const Pnt_t& p)
{
  return Vec_t(p.x(), p.y(), p.z());
}

template<typename T>
geom::Vector3<T> PntVecTraits< geom::Point3<T>, geom::Vector3<T> >::mult(Value_t k, const Vec_t& v)
{
  return k * v;
}

#endif // BITS_GEOM_POINT_VECTOR_H

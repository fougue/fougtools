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

/*! \class Point
 *  \brief
 */

// --- Construction

template<typename _T_, unsigned _S_>
Point<_T_, _S_>::Point()
{
}

template<typename _T_, unsigned _S_>
Point<_T_, _S_>::Point(const Self_t& other) :
    Super_t(other)
{
}

// --- Element change

template<typename _T_, unsigned _S_>
Point<_T_, _S_>& Point<_T_, _S_>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

//! Synonym to distL2()
template<typename _T_, unsigned _S_>
_T_ Point<_T_, _S_>::dist(const Self_t& other) const
{
  return this->distL2(other);
}

//! Synonym to distL2Square()
template<typename _T_, unsigned _S_>
_T_ Point<_T_, _S_>::distSquare(const Self_t& other) const
{
  return this->distL2Square(other);
}

//! Euclidian distance
template<typename _T_, unsigned _S_>
_T_ Point<_T_, _S_>::distL2(const Self_t& other) const
{
  return static_cast<_T_>(std::sqrt(this->distL2Square(other)));
}

//! Squared euclidian distance
template<typename _T_, unsigned _S_>
_T_ Point<_T_, _S_>::distL2Square(const Self_t& other) const
{
  _T_ result = static_cast<_T_>(0);
  for (unsigned i = 0; i < _S_; i++)
  {
    _T_ d = this->_vector[i] - other[i];
    result += d * d;
  }
  assert(result >= 0 && "positive_distance");
  return result;
}

/*! \brief
 *  \relates Point
 */
template<typename _T_, unsigned _S_>
Point<_T_, _S_> operator-(const Point<_T_, _S_>& p)
{
  Point<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = -p[i];
  return result;
}

/*! \class Point2
 *  \brief
 */

// --- Construction

template<typename _T_>
Point2<_T_>::Point2()
{
}

template<typename _T_>
Point2<_T_>::Point2(const _T_& vx, const _T_& vy)
{
  this->_vector[0] = vx;
  this->_vector[1] = vy;
}

template<typename _T_>
Point2<_T_>::Point2(const Super_t& other) :
    Super_t(other)
{
}

// --- Access

template<typename _T_>
const _T_& Point2<_T_>::x() const
{
  return this->_vector[0];
}


template<typename _T_>
const _T_& Point2<_T_>::y() const
{
  return this->_vector[1];
}

template<typename _T_>
const _T_& Point2<_T_>::theta() const
{
  return this->_vector[1];
}

// --- Element change

template<typename _T_>
Point2<_T_>& Point2<_T_>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename _T_>
void Point2<_T_>::setX(const _T_& v)
{
  this->_vector[0] = v;
}

template<typename _T_>
void Point2<_T_>::setY(const _T_& v)
{
  this->_vector[1] = v;
}

template<typename _T_>
void Point2<_T_>::setTheta(const _T_& v)
{
  this->_vector[1] = v;
}

template<typename _T_>
void Point2<_T_>::setXy(const _T_& vx, const _T_& vy)
{
  this->_vector[0] = vx;
  this->_vector[1] = vy;
}

/*! \class Point3
 *  \brief 
 */

// --- Construction

template<typename _T_>
Point3<_T_>::Point3()
{
}

template<typename _T_>
Point3<_T_>::Point3(const _T_& vx, const _T_& vy, const _T_& vz)
{
  this->_vector[0] = vx;
  this->_vector[1] = vy;
  this->_vector[2] = vz;
}

template<typename _T_>
Point3<_T_>::Point3(const Super_t& other) :
    Super_t(other)
{
}

// --- Access

template<typename _T_>
const _T_& Point3<_T_>::x() const
{
  return this->_vector[0];
}

template<typename _T_>
const _T_& Point3<_T_>::y() const
{
  return this->_vector[1];
}

template<typename _T_>
const _T_& Point3<_T_>::z() const
{
  return this->_vector[2];
}

// --- Element change

template<typename _T_>
Point3<_T_>& Point3<_T_>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename _T_>
void Point3<_T_>::setX(const _T_& v)
{
  this->_vector[0] = v;
}

template<typename _T_>
void Point3<_T_>::setY(const _T_& v)
{
  this->_vector[1] = v;
}

template<typename _T_>
void Point3<_T_>::setZ(const _T_& v)
{
  this->_vector[2] = v;
}

template<typename _T_>
void Point3<_T_>::setXyz(const _T_& vx, const _T_& vy, const _T_& vz)
{
  this->_vector[0] = vx;
  this->_vector[1] = vy;
  this->_vector[2] = vz;
}

/*! \class Vector
 *  \brief 
 */

// --- Construction

template<typename _T_, unsigned _S_>
Vector<_T_, _S_>::Vector()
{
}

template<typename _T_, unsigned _S_>
Vector<_T_, _S_>::Vector(const Self_t& other) :
    Super_t(other)
{
}

template<typename _T_, unsigned _S_>
const Vector<_T_, _S_> Vector<_T_, _S_>::normalized() const
{
  return *this / this->norm();
}

// --- Measurement

template<typename _T_, unsigned _S_>
bool Vector<_T_, _S_>::isNull(const _T_& tol) const
{
  return this->squareNorm() < tol;
}

template<typename _T_, unsigned _S_>
_T_ Vector<_T_, _S_>::norm() const
{
  return std::sqrt(this->squareNorm());
}

template<typename _T_, unsigned _S_>
_T_ Vector<_T_, _S_>::squareNorm() const
{
  _T_ result = static_cast<_T_>(0);
  for (unsigned i = 0; i < _S_; ++i)
    result += this->_vector[i] * this->_vector[i];
  return result;
}

// --- Element change

template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& Vector<_T_, _S_>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename _T_, unsigned _S_>
void Vector<_T_, _S_>::normalize()
{
  const _T_ n = this->norm();
  for (unsigned i = 0; i < _S_; ++i)
    this->_vector[i] /= n;
}

template<typename _T_, unsigned _S_>
void Vector<_T_, _S_>::reverse()
{
  for (unsigned i = 0; i < _S_; ++i)
    this->_vector[i] = -this->_vector[i];
}


/*! \brief Vector \p u multiplied by scalar \p k
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator*(const Vector<_T_, _S_>& u, const _T_& k)
{
  Vector<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = k * u[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator*(const _T_& k, const Vector<_T_, _S_>& u)
{
  return u * k;
}

/*! \brief Vector \p u divided by scalar \p k
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator/(const Vector<_T_, _S_>& u, const _T_& k)
{
  Vector<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = u[i] / k;
  return result;
}

/*! \brief Scalar product of vectors \p u and \p v i.e. <u|v>
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
_T_ operator*(const Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v)
{
  _T_ result = static_cast<_T_>(0);
  for (unsigned i = 0; i < _S_; ++i)
    result += u[i] * v[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator+(const Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v)
{
  Vector<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = u[i] + v[i];
  return result;
}

/*! \brief Point \p p translated by vector \p v
 *  \relates Point
 */
template<typename _T_, unsigned _S_>
Point<_T_, _S_> operator+(const Point<_T_, _S_>& p, const Vector<_T_, _S_>& v)
{
  Point<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = p[i] + v[i];
  return result;
}

/*! \brief Point \p p translated by vector \p v
 *  \relates Point
 */
template<typename _T_, unsigned _S_>
Point<_T_, _S_> operator-(const Point<_T_, _S_>& p, const Vector<_T_, _S_>& v)
{
  Point<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = p[i] - v[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator-(const Vector<_T_, _S_>& u)
{
  Vector<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = -u[i];
  return result; 
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator-(const Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v)
{
  Vector<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = u[i] - v[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_> operator-(const Point<_T_, _S_>& p1, const Point<_T_, _S_>& p2)
{
  Vector<_T_, _S_> result;
  for (unsigned i = 0; i < _S_; ++i)
    result[i] = p1[i] - p2[i];
  return result;
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& operator+=(Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v)
{
  for (unsigned i = 0; i < _S_; ++i)
    u[i] += v[i];
  return u;
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& operator-=(Vector<_T_, _S_>& u, const Vector<_T_, _S_>& v)
{
  for (unsigned i = 0; i < _S_; ++i)
    u[i] -= v[i];
  return u;
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& operator*=(Vector<_T_, _S_>& u, const _T_& k)
{
  for (unsigned i = 0; i < _S_; ++i)
    u[i] *= k;
  return u;
}

/*! \brief
 *  \relates Vector
 */
template<typename _T_, unsigned _S_>
Vector<_T_, _S_>& operator/=(Vector<_T_, _S_>& u, const _T_& k)
{
  for (unsigned i = 0; i < _S_; ++i)
    u[i] /= k;
  return u;
}

/*! \class Vector2
 *  \brief 
 */

// --- Construction

template<typename _T_>
Vector2<_T_>::Vector2()
{
}

template<typename _T_>
Vector2<_T_>::Vector2(const _T_& vx, const _T_& vy)
{
  this->_vector[0] = vx;
  this->_vector[1] = vy;
}

template<typename _T_>
Vector2<_T_>::Vector2(const Super_t& other) :
    Super_t(other)
{
}

// --- Access

template<typename _T_>
const _T_& Vector2<_T_>::x() const
{
  return this->_vector[0];
}


template<typename _T_>
const _T_& Vector2<_T_>::y() const
{
  return this->_vector[1];
}

template<typename _T_>
const _T_& Vector2<_T_>::theta() const
{
  return this->_vector[1];
}

// --- Element change

template<typename _T_>
Vector2<_T_>& Vector2<_T_>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename _T_>
void Vector2<_T_>::setX(const _T_& v)
{
  this->_vector[0] = v;
}

template<typename _T_>
void Vector2<_T_>::setY(const _T_& v)
{
  this->_vector[1] = v;
}

template<typename _T_>
void Vector2<_T_>::setTheta(const _T_& v)
{
  this->_vector[1] = v;
}

template<typename _T_>
void Vector2<_T_>::setXy(const _T_& vx, const _T_& vy)
{
  this->_vector[0] = vx;
  this->_vector[1] = vy;
}

template<typename _T_>
_T_ angle2(const Vector<_T_, 2>& v1, const Vector<_T_, 2>& v2)
{
  const Vector<_T_, 2> nv1(v1.normalized());
  const Vector<_T_, 2> nv2(v2.normalized());
  const double cosinus = nv1 * nv2;
  const double sinus = nv1[0] * nv2[1] - nv1[1] * nv2[0];
  if (cosinus > -math::pi / 4. && cosinus < math::pi / 4.)
  {
    return sinus > 0. ? std::acos(cosinus) : -std::acos(cosinus);
  }
  else
  {
    if (cosinus > 0.)
      return std::asin(sinus);
    else
    {
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

template<typename _T_>
Vector3<_T_>::Vector3()
{
}

template<typename _T_>
Vector3<_T_>::Vector3(const _T_& vx, const _T_& vy, const _T_& vz)
{
  this->_vector[0] = vx;
  this->_vector[1] = vy;
  this->_vector[2] = vz;
}

template<typename _T_>
Vector3<_T_>::Vector3(const Super_t& other) :
    Super_t(other)
{
}

// --- Access

template<typename _T_>
const _T_& Vector3<_T_>::x() const
{
  return this->_vector[0];
}

template<typename _T_>
const _T_& Vector3<_T_>::y() const
{
  return this->_vector[1];
}

template<typename _T_>
const _T_& Vector3<_T_>::z() const
{
  return this->_vector[2];
}

// --- Element change

template<typename _T_>
Vector3<_T_>& Vector3<_T_>::operator=(const Self_t & other)
{
  Super_t::operator=(other);
  return *this;
}

template<typename _T_>
void Vector3<_T_>::setX(const _T_& v)
{
  this->_vector[0] = v;
}

template<typename _T_>
void Vector3<_T_>::setY(const _T_& v)
{
  this->_vector[1] = v;
}

template<typename _T_>
void Vector3<_T_>::setZ(const _T_& v)
{
  this->_vector[2] = v;
}

template<typename _T_>
void Vector3<_T_>::setXyz(const _T_& vx, const _T_& vy, const _T_& vz)
{
  this->_vector[0] = vx;
  this->_vector[1] = vy;
  this->_vector[2] = vz;
}

template<typename _T_>
_T_ angle3(const Vector<_T_, 3>& v1, const Vector<_T_, 3>& v2)
{
  const Vector<_T_, 3> nv1(v1.normalized());
  const Vector<_T_, 3> nv2(v2.normalized());
  const double cosinus = nv1 * nv2;
  if (cosinus > -math::pi / 4. && cosinus < math::pi / 4.)
  {
    return std::acos(cosinus);
  }
  else
  {
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
template<typename _T_>
Vector<_T_, 3> operator^(const Vector<_T_, 3>& v1, const Vector<_T_, 3>& v2)
{
  Vector<_T_, 3> result;
  result[0] = v1[1] * v2[2] - v1[2] * v2[1];
  result[1] = v1[2] * v2[0] - v1[0] * v2[2];
  result[2] = v1[0] * v2[1] - v1[1] * v2[0];
  return result;
}

// ---
// --- PntVecTraits
// ---

template<typename _T_>
void PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >::normalize(
  geom::Vector3<_T_>* v)
{
  assert(v != 0);
  v->normalize();
}

template<typename _T_>
geom::Vector3<_T_> PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >
  ::cross(const geom::Vector3<_T_>& u, const geom::Vector3<_T_>& v)
{
  return u ^ v;
}

template<typename _T_>
_T_ PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >::dot(
  const geom::Vector3<_T_>& u, const geom::Vector3<_T_>& v)
{
  return u * v;
}

template<typename _T_>
geom::Point3<_T_> PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >::
  translate(const geom::Point3<_T_>& p, const geom::Vector3<_T_>& v)
{
  return p + v;
}

template<typename _T_>
geom::Vector3<_T_> PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >::
  vector(const geom::Point3<_T_>& p1, const geom::Point3<_T_>& p2)
{
  return Vec_t(p2.x() - p1.x(), p2.y() - p1.y(), p2.z() - p1.z());
}

template<typename _T_>
geom::Vector3<_T_> PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >::
  vector(const Pnt_t& p)
{
 return Vec_t(p.x(), p.y(), p.z());
}

template<typename _T_>
geom::Vector3<_T_> PntVecTraits< geom::Point3<_T_>, geom::Vector3<_T_> >::
  mult(Value_t k, const Vec_t& v)
{
 return k * v;
}

#endif // BITS_GEOM_POINT_VECTOR_H

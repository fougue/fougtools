
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

#ifdef BITS_GEOM_TRANSFORMATION_H

// ---
// --- Transformation
// ---

// --- Construction

template<typename T, unsigned SIZE>
Transformation<T, SIZE>::Transformation()
{
  this->makeIdentity();
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>::Transformation(const T* m)
{
  this->set(m);
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>::Transformation(const Transformation<T, SIZE>& m)
{
  this->set(m);
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>& Transformation<T, SIZE>::makeIdentity()
{
  for (unsigned iCol = 0; iCol < SIZE + 1; ++iCol)
  {
    std::fill(this->_m[iCol].begin(), this->_m[iCol].end(),
              static_cast<T>(0));
    this->_m[iCol][iCol] = static_cast<T>(1);
  }
  return *this;
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::makeTranslation(const Vector<T, SIZE>& dv)
{
  this->makeIdentity();
  std::copy(dv.begin(), dv.end(), this->_m[SIZE].begin());
  return *this;
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::makeScaling(const Vector<T, SIZE>& scaleFactors)
{
  this->makeIdentity();
  for (unsigned i = 0; i < SIZE; ++i)
    this->_m[i][i] = scaleFactors[i];
  return *this;
}

// --- Element change

template<typename T, unsigned SIZE>
void Transformation<T, SIZE>::fill(const T& val)
{
  for (unsigned iCol = 0; iCol < SIZE + 1; ++iCol)
    std::fill(this->_m[iCol].begin(), this->_m[iCol].end(), val);
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::set(unsigned col, unsigned row, const T& val)
{
  this->_m[col][row] = val;
  return *this;
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::set(const T* m)
{
  if (m != 0)
  {
    for (unsigned iCol = 0; iCol < SIZE + 1; ++iCol)
      std::copy(m + (iCol * (SIZE + 1)),
                m + (iCol * (SIZE + 1)) + SIZE + 1, this->_m[iCol].begin());
  }
  return *this;
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::set(const Transformation<T, SIZE>& m)
{
  for (unsigned iCol = 0; iCol < SIZE + 1; ++iCol)
    std::copy(m[iCol].begin(), m[iCol].end(), this->_m[iCol].begin());
  return *this;
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::operator=(const Transformation<T, SIZE>& m)
{
  return this->set(m);
}

// --- Operations

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::composeBy(const Transformation<T, SIZE>& m)
{
  Transformation<T, SIZE> tmp(*this);
  for (unsigned iRow = 0; iRow < SIZE + 1; ++iRow)
  {
    for (unsigned iCol = 0; iCol < SIZE + 1; ++iCol)
    {
      this->_m[iCol][iRow] = static_cast<T>(0);
      for (unsigned k = 0; k < SIZE + 1; ++k)
        this->_m[iCol][iRow] += m[k][iRow] * tmp[iCol][k];
    }
  }
  return *this;
}

template<typename T, unsigned SIZE>
void
Transformation<T, SIZE>::compose(const Transformation<T, SIZE>& m,
                                     Transformation<T, SIZE>& to) const
{
  for (unsigned iRow = 0; iRow < SIZE + 1; ++iRow)
  {
    for (unsigned iCol = 0; iCol < SIZE + 1; ++iCol)
    {
      to[iCol][iRow] = static_cast<T>(0);
      for (unsigned k = 0; k < SIZE + 1; ++k)
        to[iCol][iRow] += m[k][iRow] * this->_m[iCol][k];
    }
  }
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::translate(const Vector<T, SIZE>& dv)
{
  for (unsigned iRow = 0; iRow < SIZE; ++iRow)
    this->_m[SIZE][iRow] += dv[iRow];
  return *this;
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::scale(const Vector<T, SIZE>& scaleFactors)
{
  for (unsigned i = 0; i < SIZE; ++i)
    this->_m[i] *= scaleFactors[i];
  return *this;
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::setTranslation(const Vector<T, SIZE>& pv)
{
  this->_m[SIZE].set(pv);
  return *this;
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::setAxis(int i, const Vector<T, SIZE>& pv)
{
  this->_m[i].set(pv);
  return *this;
}

template<typename T, unsigned SIZE>
void Transformation<T, SIZE>::applyOnPoint(Point<T, SIZE>& pv) const
{
  Point<T, SIZE> tmp = pv;
  for (unsigned iRow = 0; iRow < SIZE; ++iRow)
  {
    pv[iRow] = this->_m[SIZE][iRow];
    for (unsigned iCol = 0; iCol < SIZE; ++iCol)
      pv[iRow] += this->_m[iCol][iRow] * tmp[iCol];
  }
}

template<typename T, unsigned SIZE>
void Transformation<T, SIZE>::applyOnPoint(
  const Point<T, SIZE>& pv,
  Point<T, SIZE>& to) const
{
  for (unsigned iRow = 0; iRow < SIZE; ++iRow)
  {
    to[iRow] = this->_m[SIZE][iRow];
    for (unsigned iCol = 0; iCol < SIZE; ++iCol)
      to[iRow] += this->_m[iCol][iRow] * pv[iCol];
  }
}

template<typename T, unsigned SIZE>
void Transformation<T, SIZE>::applyOnVector(Vector<T, SIZE>& pv) const
{
  Vector<T, SIZE> tmp = pv;
  for (unsigned iRow = 0; iRow < SIZE; ++iRow)
  {
    pv[iRow] = static_cast<T>(0);
    for (unsigned iCol = 0; iCol < SIZE; ++iCol)
      pv[iRow] += this->_m[iCol][iRow] * tmp[iCol];
  }
}

template<typename T, unsigned SIZE>
void Transformation<T, SIZE>::applyOnVector(
  const Vector<T, SIZE>& pv,
  Vector<T, SIZE>& to) const
{
  Vector<T, SIZE> tmp = pv;
  for (unsigned iRow = 0; iRow < SIZE; ++iRow)
  {
    to[iRow] = static_cast<T>(0);
    for (unsigned iCol = 0; iCol < SIZE; ++iCol)
      to[iRow] += this->_m[iCol][iRow] * pv[iCol];
  }
}

template<typename T, unsigned SIZE>
Transformation<T, SIZE>&
Transformation<T, SIZE>::operator*=(const Transformation<T, SIZE>& m)
{
  return this->composeBy(m);
}

// --- Access

template<typename T, unsigned SIZE>
const T& Transformation<T, SIZE>::get(unsigned col, unsigned row) const
{
  return this->_m[col][row];
}

template<typename T, unsigned SIZE>
T& Transformation<T, SIZE>::get(unsigned col, unsigned row)
{
  return this->_m[col][row];
}

template<typename T, unsigned SIZE>
const Vector<T, SIZE + 1>&
Transformation<T, SIZE>::operator[](unsigned col) const
{
  return this->_m[col];
}

template<typename T, unsigned SIZE>
Vector<T, SIZE + 1>& Transformation<T, SIZE>::operator[](unsigned col)
{
  return this->_m[col];
}

template<typename T, unsigned SIZE>
const T&
Transformation<T, SIZE>::operator()(unsigned col, unsigned row) const
{
  return this->get(col, row);
}

template<typename T, unsigned SIZE>
T& Transformation<T, SIZE>::operator()(unsigned col, unsigned row)
{
  return this->get(col, row);
}

template<typename T, unsigned SIZE>
Vector<T, SIZE> Transformation<T, SIZE>::translation() const
{
  return this->axis(SIZE);
}

template<typename T, unsigned SIZE>
Vector<T, SIZE> Transformation<T, SIZE>::axis(int i) const
{
  Vector<T, SIZE> v;
  std::copy(this->_m[i].begin(), this->_m[i].begin() + SIZE,
            v.begin());
  return v;
}

template<typename T, unsigned SIZE>
const T* Transformation<T, SIZE>::cArray() const
{
  return this->_m[0].begin();
}

template<typename T, unsigned SIZE>
T* Transformation<T, SIZE>::cArray()
{
  return this->_m[0].begin();
}

// --- Status report

template<typename T, unsigned SIZE>
bool Transformation<T, SIZE>::isIdentity(const T& tol) const
{
  for (unsigned iCol = 0; iCol < SIZE + 1; ++iCol)
  {
    for (unsigned iRow = 0; iRow < SIZE + 1; ++iRow)
    {
      if (iCol == iRow)
      {
        if (std::abs(this->_m[iCol][iRow] - 1.) > tol)
          return false;
      }
      else
      {
        if (std::abs(this->_m[iCol][iRow]) > tol)
          return false;
      }
    }
  }
  return true;
}

template<typename T, unsigned SIZE>
bool Transformation<T, SIZE>::isTranslation(const T& tol) const
{
  for (unsigned iCol = 0; iCol < SIZE; ++iCol)
  {
    for (unsigned iRow = 0; iRow < SIZE + 1; ++iRow)
    {
      if (iCol == iRow)
      {
        if (std::abs(this->_m[iCol][iRow] - 1.) > tol)
          return false;
      }
      else
      {
        if (std::abs(this->_m[iCol][iRow]) > tol)
          return false;
      }
    }
  }
  return (std::abs(this->_m[SIZE][SIZE] - 1.) < tol);
}

template<typename T, unsigned SIZE>
bool Transformation<T, SIZE>::isScaling(const T& tol) const
{
  for (unsigned iCol = 0; iCol < SIZE + 1; ++iCol)
  {
    for (unsigned iRow = 0; iRow < SIZE + 1; ++iRow)
    {
      if (iCol != iRow)
      {
        if (std::abs(this->_m[iCol][iRow]) > tol)
          return false;
      }
    }
  }
  return true;
}

// ---
// --- Related functions
// ---

template<typename T, unsigned SIZE>
const Transformation<T, SIZE> operator*(
  const Transformation<T, SIZE>& m1,
  const Transformation<T, SIZE>& m2)
{
  Transformation<T, SIZE> m(m2);
  return m.composeBy(m1);
}

template<typename T, unsigned SIZE>
Point<T, SIZE> operator*(const Transformation<T, SIZE>& m,
                             const Point<T, SIZE>& pt)
{
  Point<T, SIZE> p;
  m.applyOnPoint(pt, p);
  return p;
}

template<typename T, unsigned SIZE>
Vector<T, SIZE> operator*(const Transformation<T, SIZE>& m,
                              const Vector<T, SIZE>& v)
{
  Vector<T, SIZE> vec;
  m.applyOnVector(v, vec);
  return vec;
}

// ---
// --- Transformation2
// ---

// --- Construction

template<typename T>
Transformation2<T>::Transformation2() :
    Transformation<T, 2>()
{
}

template<typename T>
Transformation2<T>::Transformation2(const T* m) :
    Transformation<T, 2>(m)
{
}

template<typename T>
Transformation2<T>::Transformation2(const Transformation<T, 2>& m) :
    Transformation<T, 2>(m)
{
}

template<typename T>
Transformation2<T>::Transformation2(const Vector2<T>& v1,
                                      const Vector2<T>& v2,
                                      const Vector2<T>& t) :
    Transformation<T, 2>()
{
  this->_m[0].set(v1);
  this->_m[1].set(v1);
  this->_m[2].set(t);
}

template<typename T>
Transformation2<T>::Transformation2(
    const T& m11, const T& m21, const T& m31,
    const T& m12, const T& m22, const T& m32,
    const T& m13, const T& m23, const T& m33)
{
  this->_m[0].set(Vector3<T>(m11, m12, m13));
  this->_m[1].set(Vector3<T>(m21, m22, m23));
  this->_m[2].set(Vector3<T>(m31, m32, m33));
}

template<typename T>
Transformation2<T>& Transformation2<T>::makeRotation(const T& angle)
{
  const T c = std::cos(angle);
  const T s = std::sin(angle);
  this->_m[0][0] = c;
  this->_m[0][1] = s;
  this->_m[0][2] = static_cast<T>(0);;
  this->_m[1][0] = -s;
  this->_m[1][1] = c;
  this->_m[1][2] = static_cast<T>(0);;
  this->_m[2][0] = static_cast<T>(0);;
  this->_m[2][1] = static_cast<T>(0);;
  this->_m[2][2] = static_cast<T>(1);;
  return *this;
}

template<typename T>
Transformation2<T>& Transformation2<T>::makeRotation(
    const Vector2<T>& axis, const T& angle)
{
  const T c = std::cos(angle);
  const T s = std::sin(angle);
  this->_m[0][0] = c;
  this->_m[0][1] = s;
  this->_m[0][2] = 0.;
  this->_m[1][0] = -s;
  this->_m[1][1] = c;
  this->_m[1][2] = 0.;
  this->_m[2][0] = (1. - c) * axis.x() + s * axis.y();
  this->_m[2][1] = -s * axis.x() + (1. - c) * axis.y();
  this->_m[2][2] = 1.;
  return *this;
}

// --- Status report

template<typename T>
bool Transformation2<T>::isRotation(const T& tol) const
{
  const T& a = this->_m[0][0];
  const T& b = this->_m[0][1];
  const T& c = this->_m[1][0];
  const T& d = this->_m[1][1];

  if (std::abs(a * c  + b * d) > tol) // not orthogonal?
    return false;
  if (std::abs((a * d - b * c) - 1.) > tol) // det /= 1?
    return false;
  return
    std::abs(this->_m[2][0]) <= tol && std::abs(this->_m[2][1]) <= tol; // no translation
}

/*! \class Transformation3
 *  \brief 
 */

// --- Construction

template<typename T>
Transformation3<T>::Transformation3()  :
    Transformation<T, 3>()
{
}

template<typename T>
Transformation3<T>::Transformation3(const T* m) :
    Transformation<T, 3>(m)
{
}

template<typename T>
Transformation3<T>::Transformation3(const Transformation<T, 3>& m) :
    Transformation<T, 3>(m)
{
}

template<typename T>
Transformation3<T>::Transformation3(const Vector3<T>& v1,
                                      const Vector3<T>& v2,
                                      const Vector3<T>& v3,
                                      const Vector3<T>& t) :
    Transformation<T, 3>()
{
  this->_m[0].set(v1);
  this->_m[1].set(v2);
  this->_m[2].set(v3);
  this->_m[3].set(t);
}

template<typename T>
Transformation3<T>::Transformation3(
    const T& m11, const T& m21, const T& m31, const T& m41,
    const T& m12, const T& m22, const T& m32, const T& m42,
    const T& m13, const T& m23, const T& m33, const T& m43,
    const T& m14, const T& m24, const T& m34, const T& m44) :
    Transformation<T, 3>()
{
  this->_m[0][0] = m11;
  this->_m[0][1] = m12;
  this->_m[0][2] = m13;
  this->_m[0][3] = m14;

  this->_m[1][0] = m21;
  this->_m[1][1] = m22;
  this->_m[1][2] = m23;
  this->_m[1][3] = m24;

  this->_m[2][0] = m31;
  this->_m[2][1] = m32;
  this->_m[2][2] = m33;
  this->_m[2][3] = m34;

  this->_m[3][0] = m41;
  this->_m[3][1] = m42;
  this->_m[3][2] = m43;
  this->_m[3][3] = m44;
}

template<typename T>
Transformation3<T>&
Transformation3<T>::makeRotation(const Vector3<T>& axis, const T& angle)
{
  const T c = std::cos(angle);
  const T s = std::sin(angle);
  const T t = 1. - c;
  const T sx = s * axis.x();
  const T sy = s * axis.y();
  const T sz = s * axis.z();
  const T tx = t * axis.x();
  const T ty = t * axis.y();
  const T tz = t * axis.z();

  this->_m[0][0] = tx * axis.x() + c;
  this->_m[0][1] = tx * axis.y() + sz;
  this->_m[0][2] = tx * axis.z() - sy;
  this->_m[0][3] = static_cast<T>(0);

  this->_m[1][0] = ty * axis.x() - sz;
  this->_m[1][1] = ty * axis.y() + c;
  this->_m[1][2] = ty * axis.z() + sx;
  this->_m[1][3] = static_cast<T>(0);

  this->_m[2][0] = tz * axis.x() + sy;
  this->_m[2][1] = tz * axis.y() - sx;
  this->_m[2][2] = tz * axis.z() + c;
  this->_m[2][3] = static_cast<T>(0);

  this->_m[3][0] = this->_m[3][1] = this->_m[3][2] = static_cast<T>(0);
  this->_m[3][3] = static_cast<T>(1);
  return *this;
}

// --- Status report

template<typename T>
bool Transformation3<T>::isRotation(const T& tol) const
{
  const T d = static_cast<T>(0);
  for (unsigned iCol1 = 0; iCol1 < 3; ++iCol1)
  {
    for (unsigned iCol2 = 0; iCol2 < 3; ++iCol2)
    {
      if (iCol1 == iCol2)
      {
        if (std::abs(this->_m[iCol1].squareNorm() - 1.0) > tol)
          return false;
      }
      else
      {
        if (std::abs(this->_m[iCol1]*this->_m[iCol2]) > tol)
          return false;
      }
    }
  }
  for (unsigned iRow = 0; iRow < 3; ++iRow)
  {
    if (std::abs(this->_m[3][iRow]) > tol)
      return false;
  }
  return true;
}

// --- Operations

template<typename T>
Transformation3<T>&
Transformation3<T>::rotate(const Vector3<T>& axis, const T& angle)
{
  Transformation3<T> tmp;
  tmp.makeRotation(axis, angle);
  const Vector3<T> tr(this->translation());
  this->setTranslation(Vector3<T>(static_cast<T>(0),
                                    static_cast<T>(0),
                                    static_cast<T>(0)));
  this->composeBy(tmp);
  this->setTranslation(tr);
  return *this;
}

template<typename T>
void Transformation3<T>::invertTo(Transformation3<T>& to) const
{
  const Vector<T, 4>*const kM = this->_m;
  // transposed cofactors
  const T c00 = kM[1][1] * kM[2][2] - kM[2][1] * kM[1][2];
  const T c01 = kM[2][1] * kM[0][2] - kM[0][1] * kM[2][2];
  const T c02 = kM[0][1] * kM[1][2] - kM[1][1] * kM[0][2];
  const T c10 = kM[1][2] * kM[2][0] - kM[2][2] * kM[1][0];
  const T c11 = kM[2][2] * kM[0][0] - kM[0][2] * kM[2][0];
  const T c12 = kM[0][2] * kM[1][0] - kM[1][2] * kM[0][0];
  const T c20 = kM[1][0] * kM[2][1] - kM[2][0] * kM[1][1];
  const T c21 = kM[2][0] * kM[0][1] - kM[0][0] * kM[2][1];
  const T c22 = kM[0][0] * kM[1][1] - kM[1][0] * kM[0][1];
  const T d = kM[0][0] * c00 + kM[1][0] * c01 + kM[2][0] * c02;
  if (std::abs(d) < 1.e-10)
  {
    to.fill(static_cast<T>(0));
    return;
  }
  to[0][0] = c00 / d;
  to[0][1] = c01 / d;
  to[0][2] = c02 / d;
  to[0][3] = static_cast<T>(0);
  to[1][0] = c10 / d;
  to[1][1] = c11 / d;
  to[1][2] = c12 / d;
  to[1][3] = static_cast<T>(0);
  to[2][0] = c20 / d;
  to[2][1] = c21 / d;
  to[2][2] = c22 / d;
  to[2][3] = static_cast<T>(0);
  to[3][0] = -(kM[3][0] * c00 + kM[3][1] * c10 + kM[3][2] * c20) / d;
  to[3][1] = -(kM[3][0] * c01 + kM[3][1] * c11 + kM[3][2] * c21) / d;
  to[3][2] = -(kM[3][0] * c02 + kM[3][1] * c12 + kM[3][2] * c22) / d;
  to[3][3] = static_cast<T>(1);
}

template<typename T>
Transformation3<T>& Transformation3<T>::revertZ()
{
  this->_m[2] = -(this->_m[2]);
  this->_m[1] = -(this->_m[1]);
  return *this;
}

template<typename T>
Transformation3<T>& Transformation3<T>::defineZ(const Vector3<T>& zdir)
{
  Vector3<T> tmpZ(zdir.normalized());
  Vector3<T> xdir = this->axis(0);
  Vector3<T> ydir = this->axis(1);
  Vector3<T> tmpX = ydir ^ tmpZ;
  Vector3<T> tmpY = tmpZ ^ xdir;
  if (tmpX.squareNorm() > tmpY.squareNorm())
    tmpY = tmpZ ^ tmpX;
  else
    tmpX = tmpY ^ tmpZ;
  this->_m[0].set(tmpX);
  this->_m[1].set(tmpY);
  this->_m[2].set(tmpZ);
  return *this;
}

#endif // BITS_GEOM_TRANSFORMATION_H

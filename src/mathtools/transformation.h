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

#ifndef BITS_GEOM_TRANSFORMATION_H
#define BITS_GEOM_TRANSFORMATION_H

#include <cmath>
#include "point_vector.h"
#include "transformation_fwd.h"

namespace geom {

// ---
// --- Transformation
// ---
template<typename T, unsigned SIZE>
class Transformation
{
public:
  // --- Types definitions
  typedef Transformation<T, SIZE> Self_t;
  typedef Vector<T, SIZE + 1>     Column_t;
  typedef Vector<T, SIZE>         Vector_t;
  typedef Point<T, SIZE>          Point_t;

  // --- Construction
  Transformation();
  Transformation(const T* m);
  Transformation(const Self_t& m);

  Self_t& makeIdentity();
  Self_t& makeTranslation(const Vector_t& dv);
  Self_t& makeScaling(const Vector_t& scaleFactors);

  // --- Element change
  void fill(const T& val);
  Self_t& set(unsigned col, unsigned row, const T& val);
  Self_t& set(const T* m);
  Self_t& set(const Self_t& m);
  Self_t& operator=(const Self_t& m);

  // --- Operations
  Self_t& composeBy(const Self_t& m);
  void compose(const Self_t& m, Self_t& to) const;

  Self_t& translate(const Vector_t& dv);
  Self_t& scale(const Vector_t& scaleFactors);
  Self_t& setTranslation(const Vector_t& pv);
  Self_t& setAxis(int i, const Vector_t& pv);

  void applyOnPoint(Point_t& pv) const;
  void applyOnPoint(const Point_t& pv, Point_t& to) const;
  void applyOnVector(Vector_t& pv) const;
  void applyOnVector(const Vector_t& pv, Vector_t& to) const;

  Self_t& operator*=(const Self_t& m);

  // --- Access

  const T& get(unsigned col, unsigned row) const;
  T&       get(unsigned col, unsigned row);

  const Column_t& operator[](unsigned col) const;
  Column_t&       operator[](unsigned col);

  const T& operator()(unsigned col, unsigned row) const;
  T&       operator()(unsigned col, unsigned row);

  Vector_t translation() const;
  Vector_t axis(int i) const;

  const T* cArray() const;
  T* cArray();

  // --- Status report
  bool isIdentity(const T& tol = static_cast<T>(1e-6)) const;
  bool isTranslation(const T& tol = static_cast<T>(1e-6)) const;
  bool isScaling(const T& tol = static_cast<T>(1e-6)) const;

  // --- Attributes
protected:
  Column_t _m[SIZE + 1];
};

// ---
// --- Related functions
// ---
template<typename T, unsigned SIZE>
const Transformation<T, SIZE> operator*(const Transformation<T, SIZE>& m1,
                                        const Transformation<T, SIZE>& m2);
template<unsigned SIZE, class T>
Point<T, SIZE> operator*(const Transformation<T, SIZE>& m, const Point<T, SIZE>& pt);
template<unsigned SIZE, class T>
Vector<T, SIZE> operator*(const Transformation<T, SIZE>& m, const Vector<T, SIZE>& v);

// ---
// --- Transformation2
// ---
template<typename T>
class Transformation2 : public Transformation<T, 2>
{
public:
  // --- Construction
  Transformation2();
  Transformation2(const T* m);
  Transformation2(const Transformation<T, 2>& m);
  Transformation2(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& t);
  Transformation2(const T& m11, const T& m21, const T& m31,
                  const T& m12, const T& m22, const T& m32,
                  const T& m13, const T& m23, const T& m33);

  Transformation2<T>& makeRotation(const T& angle);
  Transformation2<T>& makeRotation(const Vector2<T>& around, const T& angle);

  // --- Status report
  bool isRotation(const T& tol = static_cast<T>(1e-6)) const;
};

// ---
// --- Transformation3
// ---
template<typename T>
class Transformation3 : public Transformation<T, 3>
{
public:
  // --- Construction
  Transformation3();
  Transformation3(const T* m);
  Transformation3(const Transformation<T, 3>& m);
  Transformation3(const Vector3<T>& v1, const Vector3<T>& v2, const Vector3<T>& v3,
                  const Vector3<T>& t);
  Transformation3(const T& m11, const T& m21, const T& m31, const T& m41,
                  const T& m12, const T& m22, const T& m32, const T& m42,
                  const T& m13, const T& m23, const T& m33, const T& m43,
                  const T& m14, const T& m24, const T& m34, const T& m44);

  Transformation3<T>& makeRotation(const Vector3<T>& axis, const T& angle);

  // --- Status report
  bool isRotation(const T& tol = static_cast<T>(1e-6)) const;

  // --- Operations
  Transformation3<T>& rotate(const Vector3<T>& axis,
                             const T& angle);
  Transformation3<T>& revertZ();
  Transformation3<T>& defineZ(const Vector3<T>& zdir);
  void invertTo(Transformation3<T>& to) const;
};

#include "transformation.impl.h"

} // namespace geom

#endif // BITS_GEOM_TRANSFORMATION_H

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

#ifndef BITS_MATH_UTILS_H
#define BITS_MATH_UTILS_H

#include <cmath>
#include <limits>
#include "consts.h"
#include "utils_helpers.h"

namespace math {

// ---- Types Definitions

enum ComparisonCheckFlags
{
  NoCheck = 0x1,
  InfinityCheck = 0x2,
  NanCheck = 0x4,
  SignCheck = 0x8,
  AllCheck = InfinityCheck | NanCheck | SignCheck
};

// ---- Comparison

template<typename T>
bool equalByAbsError(const T& a, const T& b,
                     const T& tol = static_cast<T>(1e-6));

template<typename T>
bool equalByRelError(const T& a, const T& b,
                     const T& maxRelError = static_cast<T>(1e-5),
                     const T& maxAbsError = std::numeric_limits<T>::epsilon());

template<typename T>
bool equalByIntDiff(const T& a, const T& b,
                    typename __impl::TypeTraits<T>::IntegralType_t maxDistInts = 10,
                    ComparisonCheckFlags checkFlags = NoCheck);

template<typename T>
const T& minimum(const T& a, const T& b);

template<typename T>
const T& maximum(const T& a, const T& b);

template<typename T, typename _LESS_THAN_>
const T& minimum(const T& a, const T& b, _LESS_THAN_ lessThan);

template<typename T, typename _LESS_THAN_>
const T& maximum(const T& a, const T& b, _LESS_THAN_ lessThan);

template<typename T>
T clamped(const T& v, const T& min, const T& max);

// ---- Conversion

template<typename T>
double radianToDegree(const T& angle);

template<typename T>
double degreeToRadian(const T& angle);

// ---- Misceallenous

template<typename T>
int sign(const T& v);

template<typename T>
T square(const T& x);

template<typename T>
T zero();

// ---- Status Report

template<typename T>
bool isPositive(const T& v);

template<typename T>
bool isNegative(const T& v);

//   inline const bool isInfinite(const float v);
//   inline const bool isNan(const float v);

#include "mathtools/utils.impl.h"

} // namespace math

#endif // BITS_MATH_UTILS_H

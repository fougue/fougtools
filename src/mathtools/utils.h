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
#include "mathtools/consts.h"
#include "mathtools/utils_helpers.h"

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

template<typename _T_>
bool equalByAbsError(const _T_& a, const _T_& b,
                     const _T_& tol = static_cast<_T_>(1e-6));

template<typename _T_>
bool equalByRelError(
    const _T_& a, const _T_& b,
    const _T_& maxRelError = static_cast<_T_>(1e-5),
    const _T_& maxAbsError = std::numeric_limits<_T_>::epsilon());

template<typename _T_>
bool equalByIntDiff(
    const _T_& a, const _T_& b,
    typename __impl::TypeTraits<_T_>::IntegralType_t maxDistInts = 10,
    ComparisonCheckFlags checkFlags = NoCheck);

template<typename _T_>
const _T_& minimum(const _T_& a, const _T_& b);

template<typename _T_>
const _T_& maximum(const _T_& a, const _T_& b);

template<typename _T_, typename _LESS_THAN_>
const _T_& minimum(const _T_& a, const _T_& b, _LESS_THAN_ lessThan);

template<typename _T_, typename _LESS_THAN_>
const _T_& maximum(const _T_& a, const _T_& b, _LESS_THAN_ lessThan);

template<typename _T_>
_T_ clamped(const _T_& v, const _T_& min, const _T_& max);

// ---- Conversion

template<typename _T_>
double radianToDegree(const _T_& angle);

template<typename _T_>
double degreeToRadian(const _T_& angle);

// ---- Misceallenous

template<typename _T_>
int sign(const _T_& v);

template<typename _T_>
_T_ square(const _T_& x);

template<typename _T_>
_T_ zero();

// ---- Status Report

template<typename _T_>
bool isPositive(const _T_& v);

template<typename _T_>
bool isNegative(const _T_& v);

//   inline const bool isInfinite(const float v);
//   inline const bool isNan(const float v);

#include "mathtools/utils.impl.h"

} // namespace math

#endif // BITS_MATH_UTILS_H

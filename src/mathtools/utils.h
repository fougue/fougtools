#ifndef BITS_MATH_UTILS_H
# define BITS_MATH_UTILS_H

# include <cmath>
# include <limits>
# include "mathtools/consts.h"
# include "mathtools/utils_helpers.h"

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

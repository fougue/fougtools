/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
****************************************************************************/

#ifndef MATHTOOLS_MAXIMUM_NORM_H
#define MATHTOOLS_MAXIMUM_NORM_H

#include "norm.h"
#include <algorithm>

namespace math {
namespace internal {

template<typename COORD_ITERATOR>
auto MaximumFunc_value(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(typeHelper(*begin))
{
  return *std::max_element(begin, end);
}

template<std::size_t N, typename COORD_TYPE>
struct MaximumFuncArity
{
  static typename NumTraits<COORD_TYPE>::Real value(const COORD_TYPE* coordPtr)
  {
    return std::max(*(coordPtr + N - 1), MaximumFuncArity<N - 1, COORD_TYPE>::value(coordPtr));
  }
};

template<typename COORD_TYPE>
struct MaximumFuncArity<1, COORD_TYPE>
{
  static typename NumTraits<COORD_TYPE>::Real value(const COORD_TYPE* coordPtr)
  { return *coordPtr; }
};

struct MaximumFunc
{
  template<typename COORD_ITERATOR>
  static auto fromRange(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(typeHelper(*begin))
  { return MaximumFunc_value(begin, end); }

  template<std::size_t N, typename COORD_TYPE>
  static typename NumTraits<COORD_TYPE>::Real fromPtr(const COORD_TYPE* coordPtr)
  { return MaximumFuncArity<N, COORD_TYPE>::value(coordPtr); }
};

template<> struct NormTraits<internal::MaximumFunc>
{
  typedef ArityNormSpecializationTag NormCategory;
};

} // namespace internal

/*! \brief Provides computation of the
 *         <a href="http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Maximum_norm_.28special_case_of:_infinity_norm.2C_uniform_norm.2C_or_supremum_norm.29">
 *         maximum norm</a>
 *
 *  \headerfile euclidean_norm.h <mathtools/euclidean_norm.h>
 *  \ingroup mathtools
 */
typedef Norm<internal::MaximumFunc> MaximumNorm;

} // namespace math

#endif // MATHTOOLS_MAXIMUM_NORM_H

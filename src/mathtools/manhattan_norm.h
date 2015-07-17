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

#ifndef MATHTOOLS_MANHATTAN_NORM_H
#define MATHTOOLS_MANHATTAN_NORM_H

#include "norm.h"
#include <cmath>

namespace math {
namespace internal {

template<typename COORD_ITERATOR>
auto ManhattanFunc_value(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(typeHelper(*begin))
{
  decltype(typeHelper(*begin)) result = 0;
  while (begin != end) {
    result += std::fabs(*begin);
    ++begin;
  }
  return result;
}

template<std::size_t N, typename COORD_TYPE>
struct ManhattanFuncArity
{
  static typename NumTraits<COORD_TYPE>::Real value(const COORD_TYPE* coordPtr)
  {
    return ManhattanFuncArity<N - 1, COORD_TYPE>::value(coordPtr) + std::fabs(*(coordPtr + N - 1));
  }
};

template<typename COORD_TYPE>
struct ManhattanFuncArity<1, COORD_TYPE>
{
  static typename NumTraits<COORD_TYPE>::Real value(const COORD_TYPE* coordPtr)
  { return std::fabs(*coordPtr); }
};

struct ManhattanFunc
{
  template<typename COORD_ITERATOR>
  static auto fromRange(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(typeHelper(*begin))
  { return ManhattanFunc_value(begin, end); }

  template<std::size_t N, typename COORD_TYPE>
  static typename NumTraits<COORD_TYPE>::Real fromPtr(const COORD_TYPE* coordPtr)
  { return ManhattanFuncArity<N, COORD_TYPE>::value(coordPtr); }
};

template<> struct NormTraits<internal::ManhattanFunc>
{
  typedef ArityNormSpecializationTag NormCategory;
};

} // namespace internal

/*! \brief Provides computation of the
 *         <a href="http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Taxicab_norm_or_Manhattan_norm">
 *         manhattan(or taxicab) norm</a>
 *
 *  \headerfile manhattan_norm.h <mathtools/manhattan_norm.h>
 *  \ingroup mathtools
 */
typedef Norm<internal::ManhattanFunc> ManhattanNorm;

} // namespace math

#endif // MATHTOOLS_NORMS_MANHATTAN_H

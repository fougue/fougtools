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

#ifndef MATHTOOLS_SQR_EUCLIDEAN_NORM_H
#define MATHTOOLS_SQR_EUCLIDEAN_NORM_H

#include "norm.h"

namespace math {
namespace internal {

template<typename COORD_ITERATOR>
auto SqrEuclideanFunc_value(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(typeHelper(*begin))
{
  decltype(typeHelper(*begin)) result = 0;
  while (begin != end) {
    result += (*begin) * (*begin);
    ++begin;
  }
  return result;
}

template<std::size_t N, typename COORD_TYPE>
struct SqrEuclideanFuncArity
{
  static typename NumTraits<COORD_TYPE>::Real value(const COORD_TYPE* coordPtr)
  {
    const COORD_TYPE& coord = *(coordPtr + N - 1);
    return SqrEuclideanFuncArity<N - 1, COORD_TYPE>::value(coordPtr) + coord*coord;
  }
};

template<typename COORD_TYPE>
struct SqrEuclideanFuncArity<1, COORD_TYPE>
{
  static typename NumTraits<COORD_TYPE>::Real value(const COORD_TYPE* coordPtr)
  { return (*coordPtr) * (*coordPtr); }
};

struct SqrEuclideanFunc
{
  template<typename COORD_ITERATOR>
  static auto fromRange(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(typeHelper(*begin))
  { return SqrEuclideanFunc_value(begin, end); }

  template<std::size_t N, typename COORD_TYPE>
  static typename NumTraits<COORD_TYPE>::Real fromPtr(const COORD_TYPE* coordPtr)
  { return SqrEuclideanFuncArity<N, COORD_TYPE>::value(coordPtr); }
};

template<> struct NormTraits<internal::SqrEuclideanFunc>
{
  typedef ArityNormSpecializationTag NormCategory;
};

} // namespace internal

/*! \brief Provides computation of the squared euclidean norm
 *
 *  \headerfile sqr_euclidean_norm.h <mathtools/sqr_euclidean_norm.h>
 *  \ingroup mathtools
 */
typedef Norm<internal::SqrEuclideanFunc> SqrEuclideanNorm;

} // namespace math

#endif // MATHTOOLS_NORMS_SQR_EUCLIDEAN_H

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

#ifndef MATHTOOLS_EUCLIDEAN_NORM_H
#define MATHTOOLS_EUCLIDEAN_NORM_H

#include "sqr_euclidean_norm.h"
#include <cmath>

namespace math {
namespace internal {

struct EuclideanFunc
{
  template<typename COORD_ITERATOR>
  static auto fromRange(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(typeHelper(*begin))
  { return std::sqrt(SqrEuclideanFunc::fromRange(begin, end)); }

  template<std::size_t N, typename COORD_TYPE>
  static typename NumTraits<COORD_TYPE>::Real fromPtr(const COORD_TYPE* coordPtr)
  { return std::sqrt(SqrEuclideanFunc::fromPtr<N, COORD_TYPE>(coordPtr)); }
};

template<> struct NormTraits<internal::EuclideanFunc>
{
  typedef ArityNormSpecializationTag NormCategory;
};

} // namespace internal

/*! \brief Provides computation of the
 *         <a href="http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Euclidean_norm">
 *         euclidean norm</a>
 *
 *  \headerfile euclidean_norm.h <mathtools/euclidean_norm.h>
 *  \ingroup mathtools
 */
typedef Norm<math::internal::EuclideanFunc> EuclideanNorm;

} // namespace math

#endif // MATHTOOLS_EUCLIDEAN_NORM_H

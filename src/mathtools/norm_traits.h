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

#ifndef MATHTOOLS_NORM_TRAITS_H
#define MATHTOOLS_NORM_TRAITS_H

#include <cstddef>
#include "num_traits.h"

namespace math {
namespace internal {

template<typename T> typename NumTraits<T>::Real typeHelper(const T&) { return 0; }

struct NormSpecializationTag { };
struct DefaultNormSpecializationTag { };
struct ArityNormSpecializationTag { };

template<typename FUNC>
struct NormTraits
{
  typedef NormSpecializationTag NormCategory;
};

} // namespace internal
} // namespace math

#endif // MATHTOOLS_NORMS_NORM_TRAITS_H

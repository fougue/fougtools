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

typedef Norm<internal::ManhattanFunc> ManhattanNorm;

} // namespace math

#endif // MATHTOOLS_NORMS_MANHATTAN_H

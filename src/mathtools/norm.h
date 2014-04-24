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

#ifndef MATHTOOLS_NORM_H
#define MATHTOOLS_NORM_H

#include "norm_traits.h"
#include "vec_traits.h"

namespace math {

namespace internal {

template<typename VEC> struct VecTraitsHelper
{
  typedef typename NumTraits< typename VecTraits<VEC>::CoordType >::Real Real;
};

} // namespace internal

/*! \brief Computation of norms in K-vector space
 *
 *  \tparam FUNC Class providing the concrete computation functions
 *
 *  \headerfile norm.h <mathtools/norm.h>
 *  \ingroup mathtools
 */
template<typename FUNC>
struct Norm
{
  /*! \brief Returns the norm of the vector with coordinates in iterator range [ \p begin , \p end ]
   *  \tparam COORD_ITERATOR Type of the iterator over the vector's coordinates
   */
  template<typename COORD_ITERATOR>
#ifndef DOXYGEN
  static auto fromRange(COORD_ITERATOR begin, COORD_ITERATOR end) -> decltype(internal::typeHelper(*begin))
  { return FUNC::fromRange(begin, end); }
#else
  static CompatibleRealType fromRange(COORD_ITERATOR begin, COORD_ITERATOR end);
#endif

  template<typename COORD_ITERATOR>
  static bool isNullRange(COORD_ITERATOR begin, COORD_ITERATOR end)
  {
    typedef decltype(*begin) CoordType;
    return Norm::fromRange(begin, end) < NumTraits<CoordType>::precision();
  }


  /*! \brief Returns the norm of the vector with its N coordinates stored in memory at \p coordPtr
   *  \tparam N Size of the vector (count of coordinates)
   *  \tparam COORD_TYPE Type of the vector's corrdinates
   */
  template<std::size_t N, typename COORD_TYPE>
#ifndef DOXYGEN
  static typename NumTraits<COORD_TYPE>::Real fromPtr(const COORD_TYPE* coordPtr)
  {
    typename internal::NormTraits<FUNC>::NormCategory normCategory;
    return Norm::fromPtrDispatch<N, COORD_TYPE>(coordPtr, normCategory);
  }
#else
  static CompatibleRealType fromPtr(const COORD_TYPE* coordPtr);
#endif

  template<std::size_t N, typename COORD_TYPE>
  static bool isNullPtr(const COORD_TYPE* coordPtr)
  { return Norm::fromPtr(coordPtr) < NumTraits<COORD_TYPE>::precision(); }


  /*! \brief Returns the norm of the vector with its N coordinates stored in array \p coordArray
   */
  template<std::size_t N, typename COORD_TYPE>
#ifndef DOXYGEN
  static typename NumTraits<COORD_TYPE>::Real fromArray(const COORD_TYPE (&coordArray)[N])
  { return Norm::fromPtr<N, COORD_TYPE>(&coordArray[0]); }
#else
  static CompatibleRealType fromArray(const COORD_TYPE (&coordArray)[N]);
#endif

  template<std::size_t N, typename COORD_TYPE>
  static bool isNullArray(const COORD_TYPE (&coordArray)[N])
  { return Norm::fromArray(coordArray) < NumTraits<COORD_TYPE>::precision(); }


  /*! \brief Returns the norm of the vector object \p vec
   */
  template<typename VEC>
#ifndef DOXYGEN
  static typename internal::VecTraitsHelper<VEC>::Real fromObject(const VEC& vec)
  {
    typename VecTraits<VEC>::AccessCategory accessCategory;
    return Norm::fromObjectDispatch(vec, accessCategory);
  }
#else
  static CompatibleRealType fromObject(const VEC& vec);
#endif

  template<typename VEC>
  static bool isNullObject(const VEC& vec)
  {
    typedef typename VecTraits<VEC>::CoordType CoordType;
    return Norm::fromObject(vec) < NumTraits<CoordType>::precision();
  }

#ifndef DOXYGEN
  // -- Implementation

private:
  template<std::size_t N, typename COORD_TYPE>
  static typename NumTraits<COORD_TYPE>::Real fromPtrDispatch(const COORD_TYPE* coordPtr,
                                                              internal::DefaultNormSpecializationTag)
  { return Norm::fromRange(coordPtr, coordPtr + N); }


  template<std::size_t N, typename COORD_TYPE>
  static typename NumTraits<COORD_TYPE>::Real fromPtrDispatch(const COORD_TYPE* coordPtr,
                                                              internal::ArityNormSpecializationTag)
  { return FUNC::template fromPtr<N, COORD_TYPE>(coordPtr); }


  template<typename VEC>
  static typename internal::VecTraitsHelper<VEC>::Real fromObjectDispatch(const VEC& vec,
                                                                          StlIteratorVecAccessTag)
  { return Norm::fromRange(vec.begin(), vec.end()); }


  template<typename VEC>
  static typename internal::VecTraitsHelper<VEC>::Real fromObjectDispatch(const VEC& vec,
                                                                          FuncIteratorVecAccessTag)
  { return Norm::fromRange(VecAccess<VEC>::begin(vec), VecAccess<VEC>::end(vec)); }


  template<typename VEC>
  static typename internal::VecTraitsHelper<VEC>::Real fromObjectDispatch(const VEC& vec,
                                                                          PointerVecAccessTag)
  {
    typedef typename VecTraits<VEC>::CoordType CoordType;
    return Norm::fromPtr<VecTraits<VEC>::Arity, CoordType>(VecAccess<VEC>::pointer(vec));
  }


  template<typename VEC>
  static typename internal::VecTraitsHelper<VEC>::Real fromObjectDispatch(const VEC& vec,
                                                                          StdArrayVecAccessTag)
  {
    const auto&& array = VecAccess<VEC>::stdarray(vec);
    return Norm::fromRange(array.cbegin(), array.cend());
  }

#endif // !DOXYGEN
};

} // namespace math

#endif // MATHTOOLS_NORM_H

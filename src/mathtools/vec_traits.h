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

#ifndef MATHTOOLS_VEC_TRAITS_H
#define MATHTOOLS_VEC_TRAITS_H

#include "num_traits.h"

namespace math {

/*! \brief Base class for tag dispatching on how to access vector coordinates
 *  \headerfile vec_traits.h <mathtools/vec_traits.h>
 *  \ingroup mathtools
 */
struct VecAccessTag { };

/*! \brief Tag dispatch for STL iterator interface
 *
 *  This means the vector class provides begin()/end() functions
 *
 *  \headerfile vec_traits.h <mathtools/vec_traits.h>
 *  \ingroup mathtools
 */
struct StlIteratorVecAccessTag : public VecAccessTag { };

/*! \brief Tag dispatch for iterator interface provided by static functions
 *
 *  This means there exists functions provinding iterator access for the vector objects.
 *
 *  Example :
 *  \code
 *  struct MyVector2D
 *  {
 *    double x;
 *    double y;
 *  };
 *
 *  namespace math {
 *    template<> struct VecAccess<MyVector2D>
 *    {
 *      static double* begin(MyVector2d& vec) { &return vec.x; } // Optional: required only for mutating algorithms
 *      static double* end(MyVector2d& vec)   { &return vec.y; } // Optional: required only for mutating algorithms
 *
 *      static const double* begin(const MyVector2d& vec) { &return vec.x; }
 *      static const double* end(const MyVector2d& vec)   { &return vec.y; }
 *    };
 *  }
 *  \endcode
 *
 *  \headerfile vec_traits.h <mathtools/vec_traits.h>
 *  \ingroup mathtools
 */
struct FuncIteratorVecAccessTag : public VecAccessTag { };

/*! \brief Tag dispatch for vector coordinates to be accessed with a static constPointer() function
 *
 * "Pointer" access requires that coordinates of a vector object have to be layout contiguously in
 *  memory.
 *
 *  Example :
 *  \code
 *  struct MyVector2D
 *  {
 *    double x;
 *    double y;
 *  };
 *
 *  namespace math {
 *    template<> struct VecAccess<MyVector2D>
 *    {
 *      static double* pointer(MyVector2D& vec) // Optional: required only for mutating algorithms
 *      { return &vec.x; }
 *
 *      static const double* pointer(const MyVector2D& vec)
 *      { return &vec.x; }
 *    };
 *  }
 *  \endcode
 *
 *  \headerfile vec_traits.h <mathtools/vec_traits.h>
 *  \ingroup mathtools
 */
struct PointerVecAccessTag : public VecAccessTag { };

/*! \brief Tag dispatch for vector coordinates to be accessed with a temporary std::array<> object
 *
 *  When none of the other tags can be used, then StdArrayVecAccessTag is the fallback access to
 *  vector coordinates. It has the penality of the creation of a temporary std::array<> object that
 *  will store the vector coordinates.
 *
 *  Example :
 *  \code
 *  struct MyVector2D
 *  {
 *    double x;
 *    double y;
 *  };
 *
 *  namespace math {
 *    template<> struct VecAccess<MyVector2D>
 *    {
 *      // Optional: required only for mutating algorithms
 *      static void assign(MyVector2D& vec, const std::array<double, 2>& array)
 *      {
 *        vec.x = array.at(0);
 *        vec.y = array.at(1);
 *      }
 *
 *      static std::array<double, 2> stdarray(const MyVector2D& vec)
 *      {
 *        const std::array<double, 2> array = { vec.x, vec.y };
 *        return array;
 *      }
 *    };
 *  }
 *  \endcode
 *
 *  \headerfile vec_traits.h <mathtools/vec_traits.h>
 *  \ingroup mathtools
 */
struct StdArrayVecAccessTag : public VecAccessTag { };


/*! \brief Type traits on vector types
 *
 *  Example:
 *  \code
 *  struct MyVector2D
 *  {
 *    double x;
 *    double y;
 *  };

 *  namespace math {
 *
 *    template<> struct VecTraits<MyVector2D>
 *    {
 *      typedef PointerVecAccessTag AccessCategory;
 *      typedef double CoordType;
 *      enum { Arity = 2 };
 *    };
 *
 *    template<> struct VecAccess<MyVector2D>
 *    {
 *      static const double* pointer(const MyVector2D& vec)
 *      { return &vec.x; }
 *    };
 *
 *  }
 *  \endcode
 *
 *  \headerfile vec_traits.h <mathtools/vec_traits.h>
 *  \ingroup mathtools
 */
template<typename VEC> struct VecTraits
{
  // typedef VecAccessTag AccessCategory;
  // typedef double CoordType;
  // enum { Arity = 3 };
};

/*! \brief Empty generic class to be specialized by vector type
 */
template<typename VEC> struct VecAccess { };

} // namespace math

#endif // MATHTOOLS_VEC_TRAITS_H

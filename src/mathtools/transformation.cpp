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

#include "transformation.h"

/*! \file transformation.cpp
 *  \brief This file only exists for documentation purpose
 *  \dontinclude transformation.cpp
 */

namespace geom {

/*! \class Transformation
 *  \brief Transformations in space of dimension \c _SIZE_ express as a column-major square matrix
 */

/*! \fn template<typename _T_, unsigned _SIZE_> \
 *              const Transformation<_T_, _SIZE_> operator*( \
 *                                  const Transformation<_T_, _SIZE_>& m1, \
 *                                  const Transformation<_T_, _SIZE_>& m2)
 *  \brief Compose
 *  \relates Transformation
 */

/*! \fn template<typename _T_, unsigned _SIZE_> \
 *               const Point<_T_, _SIZE_> operator*( \
 *                                const Transformation<_T_, _SIZE_>& m, \
 *                                const Point<_T_, _SIZE_>& pt)
 *  \brief Compose for points
 *  \relates Transformation
 */

/*! \fn template<typename _T_, unsigned _SIZE_> \
 *               Vector<_T_, _SIZE_> operator*( \
 *                                const Transformation<_T_, _SIZE_>& m, \
 *                                const Vector<_T_, _SIZE_>& v)
 *
 *  \brief Compose for vectors
 *  \relates Transformation
 */

/*! \class Transformation2
 *  \brief Transformations in 2d space
 */

/*! \class Transformation3
 *  \brief Transformations in 3d space
 *
 *  The transformations implemented are translation, rotation, scale.\n
 *  Complex transformations can be obtained by combining the previous elementary transformations
 *  using the method compose().\n
 *  Transformations can be represented as follow : \n
 *  \code
 *       V1   V2   V3    T       XYZ        XYZ
 *    | a11  a12  a13   a14 |   | x |      | x'|
 *    | a21  a22  a23   a24 |   | y |      | y'|
 *    | a31  a32  a33   a34 |   | z |   =  | z'|
 *    |  0    0    0     1  |   | 1 |      | 1 |
 *  \endcode
*/

} // namespace geom

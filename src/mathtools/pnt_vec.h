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

#ifndef MATHTOOLS_PNT_VEC_H
#define MATHTOOLS_PNT_VEC_H

namespace math {

template<typename PNT_VEC>
struct PntVecCoords
{
//  static double x(const PNT_VEC& p); //! X coordinate of point-vector \p
//  static double y(const PNT_VEC& p); //! Y coordinate of point-vector \p
//  static double z(const PNT_VEC& p); //! Z coordinate of point-vector \p
};

template<typename POINT, typename VECTOR>
struct PntVecOperations
{
//  static void normalize(VECTOR* v);
//  static VECTOR cross(const VECTOR& u, const VECTOR& v);
//  static double dot(const VECTOR& u, const VECTOR& v);
//  static POINT translate(const POINT& p, const VECTOR& v);
//  static VECTOR vector(const POINT& p1, const POINT& p2);
//  static VECTOR vector(const POINT& p);
//  static VECTOR mult(double k, const VECTOR& v);
};

template<typename PNT_VEC>
struct PntVecTraits
{
  typedef PNT_VEC Point;
  typedef PNT_VEC Vector;
};

} // namespace math

#endif // MATHTOOLS_PNT_VEC_H

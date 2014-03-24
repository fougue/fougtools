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

#ifdef MATHTOOLS_PROJECT_POINT_ON_TRIANGLE_H

#include "pnt_vec.h"

namespace math {

template<typename POINT>
const std::pair<POINT, bool> projectPointOnTriangle(const POINT& p,
                                                    const POINT& v0,
                                                    const POINT& v1,
                                                    const POINT& v2)
{
  typedef typename PntVecTraits<POINT>::CoordValue CoordValue;
  typedef typename PntVecTraits<POINT>::Vector Vector;
  typedef PntVecOperations<POINT, Vector> PntVecOps;

  const Vector e0(PntVecOps::vector(v0, v1));
  const Vector e1(PntVecOps::vector(v0, v2));
  const Vector D(PntVecOps::vector(p, v0));

  const CoordValue a = PntVecOps::dot(e0, e0);
  const CoordValue b = PntVecOps::dot(e0, e1);
  const CoordValue c = PntVecOps::dot(e1, e1);
  const CoordValue d = PntVecOps::dot(e0, D);
  const CoordValue e = PntVecOps::dot(e1, D);

  const CoordValue det = a * c - b * b;
  CoordValue s = b * e - c * d;
  CoordValue t = b * d - a * e;

  int region = 0;
  if (s + t <= det) {
    if (s < 0.) {
      if (t < 0.)
        region = 4;
      else
        region = 3;
    }
    else if (t < 0.)
      region = 5;
  }
  else {
    if (s < 0.)
      region = 2;
    else if (t < 0.)
      region = 6;
    else
      region = 1;
  }

  switch (region) {
  case 0: {
    const CoordValue invDet = 1. / det;
    s *= invDet;
    t *= invDet;
    break;
  }
  case 1: {
    const CoordValue numer = c + e - b - d;
    if (numer <= 0.) {
      s = 0.;
    }
    else {
      const CoordValue denom = a - 2. * b + c;
      s = (numer >= denom ? 1. : numer / denom);
    }
    t = 1. - s;
    break;
  }
  case 2: {
    s = 0.;
    t = 1.;
    break;
  }
  case 3: {
    s = 0.;
    t = (e >= 0. ? 0. : (-e >= c ? 1. : -e / c));
    break;
  }
  case 4: {
    s = 0.;
    t = 0.;
    break;
  }
  case 5: {
    t = 0.;
    s = (d >= 0. ? 0. : (-d >= a ? 1. : -d / a));
    break;
  }
  case 6: {
    s = 1.;
    t = 0.;
    break;
  }
  }

  return std::make_pair(PntVecOps::translate(PntVecOps::translate(v0, e0 * s), e1 * t),
                        region == 0);
}

/*! \struct project_point_on_triangle
 *  \brief  Wraps projectPointOnTriangle() as a unary functor
 */

//! Construct the functor : \p v0 , \p v1 , \p v2 are the vertices of the
//! triangle to project points to.
template<typename POINT>
project_point_on_triangle<POINT>::project_point_on_triangle(const POINT& v0,
                                                            const POINT& v1,
                                                            const POINT& v2)
  : m_v0(v0), m_v1(v1), m_v2(v2)
{
}

template<typename POINT>
const std::pair<POINT, bool> project_point_on_triangle<POINT>::operator()(const POINT& pnt)
{
  return projectPointOnTriangle<POINT>(pnt, m_v0, m_v1, m_v2);
}

} // namespace math

#endif // MATHTOOLS_PROJECT_POINT_ON_TRIANGLE_H

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

#include "math_tools.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <Poly_Triangle.hxx>
#include <TColgp_Array1OfPnt.hxx>

namespace occ {

/*! \class MathTools
 *  \brief Collection of tools for the Math toolkit
 *
 *  \headerfile math_tools.h <occtools/math_tools.h>
 *  \ingroup occtools
 */

Standard_Real MathTools::euclideanNorm(const gp_Vec &vec)
{
  return std::sqrt(MathTools::squaredEuclideanNorm(vec));
}

Standard_Real MathTools::squaredEuclideanNorm(const gp_Vec &vec)
{
  return vec.X() * vec.X() + vec.Y() * vec.Y() + vec.Z() * vec.Z();
}

Standard_Real MathTools::manhattanNorm(const gp_Vec &vec)
{
  return std::fabs(vec.X()) + std::fabs(vec.Y()) + std::fabs(vec.Z());
}

Standard_Real MathTools::maximumNorm(const gp_Vec &vec)
{
  return std::max(std::fabs(vec.X()), std::max(std::fabs(vec.Y()), std::fabs(vec.Z())));
}

/*! \brief Non-normalized vector to a triangle
 *  \param nodes
 *         Vertices of the triangulation that \p triangle belongs to
 *  \param triangle
 *         Triangle whose normal has to be computed
 *  \param ori
 *         Orientation of the triangle (generally inherited from the triangulated face)
 */
gp_Vec MathTools::triangleNormal(const TColgp_Array1OfPnt &nodes,
                                 const Poly_Triangle &triangle,
                                 TopAbs_Orientation ori)
{
  Standard_Integer n1, n2, n3;
  if (ori == TopAbs_REVERSED)
    triangle.Get(n1, n3, n2);
  else
    triangle.Get(n1, n2, n3);
  assert(nodes.Lower() <= n1 && n1 <= nodes.Upper());
  assert(nodes.Lower() <= n2 && n2 <= nodes.Upper());
  assert(nodes.Lower() <= n3 && n3 <= nodes.Upper());
  const gp_Vec v1(nodes(n1), nodes(n2)); // V1=(P1,P2)
  const gp_Vec v2(nodes(n2), nodes(n3)); // V2=(P2,P3)
  const gp_Vec v3(nodes(n3), nodes(n1)); // V3=(P3,P1)

  if ((v1.SquareMagnitude() > 1.e-10)
      && (v2.SquareMagnitude() > 1.e-10)
      && (v3.SquareMagnitude() > 1.e-10))
  {
    return v1.Crossed(v2);
  }
  return v1;
}

} // namespace occ

//! \relates MathTools
gp_Vec operator-(const gp_Pnt& p1, const gp_Pnt& p2)
{
  return gp_Vec(p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z());
}

//! \relates MathTools
gp_Pnt operator-(const gp_Pnt& p, const gp_Vec& v)
{
  return gp_Pnt(p.X() - v.X(), p.Y() - v.Y(), p.Z() - v.Z());
}

//! \relates MathTools
gp_Pnt operator+(const gp_Pnt& p, const gp_Vec& v)
{
  return gp_Pnt(p.X() + v.X(), p.Y() + v.Y(), p.Z() + v.Z());
}

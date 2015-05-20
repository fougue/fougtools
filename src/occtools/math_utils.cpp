/****************************************************************************
**
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
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

#include "math_utils.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <Poly_Triangle.hxx>
#include <TColgp_Array1OfPnt.hxx>

namespace occ {

/*! \class MathUtils
 *  \brief Collection of tools for the Math toolkit
 *
 *  \headerfile math_utils.h <occtools/math_utils.h>
 *  \ingroup occtools
 */

gp_Trsf MathUtils::displacement(const gp_Ax3 &srcSys, const gp_Ax3 &dstSys)
{
    gp_Trsf trsf;
    trsf.SetDisplacement(srcSys, dstSys);
    return trsf;
}

gp_Trsf MathUtils::transformation(const gp_Ax3 &srcSys, const gp_Ax3 &dstSys)
{
    gp_Trsf trsf;
    trsf.SetTransformation(srcSys, dstSys);
    return trsf;
}

gp_Trsf MathUtils::transformation(const gp_Ax3 &dstSys)
{
    gp_Trsf trsf;
    trsf.SetTransformation(dstSys);
    return trsf;
}

gp_Trsf MathUtils::transformation(const gp_Quaternion &q, const gp_Vec &vec)
{
    gp_Trsf trsf;
    trsf.SetTransformation(q, vec);
    return trsf;
}

gp_Pnt MathUtils::projectPointOnPlane(const gp_Pnt &p, const gp_Vec &n)
{
    const gp_Vec pVec(p.X(), p.Y(), p.Z());
    const Standard_Real dotVN = pVec.Dot(n);
    return p.Translated(-dotVN * n);
}

std::pair<gp_Pnt, bool> MathUtils::projectPointOnTriangle(
        const gp_Pnt &p, const gp_Pnt &v0, const gp_Pnt &v1, const gp_Pnt &v2)
{
    const gp_Vec e0(v0, v1);
    const gp_Vec e1(v0, v2);
    const gp_Vec D(p, v0);

    const Standard_Real a = e0.Dot(e0);
    const Standard_Real b = e0.Dot(e1);
    const Standard_Real c = e1.Dot(e1);
    const Standard_Real d = e0.Dot(D);
    const Standard_Real e = e1.Dot(D);

    const Standard_Real det = a * c - b * b;
    Standard_Real s = b * e - c * d;
    Standard_Real t = b * d - a * e;

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
        const Standard_Real invDet = 1. / det;
        s *= invDet;
        t *= invDet;
        break;
    }
    case 1: {
        const Standard_Real numer = c + e - b - d;
        if (numer <= 0.) {
            s = 0.;
        }
        else {
            const Standard_Real denom = a - 2. * b + c;
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
    } // end switch

    return std::make_pair(
                v0.Translated(e0 * s).Translated(e1 * t),
                region == 0);
}

Standard_Real MathUtils::euclideanNorm(const gp_Vec &vec)
{
    return std::sqrt(MathUtils::squaredEuclideanNorm(vec));
}

Standard_Real MathUtils::squaredEuclideanNorm(const gp_Vec &vec)
{
    return vec.X() * vec.X() + vec.Y() * vec.Y() + vec.Z() * vec.Z();
}

Standard_Real MathUtils::manhattanNorm(const gp_Vec &vec)
{
    return std::fabs(vec.X()) + std::fabs(vec.Y()) + std::fabs(vec.Z());
}

/*! \brief Returns the component of \p vec having the maximum absolute value */
Standard_Real MathUtils::maximumNorm(const gp_Vec &vec)
{
    return std::max(
                std::fabs(vec.X()),
                std::max(std::fabs(vec.Y()), std::fabs(vec.Z())));
}

/*! \brief Returns the oriented normal of a triangle
 *
 *  \warning The returned vector is not normalized
 *
 *  \param nodes  Vertices of the triangulation that \p triangle belongs to
 *  \param triangle  Triangle whose normal has to be computed
 *  \param ori  Orientation of the triangle (generally inherited from the
 *              triangulated face)
 */
gp_Vec MathUtils::triangleNormal(
        const TColgp_Array1OfPnt &nodes,
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

//! \relates MathUtils
gp_Vec operator-(const gp_Pnt& p1, const gp_Pnt& p2)
{
    return gp_Vec(p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z());
}

//! \relates MathUtils
gp_Pnt operator-(const gp_Pnt& p, const gp_Vec& v)
{
    return gp_Pnt(p.X() - v.X(), p.Y() - v.Y(), p.Z() - v.Z());
}

//! \relates MathUtils
gp_Pnt operator+(const gp_Pnt& p, const gp_Vec& v)
{
    return gp_Pnt(p.X() + v.X(), p.Y() + v.Y(), p.Z() + v.Z());
}

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

#pragma once

#include "occtools.h"

#include <utility>
#include <gp_Vec.hxx>
#include <TopAbs_Orientation.hxx>
class Poly_Triangle;
class TColgp_Array1OfPnt;

namespace occ {

class OCCTOOLS_EXPORT MathTools
{
public:
    static gp_Pnt projectPointOnPlane(const gp_Pnt& p, const gp_Vec& n);
    static std::pair<gp_Pnt, bool> projectPointOnTriangle(const gp_Pnt& p,
                                                          const gp_Pnt& v0,
                                                          const gp_Pnt& v1,
                                                          const gp_Pnt& v2);

    static Standard_Real euclideanNorm(const gp_Vec& vec);
    static Standard_Real squaredEuclideanNorm(const gp_Vec& vec);
    static Standard_Real manhattanNorm(const gp_Vec& vec);
    static Standard_Real maximumNorm(const gp_Vec& vec);

    template<typename NORM>
    static bool isNull(const gp_Vec& vec, const NORM& norm);

    static gp_Vec triangleNormal(const TColgp_Array1OfPnt& nodes,
                                 const Poly_Triangle& triangle,
                                 TopAbs_Orientation ori = TopAbs_FORWARD);

    template<typename OCC_PNT_VEC, typename TEXT_STREAM>
    static TEXT_STREAM& printOccPntVec(TEXT_STREAM& ts, const OCC_PNT_VEC& v);
};

const gp_Pnt2d origin2d(0, 0);
const gp_Dir2d xDir2d(1, 0);
const gp_Dir2d yDir2d(0, 1);

const gp_Pnt origin3d(0, 0, 0);
const gp_Dir xDir3d(1, 0, 0);
const gp_Dir yDir3d(0, 1, 0);
const gp_Dir zDir3d(0, 0, 1);

} // namespace occ

OCCTOOLS_EXPORT gp_Vec operator-(const gp_Pnt& p1, const gp_Pnt& p2);
OCCTOOLS_EXPORT gp_Pnt operator-(const gp_Pnt& p, const gp_Vec& v);
OCCTOOLS_EXPORT gp_Pnt operator+(const gp_Pnt& p, const gp_Vec& v);

template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Pnt& p);

template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Vec& v);

template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Dir& d);

//--
//-- Implementation
//--

template<typename NORM>
bool occ::MathTools::isNull(const gp_Vec& vec, const NORM& norm)
{
    return norm(vec) <= 0.000000000001;
}

template<typename OCC_PNT_VEC, typename TEXT_STREAM>
TEXT_STREAM &occ::MathTools::printOccPntVec(TEXT_STREAM &ts, const OCC_PNT_VEC &v)
{
    return ts << "(" << v.X() << ", " << v.Y() << ", " << v.Z() << ")";
}

//! Print (dump) in the text stream \p ts the point \p p
template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Pnt& p)
{
    return occ::MathTools::printOccPntVec(ts, p);
}

//! Print (dump) in the text stream \p ts the vector \p v
template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Vec& v)
{
    return occ::MathTools::printOccPntVec(ts, v);
}

//! Print (dump) in the text stream \p ts the direction \p d
template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Dir& d)
{
    return occ::MathTools::printOccPntVec(ts, d);
}

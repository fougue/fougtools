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

#ifndef GEOM_POINT_VECTOR_FWD_H
#define GEOM_POINT_VECTOR_FWD_H

#include "pnt_vec_traits_def.h"

namespace geom {

template<typename T, unsigned S>
class Point;

template<typename T>
class Point2;

typedef Point2<int>         Point2i_t;
typedef Point2<long>        Point2l_t;
typedef Point2<float>       Point2f_t;
typedef Point2<double>      Point2d_t;
typedef Point2<long double> Point2ld_t;

template<typename T>
class Point3;

typedef Point3<int>         Point3i_t;
typedef Point3<long>        Point3l_t;
typedef Point3<float>       Point3f_t;
typedef Point3<double>      Point3d_t;
typedef Point3<long double> Point3ld_t;

template<typename T, unsigned S>
class Vector;

template<typename T>
class Vector2;

typedef Vector2<int>         Vector2i_t;
typedef Vector2<long>        Vector2l_t;
typedef Vector2<float>       Vector2f_t;
typedef Vector2<double>      Vector2d_t;
typedef Vector2<long double> Vector2ld_t;

template<typename T>
class Vector3;

typedef Vector3<int>         Vector3i_t;
typedef Vector3<long>        Vector3l_t;
typedef Vector3<float>       Vector3f_t;
typedef Vector3<double>      Vector3d_t;
typedef Vector3<long double> Vector3ld_t;

template<typename T>
struct PntVecTraits< geom::Point3<T>, geom::Vector3<T> >;

typedef PntVecTraits< geom::Point3<int>, geom::Vector3<int> >
NaturalPntVecTraitsi_t;
typedef PntVecTraits< geom::Point3<long>, geom::Vector3<long> >
NaturalPntVecTraitsl_t;
typedef PntVecTraits< geom::Point3<float>, geom::Vector3<float> >
NaturalPntVecTraitsf_t;
typedef PntVecTraits< geom::Point3<double>, geom::Vector3<double> >
NaturalPntVecTraitsd_t;
typedef PntVecTraits< geom::Point3<long double>, geom::Vector3<long double> >
NaturalPntVecTraitsld_t;

} // namespace geom

#endif // GEOM_POINT_VECTOR_FWD_H

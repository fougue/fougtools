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

#ifndef OCC_PNT_VEC_TRAITS_H
#define OCC_PNT_VEC_TRAITS_H

#include <cassert>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include "../mathtools/pnt_vec.h"

namespace math {

namespace internal_occtools {

template<typename OCC_PNT_VEC>
struct PntVecCoords
{
  static double x(const OCC_PNT_VEC& pv)
  { return pv.X(); }

  static double y(const OCC_PNT_VEC& pv)
  { return pv.Y(); }

  static double z(const OCC_PNT_VEC& pv)
  { return pv.Z(); }
};

struct PntVecTraits
{
  typedef gp_Pnt Point;
  typedef gp_Vec Vector;
  typedef Standard_Real CoordValue;
};

} // namespace internal_occtools

template<>
struct PntVecCoords<gp_Pnt> : public internal_occtools::PntVecCoords<gp_Pnt>
{ };

template<>
struct PntVecCoords<gp_Vec> : public internal_occtools::PntVecCoords<gp_Pnt>
{ };

template<>
struct PntVecOperations<gp_Pnt, gp_Vec>
{
  static void normalize(gp_Vec* v)
  { v->Normalize(); }

  static gp_Vec cross(const gp_Vec& u, const gp_Vec& v)
  { return u.Crossed(v); }

  static Standard_Real dot(const gp_Vec& u, const gp_Vec& v)
  { return u.Dot(v); }

  static gp_Pnt translate(const gp_Pnt& p, const gp_Vec& v)
  { return p.Translated(v); }

  static gp_Vec vector(const gp_Pnt& p1, const gp_Pnt& p2)
  { return gp_Vec(p1, p2); }

  static gp_Vec vector(const gp_Pnt& p)
  { return gp_Vec(p.X(), p.Y(), p.Z()); }

  static gp_Vec mult(Standard_Real k, const gp_Vec& v)
  { return k * v; }
};

template<>
struct PntVecTraits<gp_Pnt> : public internal_occtools::PntVecTraits
{ };

template<>
struct PntVecTraits<gp_Vec> : public internal_occtools::PntVecTraits
{ };

} // namespace math

#endif // OCC_PNT_VEC_TRAITS_H

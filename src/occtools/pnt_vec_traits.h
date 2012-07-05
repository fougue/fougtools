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
#include "../mathtools/pnt_vec_traits_def.h"

namespace geom {

template<>
struct PntVecTraits<gp_Pnt, gp_Vec>
{
  typedef gp_Pnt Pnt_t;
  typedef gp_Vec Vec_t;
  typedef Standard_Real Value_t;

  static void normalize(Vec_t* v)
  {
    assert(v != 0);
    v->Normalize();
  }

  static Vec_t cross(const Vec_t& u, const Vec_t& v)
  {
    return u.Crossed(v);
  }

  static Value_t dot(const Vec_t& u, const Vec_t& v)
  {
    return u.Dot(v);
  }

  static Pnt_t translate(const Pnt_t& p, const Vec_t& v)
  {
    return p.Translated(v);
  }

  static Vec_t vector(const Pnt_t& p1, const Pnt_t& p2)
  {
    return Vec_t(p1, p2);
  }

  static Vec_t vector(const Pnt_t& p)
  {
    return Vec_t(p.X(), p.Y(), p.Z());
  }

  static Vec_t mult(Value_t k, const Vec_t& v)
  {
    return k * v;
  }
};

} // namespace geom

namespace occ {

typedef geom::PntVecTraits<gp_Pnt, gp_Vec> PntVecTraits_t;

} // namespace occ

#endif // OCC_PNT_VEC_TRAITS_H

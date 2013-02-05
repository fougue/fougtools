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

#ifdef OCC_UTILS_H

#include "../mathtools/point_vector.h"

namespace occ {
//
// --- Creation
//

//! Topologic compound of shapes denoted between the begin and end iterators
//! \p iBegin and \p iEnd
template<typename FWD_ITERATOR>
TopoDS_Compound makeCompound(FWD_ITERATOR iBegin, FWD_ITERATOR iEnd)
{
  TopoDS_Compound cmpd;
  BRep_Builder builder;
  builder.MakeCompound(cmpd);

  while (iBegin != iEnd) {
    builder.Add(cmpd, *iBegin);
    ++iBegin;
  }

  return cmpd;
}

//! Shorthand to occ::makeCompound(cnter.begin(), cnter.end())
template<typename CONTAINER>
TopoDS_Compound makeCompound(CONTAINER cnter)
{
  return makeCompound(cnter.begin(), cnter.end());
}

// --- Geometry conversion

//! Conversion of the Point3 \p p to a gp_Pnt
template<typename T>
gp_Pnt toOccPoint3d(const geom::Point3<T>& p)
{
  return gp_Pnt(static_cast<double>(p.x()),
                static_cast<double>(p.y()),
                static_cast<double>(p.z()));
}

//! Conversion of the Vector3 \p v to a gp_Vec.
template<typename T>
gp_Vec toOccVector3d(const geom::Vector3<T>& v)
{
  return gp_Vec(static_cast<double>(v.x()),
                static_cast<double>(v.y()),
                static_cast<double>(v.z()));
}

/*! \class occ::down_cast
 *  \brief Downcasting operator for OpenCascade handles
 *
 *  It wraps up into a syntactic C++ sugar the way casting of handles is supported in OpenCascade
 *
 *  Example : suppose you would like to downcast an Handle_Geom_Curve into a Handle_Geom_Circle.
 *  With OpenCascade it can be done by :
 *    \code
 *      Handle_Geom_Circle gcircle = Handle_Geom_Circle::DownCast(gcurve);
 *    \endcode
 *  The equivalent with the down_cast<> operator is :
 *    \code
 *      Handle_Geom_Circle gcircle = occ::down_cast<Handle_Geom_Circle>(gcurve);
 *    \endcode
 */

//! Construct the operator that will down cast \p object to an handle of type TYPE
template<typename TYPE>
down_cast<TYPE>::down_cast(const Handle_Standard_Transient& handle)
  : m_handle(handle)
{
}

//! Downcasted handle to type \e TYPE
template<typename TYPE>
down_cast<TYPE>::operator TYPE() const
{
  return TYPE::DownCast(m_handle);
}

//! Downcasted handle to type \e TYPE
template<typename TYPE>
const TYPE down_cast<TYPE>::operator->() const
{
  return TYPE::DownCast(m_handle);
}

} // namespace occ

// --- Related functions

namespace occ_utils_internal {

template<typename OCC_PT_VEC, typename TEXT_STREAM>
TEXT_STREAM& dumpOccPtVec(TEXT_STREAM& ts, const OCC_PT_VEC& v)
{
  return ts << "(" << v.X() << ", " << v.Y() << ", " << v.Z() << ")";
}

} // namespace occ_utils_internal

//! Print (dump) in the text stream \p ts the point \p p
template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Pnt& p)
{
  return occ_utils_internal::dumpOccPtVec(ts, p);
}

//! Print (dump) in the text stream \p ts the vector \p v
template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Vec& v)
{
  return occ_utils_internal::dumpOccPtVec(ts, v);
}

//! Print (dump) in the text stream \p ts the direction \p d
template<typename TEXT_STREAM>
TEXT_STREAM& operator<<(TEXT_STREAM& ts, const gp_Dir& d)
{
  return occ_utils_internal::dumpOccPtVec(ts, d);
}

#endif // OCC_UTILS_H

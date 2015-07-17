/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
****************************************************************************/

#pragma once

#include <Handle_Standard_Transient.hxx>

namespace occ {

/*! \brief Downcasting operator for OpenCascade handles
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
 *
 *  \ingroup occtools
 */
template<typename TYPE>
class down_cast
{
public:
    explicit down_cast<TYPE>(const Handle_Standard_Transient& handle);
    operator TYPE() const;
    const TYPE operator->() const;
private:
    const Handle_Standard_Transient& m_handle;
};



// --
// -- Implementation
// --

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

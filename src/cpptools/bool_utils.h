/****************************************************************************
**  FougTools
**  Copyright Fougue (1 Mar. 2011)
**  contact@fougsys.fr
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

namespace cpp {

/*! \brief Returns "eXclusive OR" evaluation of expressions in \p lhs and \p rhs
 *  \ingroup cpptools
 */
template <typename T>
bool boolXor(T lhs, T rhs)
{
    return (!lhs && rhs) || (lhs && !rhs);
}

/*! \brief Returns "boolean implies" evaluation of expressions in \p lhs and \p rhs
 *  \ingroup cpptools
 */
template <typename T>
bool boolImplies(T lhs, T rhs)
{
    return lhs ? rhs : true;
}

} // namespace cpp

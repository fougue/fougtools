/****************************************************************************
**  FougTools
**  Copyright Fougue (1 Mar. 2011)
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

#include <cstddef>

namespace cpp {

/*! Returns the item count in a C array (eg. "char str[128]" -> 128)
 *  \ingroup cpptools
 */
template <typename T, std::size_t N>
std::size_t cArraySize(const T (&/*array*/)[N])
{
    return N;
}

/*! Returns an iterator pointing to the end of C \p array
 *
 *  Example : "char str[128]" -> str + 128
 *  \ingroup cpptools
 */
template <typename T, std::size_t N>
T* cArrayEnd(T (&array)[N])
{
    return array + N;
}

/*! Returns a const iterator pointing to the end of C \p array
 *
 *  Example : "char str[128]" -> str + 128
 *  \ingroup cpptools
 */
template <typename T, std::size_t N>
const T* cArrayEnd(const T (&array)[N])
{
    return array + N;
}

} // namespace cpp

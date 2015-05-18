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

/*! Allows to change the value of a variable during the current scope, upon
 *  destruction, the original value is restored
 *
 * \headerfile scoped_value.h <cpptools/scoped_value.h>
 * \ingroup cpptools
 */
template<typename T>
class ScopedValue
{
public:
    ScopedValue(T& variable, T scopeValue);
    ~ScopedValue();

private:
    T m_orgValue;
    T& m_variable;
};

typedef ScopedValue<bool> ScopedBool;


// --
// -- Implementation
// --

template<typename T>
ScopedValue<T>::ScopedValue(T &variable, T scopeValue)
    : m_orgValue(variable),
      m_variable(variable)
{
    m_variable = scopeValue;
}

template<typename T>
ScopedValue<T>::~ScopedValue()
{
    m_variable = m_orgValue;
}

} // namespace cpp

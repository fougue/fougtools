/****************************************************************************
**
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

namespace cpp {

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

/*!
 *\class ScopedValue
 * \brief Allows to change the value of a variable during the current scope, upon destruction, the
 *        original value is restored
 *
 * \headerfile scoped_value.h <cpptools/scoped_value.h>
 * \ingroup cpptools
 */

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

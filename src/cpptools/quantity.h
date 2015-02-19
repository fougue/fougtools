/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
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

#ifndef CPPTOOLS_QUANTITY_H
#define CPPTOOLS_QUANTITY_H

#include "null.h"

namespace cpp {

template<typename NUMERIC_TRAITS, typename TRAIT = cpp::VoidNull>
class Quantity
{
public:
    typedef typename NUMERIC_TRAITS::Type NumericType;
    typedef Quantity<NUMERIC_TRAITS, TRAIT> QuantityType;

    Quantity();
    explicit Quantity(NumericType v);
    Quantity(const QuantityType& other);

    //operator NumericType() const;
    NumericType value() const;
    void setValue(NumericType v);

    QuantityType& operator=(const QuantityType& other);
    QuantityType& operator+=(const QuantityType& other);
    QuantityType& operator-=(const QuantityType& other);
    QuantityType& operator*=(const QuantityType& other);
    QuantityType& operator/=(const QuantityType& other);

    QuantityType& operator+=(NumericType v);
    QuantityType& operator-=(NumericType v);
    QuantityType& operator*=(NumericType v);
    QuantityType& operator/=(NumericType v);

private:
    NumericType m_value;
};

// Operator <
template<typename NUMERIC_TRAITS, typename TRAIT>
bool operator<(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
               const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

// Operator >
template<typename NUMERIC_TRAITS, typename TRAIT>
bool operator>(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
               const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

// Operator +
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                typename NUMERIC_TRAITS::Type k);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(typename NUMERIC_TRAITS::Type k,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

// Operator -
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                typename NUMERIC_TRAITS::Type k);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(typename NUMERIC_TRAITS::Type k,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

// Operator *
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                typename NUMERIC_TRAITS::Type k);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(typename NUMERIC_TRAITS::Type k,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

// Operator /
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                typename NUMERIC_TRAITS::Type k);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(typename NUMERIC_TRAITS::Type k,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename TYPE>
struct NumericTraits
{
    typedef TYPE Type;
    static TYPE zero()
    { return static_cast<TYPE>(0); }
};

typedef NumericTraits<double> DoubleNumericTraits;
typedef NumericTraits<float> FloatNumericTraits;
typedef NumericTraits<int> IntNumericTraits;

// --
// -- Implementation
// --

/*!
 * \class Quantity
 * \brief Represents an amount of a certain unit
 *
 * \headerfile quantity.h <cpptools/quantity.h>
 * \ingroup cpptools
 */

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>::Quantity()
    : m_value(NUMERIC_TRAITS::zero())
{
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>::Quantity(NumericType v)
    : m_value(v)
{
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>::Quantity(const QuantityType& other)
    : m_value(other.value())
{
}

//template<typename NUMERIC_TRAITS, typename TRAIT>
//Quantity<NUMERIC_TRAITS, TRAIT>::operator typename NUMERIC_TRAITS::Type() const
//{
//  return m_value;
//}

template<typename NUMERIC_TRAITS, typename TRAIT>
typename NUMERIC_TRAITS::Type Quantity<NUMERIC_TRAITS, TRAIT>::value() const
{
    return m_value;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
void Quantity<NUMERIC_TRAITS, TRAIT>::setValue(NumericType v)
{
    m_value = v;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator=(const QuantityType& other)
{
    if (this != &other)
        m_value = other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator+=(const QuantityType& other)
{
    if (this != &other)
        m_value += other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator-=(const QuantityType& other)
{
    if (this != &other)
        m_value -= other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator*=(const QuantityType& other)
{
    if (this != &other)
        m_value *= other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator/=(const QuantityType& other)
{
    if (this != &other)
        m_value /= other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator+=(NumericType v)
{
    m_value += v;
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator-=(NumericType v)
{
    m_value -= v;
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator*=(NumericType v)
{
    m_value *= v;
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>& Quantity<NUMERIC_TRAITS, TRAIT>::operator/=(NumericType v)
{
    m_value /= v;
    return *this;
}

// Operator <
//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
bool operator<(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
               const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    if (&lhs == &rhs)
        return false;
    return lhs.value() < rhs.value();
}

// Operator >
//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
bool operator>(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
               const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    if (&lhs == &rhs)
        return false;
    return lhs.value() > rhs.value();
}

// Operator +

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) += rhs;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                typename NUMERIC_TRAITS::Type k)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) += k;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(typename NUMERIC_TRAITS::Type k,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(rhs) += k;
}

// Operator -

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) -= rhs;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                typename NUMERIC_TRAITS::Type k)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) -= k;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(typename NUMERIC_TRAITS::Type k,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(rhs) -= k;
}

// Operator *

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) *= rhs;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                typename NUMERIC_TRAITS::Type k)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) *= k;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(typename NUMERIC_TRAITS::Type k,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(rhs) *= k;
}

// Operator /

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) /= rhs;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
                                                typename NUMERIC_TRAITS::Type k)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) /= k;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(typename NUMERIC_TRAITS::Type k,
                                                const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(rhs) /= k;
}

} // namespace cpp

#endif // CPPTOOLS_QUANTITY_H

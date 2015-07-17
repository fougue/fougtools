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

namespace cpp {

template<typename NUMERIC_TRAITS, typename TRAIT = void>
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
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        typename NUMERIC_TRAITS::Type k);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(
        typename NUMERIC_TRAITS::Type k,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

// Operator -
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        typename NUMERIC_TRAITS::Type k);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(
        typename NUMERIC_TRAITS::Type k,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

// Operator *
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        typename NUMERIC_TRAITS::Type k);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(
        typename NUMERIC_TRAITS::Type k,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

// Operator /
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        typename NUMERIC_TRAITS::Type k);

template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(
        typename NUMERIC_TRAITS::Type k,
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
Quantity<NUMERIC_TRAITS, TRAIT>&
Quantity<NUMERIC_TRAITS, TRAIT>::operator=(const QuantityType& other)
{
    if (this != &other)
        m_value = other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>&
Quantity<NUMERIC_TRAITS, TRAIT>::operator+=(const QuantityType& other)
{
    if (this != &other)
        m_value += other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>&
Quantity<NUMERIC_TRAITS, TRAIT>::operator-=(const QuantityType& other)
{
    if (this != &other)
        m_value -= other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>&
Quantity<NUMERIC_TRAITS, TRAIT>::operator*=(const QuantityType& other)
{
    if (this != &other)
        m_value *= other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>&
Quantity<NUMERIC_TRAITS, TRAIT>::operator/=(const QuantityType& other)
{
    if (this != &other)
        m_value /= other.value();
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>&
Quantity<NUMERIC_TRAITS, TRAIT>::operator+=(NumericType v)
{
    m_value += v;
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>&
Quantity<NUMERIC_TRAITS, TRAIT>::operator-=(NumericType v)
{
    m_value -= v;
    return *this;
}

template<typename NUMERIC_TRAITS, typename TRAIT>
Quantity<NUMERIC_TRAITS, TRAIT>&
Quantity<NUMERIC_TRAITS, TRAIT>::operator*=(NumericType v)
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
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) += rhs;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        typename NUMERIC_TRAITS::Type k)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) += k;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator+(
        typename NUMERIC_TRAITS::Type k,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(rhs) += k;
}

// Operator -

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) -= rhs;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        typename NUMERIC_TRAITS::Type k)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) -= k;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator-(
        typename NUMERIC_TRAITS::Type k,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(rhs) -= k;
}

// Operator *

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) *= rhs;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        typename NUMERIC_TRAITS::Type k)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) *= k;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator*(
        typename NUMERIC_TRAITS::Type k,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(rhs) *= k;
}

// Operator /

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) /= rhs;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(
        const Quantity<NUMERIC_TRAITS, TRAIT>& lhs,
        typename NUMERIC_TRAITS::Type k)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(lhs) /= k;
}

//! \relates Quantity
template<typename NUMERIC_TRAITS, typename TRAIT>
const Quantity<NUMERIC_TRAITS, TRAIT> operator/(
        typename NUMERIC_TRAITS::Type k,
        const Quantity<NUMERIC_TRAITS, TRAIT>& rhs)
{
    return Quantity<NUMERIC_TRAITS, TRAIT>(rhs) /= k;
}

} // namespace cpp

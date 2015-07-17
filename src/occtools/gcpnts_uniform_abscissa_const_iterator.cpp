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

#include "gcpnts_uniform_abscissa_const_iterator.h"

#include <GCPnts_UniformAbscissa.hxx>
#include <algorithm>
#include <cassert>

namespace occ {

/*! \class GCPnts_UniformAbscissaConstIterator
 *
 *  \headerfile gcpnts_uniform_abscissa_const_iterator.h <occtools/gcpnts_uniform_abscissa_const_iterator.h>
 *  \ingroup occtools
 */

GCPnts_UniformAbscissaConstIterator::GCPnts_UniformAbscissaConstIterator()
    : m_ua(NULL),
      m_index(1)
{
}

GCPnts_UniformAbscissaConstIterator::
GCPnts_UniformAbscissaConstIterator(const GCPnts_UniformAbscissa& ua, int index)
    : m_ua(&ua),
      m_index(index)
{
    this->limitInternalIndex();
}

double GCPnts_UniformAbscissaConstIterator::operator[](int n) const
{
    const int indexPlusN = m_index + n;
    assert(indexPlusN >= 1 && indexPlusN <= m_ua->NbPoints());
    return m_ua->Parameter(indexPlusN);
}

const GCPnts_UniformAbscissa& GCPnts_UniformAbscissaConstIterator::operator->() const
{
    return *(m_ua);
}

int GCPnts_UniformAbscissaConstIterator::index() const
{
    return m_index;
}

void GCPnts_UniformAbscissaConstIterator::limitInternalIndex()
{
    m_index = std::max(m_index, 1);
    m_index = std::min(m_index, m_ua->NbPoints() + 1);
}

// --- Related functions

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
double operator*(const GCPnts_UniformAbscissaConstIterator& i)
{
    return i.m_ua->Parameter(i.m_index);
}

/*! \brief Prefix ++ operator
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator& operator++(GCPnts_UniformAbscissaConstIterator& i)
{
    ++(i.m_index);
    i.limitInternalIndex();
    return i;
}

/*! \brief Postfix ++ operator
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator operator++(GCPnts_UniformAbscissaConstIterator& i, int /*unused*/)
{
    GCPnts_UniformAbscissaConstIterator old(i);
    ++(i.m_index);
    i.limitInternalIndex();
    return old;
}

/*! \brief Prefix -- operator
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator& operator--(GCPnts_UniformAbscissaConstIterator& i)
{
    --(i.m_index);
    i.limitInternalIndex();
    return i;
}

/*! \brief Postfix -- operator
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator operator--(GCPnts_UniformAbscissaConstIterator& i, int /*unused*/)
{
    GCPnts_UniformAbscissaConstIterator old(i);
    --(i.m_index);
    i.limitInternalIndex();
    return old;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator operator+(const GCPnts_UniformAbscissaConstIterator& i, int n)
{
    GCPnts_UniformAbscissaConstIterator newI(i);
    newI.m_index += n;
    newI.limitInternalIndex();
    return newI;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator operator+(int n, const GCPnts_UniformAbscissaConstIterator& i)
{
    return i + n;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator operator-(const GCPnts_UniformAbscissaConstIterator& i, int n)
{
    return i + (-n);
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator& operator+=(GCPnts_UniformAbscissaConstIterator& i, int n)
{
    i.m_index += n;
    i.limitInternalIndex();
    return i;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator& operator-=(GCPnts_UniformAbscissaConstIterator& i, int n)
{
    return i += (-n);
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
int operator-(const GCPnts_UniformAbscissaConstIterator& i,
              const GCPnts_UniformAbscissaConstIterator& j)
{
    return i.m_index - j.m_index;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
bool operator<(const GCPnts_UniformAbscissaConstIterator& i,
               const GCPnts_UniformAbscissaConstIterator& j)
{
    return i.m_index < j.m_index;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
bool operator>(const GCPnts_UniformAbscissaConstIterator& i,
               const GCPnts_UniformAbscissaConstIterator& j)
{
    return j < i;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
bool operator<=(const GCPnts_UniformAbscissaConstIterator& i,
                const GCPnts_UniformAbscissaConstIterator& j)
{
    return !(j < i);
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
bool operator>=(const GCPnts_UniformAbscissaConstIterator& i,
                const GCPnts_UniformAbscissaConstIterator& j)
{
    return !(i < j);
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
bool operator==(const GCPnts_UniformAbscissaConstIterator& i,
                const GCPnts_UniformAbscissaConstIterator& j)
{
    return i.m_index == j.m_index && i.m_ua == j.m_ua;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
bool operator!=(const GCPnts_UniformAbscissaConstIterator& i,
                const GCPnts_UniformAbscissaConstIterator& j)
{
    return !(i == j);
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator beginConstIterator(const GCPnts_UniformAbscissa& ua)
{
    return GCPnts_UniformAbscissaConstIterator(ua);
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator endConstIterator(const GCPnts_UniformAbscissa& ua)
{
    return GCPnts_UniformAbscissaConstIterator(ua, ua.NbPoints() + 1);
}

} // namespace occ

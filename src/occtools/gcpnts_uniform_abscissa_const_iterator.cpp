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

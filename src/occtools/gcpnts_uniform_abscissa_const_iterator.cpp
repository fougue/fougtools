#include "occtools/gcpnts_uniform_abscissa_const_iterator.h"

#include <GCPnts_UniformAbscissa.hxx>
#include <algorithm>
#include <cassert>

namespace occ {

GCPnts_UniformAbscissaConstIterator::GCPnts_UniformAbscissaConstIterator() :
  _ua(0),
  _index(1)
{
}

GCPnts_UniformAbscissaConstIterator::
GCPnts_UniformAbscissaConstIterator(const GCPnts_UniformAbscissa& ua, int index) :
  _ua(&ua),
  _index(index)
{
  this->limitInternalIndex();
}

double GCPnts_UniformAbscissaConstIterator::operator[](int n) const
{
  const int indexPlusN = _index + n;
  assert(indexPlusN >= 1 && indexPlusN <= _ua->NbPoints());
  return _ua->Parameter(indexPlusN);
}

const GCPnts_UniformAbscissa& GCPnts_UniformAbscissaConstIterator::operator->() const
{
  return *(_ua);
}

int GCPnts_UniformAbscissaConstIterator::index() const
{
  return _index;
}

void GCPnts_UniformAbscissaConstIterator::limitInternalIndex()
{
  _index = std::max(_index, 1);
  _index = std::min(_index, _ua->NbPoints() + 1);
}

// --- Related functions

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
double operator*(const GCPnts_UniformAbscissaConstIterator& i)
{
  return i._ua->Parameter(i._index);
}

/*! \brief Prefix ++ operator
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator& operator++(GCPnts_UniformAbscissaConstIterator& i)
{
  ++(i._index);
  i.limitInternalIndex();
  return i;
}

/*! \brief Postfix ++ operator
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator operator++(GCPnts_UniformAbscissaConstIterator& i, int /*unused*/)
{
  GCPnts_UniformAbscissaConstIterator old(i);
  ++(i._index);
  i.limitInternalIndex();
  return old;
}

/*! \brief Prefix -- operator
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator& operator--(GCPnts_UniformAbscissaConstIterator& i)
{
  --(i._index);
  i.limitInternalIndex();
  return i;
}

/*! \brief Postfix -- operator
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator operator--(GCPnts_UniformAbscissaConstIterator& i, int /*unused*/)
{
  GCPnts_UniformAbscissaConstIterator old(i);
  --(i._index);
  i.limitInternalIndex();
  return old;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
GCPnts_UniformAbscissaConstIterator operator+(const GCPnts_UniformAbscissaConstIterator& i, int n)
{
  GCPnts_UniformAbscissaConstIterator newI(i);
  newI._index += n;
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
  i._index += n;
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
  return i._index - j._index;
}

/*! \brief
 *  \relates GCPnts_UniformAbscissaConstIterator
 */
bool operator<(const GCPnts_UniformAbscissaConstIterator& i,
               const GCPnts_UniformAbscissaConstIterator& j)
{
  return i._index < j._index;
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
  return i._index == j._index && i._ua == j._ua;
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

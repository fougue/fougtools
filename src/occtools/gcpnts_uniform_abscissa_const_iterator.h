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

#ifndef OCC_GCPNTS_UNIFORM_ABSCISSA_CONST_ITERATOR_H
#define OCC_GCPNTS_UNIFORM_ABSCISSA_CONST_ITERATOR_H

#include "occtools.h"
#include <iterator>
class GCPnts_UniformAbscissa;

namespace occ {

class OCCTOOLS_EXPORT GCPnts_UniformAbscissaConstIterator
{
    // --- Friends
    friend double operator*(const GCPnts_UniformAbscissaConstIterator& i);
    friend GCPnts_UniformAbscissaConstIterator&
    operator++(GCPnts_UniformAbscissaConstIterator& i);
    friend GCPnts_UniformAbscissaConstIterator
    operator++(GCPnts_UniformAbscissaConstIterator& i, int unused);
    friend GCPnts_UniformAbscissaConstIterator&
    operator--(GCPnts_UniformAbscissaConstIterator& i);
    friend GCPnts_UniformAbscissaConstIterator
    operator--(GCPnts_UniformAbscissaConstIterator& i, int unused);
    friend GCPnts_UniformAbscissaConstIterator
    operator+(const GCPnts_UniformAbscissaConstIterator& i, int n);
    friend GCPnts_UniformAbscissaConstIterator
    operator+(int v, const GCPnts_UniformAbscissaConstIterator& i);
    friend GCPnts_UniformAbscissaConstIterator
    operator-(const GCPnts_UniformAbscissaConstIterator& i, int n);
    friend GCPnts_UniformAbscissaConstIterator&
    operator+=(GCPnts_UniformAbscissaConstIterator& i, int n);
    friend GCPnts_UniformAbscissaConstIterator&
    operator-=(GCPnts_UniformAbscissaConstIterator& i, int n);
    friend int operator-(const GCPnts_UniformAbscissaConstIterator& i,
                         const GCPnts_UniformAbscissaConstIterator& j);
    friend bool operator<(const GCPnts_UniformAbscissaConstIterator& i,
                          const GCPnts_UniformAbscissaConstIterator& j);
    friend bool operator>(const GCPnts_UniformAbscissaConstIterator& i,
                          const GCPnts_UniformAbscissaConstIterator& j);
    friend bool operator<=(const GCPnts_UniformAbscissaConstIterator& i,
                           const GCPnts_UniformAbscissaConstIterator& j);
    friend bool operator>=(const GCPnts_UniformAbscissaConstIterator& i,
                           const GCPnts_UniformAbscissaConstIterator& j);
    friend bool operator==(const GCPnts_UniformAbscissaConstIterator& i,
                           const GCPnts_UniformAbscissaConstIterator& j);
    friend bool operator!=(const GCPnts_UniformAbscissaConstIterator& i,
                           const GCPnts_UniformAbscissaConstIterator& j);

public:
    typedef int difference_type;
    typedef double value_type;
    typedef const double* pointer;
    typedef const double& reference;
    typedef std::random_access_iterator_tag iterator_category;

    GCPnts_UniformAbscissaConstIterator();
    GCPnts_UniformAbscissaConstIterator(const GCPnts_UniformAbscissa& ua, int index = 1);

    double operator[](int n) const;
    const GCPnts_UniformAbscissa& operator->() const;
    int index() const;

private:
    void limitInternalIndex();

    const GCPnts_UniformAbscissa* m_ua;
    int m_index;
};

// --- Related functions

double operator*(const GCPnts_UniformAbscissaConstIterator& i);

GCPnts_UniformAbscissaConstIterator&
operator++(GCPnts_UniformAbscissaConstIterator& i);

GCPnts_UniformAbscissaConstIterator
operator++(GCPnts_UniformAbscissaConstIterator& i, int /*unused*/);

GCPnts_UniformAbscissaConstIterator&
operator--(GCPnts_UniformAbscissaConstIterator& i);

GCPnts_UniformAbscissaConstIterator
operator--(GCPnts_UniformAbscissaConstIterator& i, int /*unused*/);

GCPnts_UniformAbscissaConstIterator
operator+(const GCPnts_UniformAbscissaConstIterator& i, int n);

GCPnts_UniformAbscissaConstIterator
operator+(int v, const GCPnts_UniformAbscissaConstIterator& i);

GCPnts_UniformAbscissaConstIterator
operator-(const GCPnts_UniformAbscissaConstIterator& i, int n);

GCPnts_UniformAbscissaConstIterator&
operator+=(GCPnts_UniformAbscissaConstIterator& i, int n);

GCPnts_UniformAbscissaConstIterator&
operator-=(GCPnts_UniformAbscissaConstIterator& i, int n);

int operator-(const GCPnts_UniformAbscissaConstIterator& i,
              const GCPnts_UniformAbscissaConstIterator& j);

bool operator<(const GCPnts_UniformAbscissaConstIterator& i,
               const GCPnts_UniformAbscissaConstIterator& j);

bool operator>(const GCPnts_UniformAbscissaConstIterator& i,
               const GCPnts_UniformAbscissaConstIterator& j);

bool operator<=(const GCPnts_UniformAbscissaConstIterator& i,
                const GCPnts_UniformAbscissaConstIterator& j);

bool operator>=(const GCPnts_UniformAbscissaConstIterator& i,
                const GCPnts_UniformAbscissaConstIterator& j);

bool operator==(const GCPnts_UniformAbscissaConstIterator& i,
                const GCPnts_UniformAbscissaConstIterator& j);

bool operator!=(const GCPnts_UniformAbscissaConstIterator& i,
                const GCPnts_UniformAbscissaConstIterator& j);

GCPnts_UniformAbscissaConstIterator
beginConstIterator(const GCPnts_UniformAbscissa& ua);

GCPnts_UniformAbscissaConstIterator
endConstIterator(const GCPnts_UniformAbscissa& ua);

} // namespace occ

#endif // OCC_GCPNTS_UNIFORM_ABSCISSA_CONST_ITERATOR_H

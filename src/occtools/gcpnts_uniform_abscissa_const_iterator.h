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

#pragma once

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

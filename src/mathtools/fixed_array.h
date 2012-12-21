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

#ifndef STRUCTS_FIXED_ARRAY_H
#define STRUCTS_FIXED_ARRAY_H

#include <cstddef>
#include <algorithm>
#include <iterator>

namespace structs {

// ---
// --- class FixedArray<>
// ---
template<typename T, unsigned S>
class FixedArray
{
private:
  typedef FixedArray<T, S> Self_t;

public:
  // --- STL compatibility
  typedef T* pointer;
  typedef T& reference;
  typedef T value_type;
  typedef unsigned size_type;
  typedef const T* const_pointer;
  typedef const T& const_reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::random_access_iterator_tag iterator_category;
  typedef T* iterator;
  typedef const T* const_iterator;

  // --- Lifecycle
  FixedArray<T, S>();
  FixedArray<T, S>(const Self_t& other);

  // --- Iteration
  const_iterator begin() const;
  iterator begin();
  const_iterator end() const;
  iterator end();

  // --- Measurement (STL compatibility)
  bool empty() const;
  size_type max_size() const;
  size_type size() const;

  // --- Access
  T& get(unsigned i);
  const T& get(unsigned i) const;
  T& operator[](unsigned i);
  const T& operator[](unsigned i) const;
  const T* cArray() const;
  T* cArray();

  // --- Element change
  void set(unsigned i, const T& coord);
  Self_t& operator=(const Self_t& other);

protected:
  // --- Attributes
  T _vector[S];
};

// --- Related functions
template<typename TEXT_STREAM, typename T, unsigned S>
TEXT_STREAM& operator<<(TEXT_STREAM& os, const FixedArray<T, S>& coords);

#include "fixed_array.impl.h"

} // namespace structs

#endif // STRUCTS_FIXED_ARRAY_H

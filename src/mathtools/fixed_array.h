#ifndef STRUCTS_FIXED_ARRAY_H
#define STRUCTS_FIXED_ARRAY_H

#include <cstddef>
#include <algorithm>
#include <iterator>

namespace structs {

// ---
// --- class FixedArray<>
// ---
template<typename _T_, unsigned _S_>
class FixedArray
{
private:
  typedef FixedArray<_T_, _S_> Self_t;

public:
  // --- STL compatibility
  typedef _T_* pointer;
  typedef _T_& reference;
  typedef _T_ value_type;
  typedef unsigned size_type;
  typedef const _T_* const_pointer;
  typedef const _T_& const_reference;
  typedef std::ptrdiff_t difference_type;
  typedef std::random_access_iterator_tag iterator_category;
  typedef _T_* iterator;
  typedef const _T_* const_iterator;

  // --- Lifecycle
  FixedArray<_T_, _S_>();
  FixedArray<_T_, _S_>(const Self_t& other);

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
  _T_& get(unsigned i);
  const _T_& get(unsigned i) const;
  _T_& operator[](unsigned i);
  const _T_& operator[](unsigned i) const;
  const _T_* cArray() const;
  _T_* cArray();

  // --- Element change
  void set(unsigned i, const _T_& coord);
  Self_t& operator=(const Self_t& other);

protected:
  // --- Attributes
  _T_ _vector[_S_];
};

// --- Related functions
template<typename _TEXT_STREAM_, typename _T_, unsigned _S_>
_TEXT_STREAM_& operator<<(_TEXT_STREAM_& os, const FixedArray<_T_, _S_>& coords);

#include "mathtools/fixed_array.impl.h"

} // namespace structs

#endif // STRUCTS_FIXED_ARRAY_H

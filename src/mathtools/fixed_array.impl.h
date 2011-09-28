#ifdef STRUCTS_FIXED_ARRAY_H

// ---
// --- class FixedArray<>
// ---

// --- Lifecycle

template<typename _T_, unsigned _S_>
FixedArray<_T_, _S_>::FixedArray()
{
}

template<typename _T_, unsigned _S_>
FixedArray<_T_, _S_>::FixedArray(const Self_t& other)
{
  std::copy(other.begin(), other.end(), this->begin());
}

// --- Iteration

template<typename _T_, unsigned _S_>
typename FixedArray<_T_, _S_>::const_iterator
FixedArray<_T_, _S_>::begin() const
{
  return this->_vector;
}

template<typename _T_, unsigned _S_>
typename FixedArray<_T_, _S_>::iterator
FixedArray<_T_, _S_>::begin()
{
  return this->_vector;
}

template<typename _T_, unsigned _S_>
typename FixedArray<_T_, _S_>::const_iterator
FixedArray<_T_, _S_>::end() const
{
  return this->_vector + _S_;
}

template<typename _T_, unsigned _S_>
typename FixedArray<_T_, _S_>::iterator
FixedArray<_T_, _S_>::end()
{
  return this->_vector + _S_;
}

// --- Measurement (STL compatibility)

template<typename _T_, unsigned _S_>
bool FixedArray<_T_, _S_>::empty() const
{
  return false;
}

template<typename _T_, unsigned _S_>
typename FixedArray<_T_, _S_>::size_type
FixedArray<_T_, _S_>::max_size() const
{
  return _S_;
}

template<typename _T_, unsigned _S_>
typename FixedArray<_T_, _S_>::size_type
FixedArray<_T_, _S_>::size() const
{
  return this->max_size();;
}


// --- Access

template<typename _T_, unsigned _S_>
_T_& FixedArray<_T_, _S_>::get(unsigned i)
{
  return this->_vector[i];
}

template<typename _T_, unsigned _S_>
const _T_& FixedArray<_T_, _S_>::get(unsigned i) const
{
  return this->_vector[i];
}

template<typename _T_, unsigned _S_>
_T_& FixedArray<_T_, _S_>::operator[](unsigned i)
{
  return this->get(i);
}

template<typename _T_, unsigned _S_>
const _T_& FixedArray<_T_, _S_>::operator[](unsigned i) const
{
  return this->get(i);
}

template<typename _T_, unsigned _S_>
const _T_* FixedArray<_T_, _S_>::cArray() const
{
  return &(this->_vector[0]);
}

template<typename _T_, unsigned _S_>
_T_* FixedArray<_T_, _S_>::cArray()
{
  return const_cast<_T_*>(
           static_cast<const FixedArray<_T_, _S_>*>(this)->cArray());
}

// --- Element change

template<typename _T_, unsigned _S_>
void FixedArray<_T_, _S_>::set(unsigned i, const _T_& coord)
{
  this->_vector[i] = coord;
}

template<typename _T_, unsigned _S_>
FixedArray<_T_, _S_>&
FixedArray<_T_, _S_>::operator=(const Self_t & other)
{
  if (this != &other)
    std::copy(other.begin(), other.end(), this->begin());
  return *this;
}

// --- Related functions

template<typename _TEXT_STREAM_, typename _T_, unsigned _S_>
_TEXT_STREAM_& operator<<(_TEXT_STREAM_& os,
                          const FixedArray<_T_, _S_>& coords)
{
  os << "(";
  for (unsigned i = 0; i < _S_; i++)
  {
    os << coords.get(i);
    if (i < _S_ - 1)
      os << ", ";
  }
  return os << ")";
}

#endif // STRUCTS_FIXED_ARRAY_H

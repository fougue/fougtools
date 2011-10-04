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

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

template<typename T, unsigned S>
FixedArray<T, S>::FixedArray()
{
}

template<typename T, unsigned S>
FixedArray<T, S>::FixedArray(const Self_t& other)
{
  std::copy(other.begin(), other.end(), this->begin());
}

// --- Iteration

template<typename T, unsigned S>
typename FixedArray<T, S>::const_iterator
FixedArray<T, S>::begin() const
{
  return this->_vector;
}

template<typename T, unsigned S>
typename FixedArray<T, S>::iterator
FixedArray<T, S>::begin()
{
  return this->_vector;
}

template<typename T, unsigned S>
typename FixedArray<T, S>::const_iterator
FixedArray<T, S>::end() const
{
  return this->_vector + S;
}

template<typename T, unsigned S>
typename FixedArray<T, S>::iterator
FixedArray<T, S>::end()
{
  return this->_vector + S;
}

// --- Measurement (STL compatibility)

template<typename T, unsigned S>
bool FixedArray<T, S>::empty() const
{
  return false;
}

template<typename T, unsigned S>
typename FixedArray<T, S>::size_type
FixedArray<T, S>::max_size() const
{
  return S;
}

template<typename T, unsigned S>
typename FixedArray<T, S>::size_type
FixedArray<T, S>::size() const
{
  return this->max_size();;
}


// --- Access

template<typename T, unsigned S>
T& FixedArray<T, S>::get(unsigned i)
{
  return this->_vector[i];
}

template<typename T, unsigned S>
const T& FixedArray<T, S>::get(unsigned i) const
{
  return this->_vector[i];
}

template<typename T, unsigned S>
T& FixedArray<T, S>::operator[](unsigned i)
{
  return this->get(i);
}

template<typename T, unsigned S>
const T& FixedArray<T, S>::operator[](unsigned i) const
{
  return this->get(i);
}

template<typename T, unsigned S>
const T* FixedArray<T, S>::cArray() const
{
  return &(this->_vector[0]);
}

template<typename T, unsigned S>
T* FixedArray<T, S>::cArray()
{
  return const_cast<T*>(
        static_cast<const FixedArray<T, S>*>(this)->cArray());
}

// --- Element change

template<typename T, unsigned S>
void FixedArray<T, S>::set(unsigned i, const T& coord)
{
  this->_vector[i] = coord;
}

template<typename T, unsigned S>
FixedArray<T, S>&
FixedArray<T, S>::operator=(const Self_t & other)
{
  if (this != &other)
    std::copy(other.begin(), other.end(), this->begin());
  return *this;
}

// --- Related functions

template<typename TEXT_STREAM, typename T, unsigned S>
TEXT_STREAM& operator<<(TEXT_STREAM& os,
                        const FixedArray<T, S>& coords)
{
  os << "(";
  for (unsigned i = 0; i < S; i++)
  {
    os << coords.get(i);
    if (i < S - 1)
      os << ", ";
  }
  return os << ")";
}

#endif // STRUCTS_FIXED_ARRAY_H

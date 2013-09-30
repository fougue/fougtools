/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
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

#ifndef CPPTOOLS_BASIC_SHARED_POINTER_H
#define CPPTOOLS_BASIC_SHARED_POINTER_H

#include <cstddef>

namespace cpp {

template <typename T>
class BasicSharedPointer
{
public:
  BasicSharedPointer(T* data = NULL);
  BasicSharedPointer(const BasicSharedPointer<T>& other);
  ~BasicSharedPointer();

  T& operator*() const;
  T* operator->() const;
  T* data() const;

  bool isNull() const;

  BasicSharedPointer<T>& operator=(const BasicSharedPointer<T>& other);

private:
  void addRef();
  void releaseRef();

  T* m_data;
  unsigned* m_refCount;
};

//
// Implementation
//

/*!
 * \class BasicSharedPointer
 * \brief Provides basic sharing of a pointer
 *
 * BasicSharedPointer is an automatic, shared pointer in C++. It behaves exactly like a normal
 * pointer for normal purposes, including respect for constness.
 *
 * BasicSharedPointer will delete the pointer it is holding when it goes out of scope, provided no
 * other BasicSharedPointer objects are referencing it.
 *
 * "Basic" means that there is no thread-safety or any sophisticated management. It aims to stay
 * light for simple uses.
 *
 * \headerfile basic_shared_pointer.h <cpptools/basic_shared_pointer.h>
 * \ingroup cpptools
 */

template<typename T>
BasicSharedPointer<T>::BasicSharedPointer(T* data)
  : m_data(data),
    m_refCount(new unsigned(1))
{
}

template<typename T>
BasicSharedPointer<T>::BasicSharedPointer(const BasicSharedPointer<T>& other)
  : m_data(other.m_data),
    m_refCount(other.m_refCount)
{
  this->addRef();
}

template<typename T>
BasicSharedPointer<T>::~BasicSharedPointer()
{
  this->releaseRef();
}

template<typename T>
T& BasicSharedPointer<T>::operator*() const
{
  return *m_data;
}

template<typename T>
T* BasicSharedPointer<T>::operator->() const
{
  return m_data;
}

template<typename T>
T* BasicSharedPointer<T>::data() const
{
  return m_data;
}

template<typename T>
bool BasicSharedPointer<T>::isNull() const
{
  return m_data == NULL;
}

template<typename T>
BasicSharedPointer<T>& BasicSharedPointer<T>::operator=(const BasicSharedPointer<T>& other)
{
  if (this != &other) {
    this->releaseRef();
    m_data = other.m_data;
    m_refCount = other.m_refCount;
    this->addRef();
  }
  return *this;
}

template<typename T>
void BasicSharedPointer<T>::addRef()
{
  ++(*m_refCount);
}

template<typename T>
void BasicSharedPointer<T>::releaseRef()
{
  --(*m_refCount);
  if (*m_refCount == 0) {
    delete m_data;
    delete m_refCount;
  }
}

} // namespace cpp

#endif // CPPTOOLS_BASIC_SHARED_POINTER_H

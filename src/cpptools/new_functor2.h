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

#ifndef CPPTOOLS_NEW_FUNCTOR2_H
#define CPPTOOLS_NEW_FUNCTOR2_H

#include "abstract_functor.h"

namespace cpp {

template<typename T, typename ARG1, typename ARG2, typename FUNCTION_PTR>
struct StoredFunctor2 : public AbstractFunctor2<T, ARG1, ARG2>
{
  StoredFunctor2(FUNCTION_PTR funcPtr)
    : m_funcPtr(funcPtr) { }
  T execute(ARG1 arg1, ARG2 arg2) { return m_funcPtr(arg1, arg2); }
  FUNCTION_PTR m_funcPtr;
};

template<typename T, typename ARG1, typename ARG2, typename FUNCTION_PTR>
struct StoredFunctorPtr2 : public AbstractFunctor2<T, ARG1, ARG2>
{
  StoredFunctorPtr2(FUNCTION_PTR* funcPtr)
    : m_funcPtr(funcPtr) { }
  T execute(ARG1 arg1, ARG2 arg2) { return m_funcPtr(arg1, arg2); }
  FUNCTION_PTR* m_funcPtr;
};

template <typename T, typename ARG1, typename ARG2, typename CLASS>
class StoredMemberFunctor2 : public AbstractFunctor2<T, ARG1, ARG2>
{
public:
  StoredMemberFunctor2(T (CLASS::*funcPtr)(ARG1, ARG2) , const CLASS& object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute(ARG1 arg1, ARG2 arg2)
  {
    return (m_object.*m_funcPtr)(arg1, arg2);
  }
private:
  T (CLASS::*m_funcPtr)(ARG1, ARG2) ;
  CLASS m_object;
};

template <typename T, typename ARG1, typename ARG2, typename CLASS>
class StoredConstMemberFunctor2 : public AbstractFunctor2<T, ARG1, ARG2>
{
public:
  StoredConstMemberFunctor2(T (CLASS::*funcPtr)(ARG1, ARG2) const, const CLASS& object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute(ARG1 arg1, ARG2 arg2)
  {
    return (m_object.*m_funcPtr)(arg1, arg2);
  }
private:
  T (CLASS::*m_funcPtr)(ARG1, ARG2) const;
  const CLASS m_object;
};

template <typename T, typename ARG1, typename ARG2, typename CLASS>
class StoredMemberFunctorPtr2 : public AbstractFunctor2<T, ARG1, ARG2>
{
public:
  StoredMemberFunctorPtr2(T (CLASS::*funcPtr)(ARG1, ARG2) , CLASS* object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute(ARG1 arg1, ARG2 arg2)
  {
    return (m_object->*m_funcPtr)(arg1, arg2);
  }
private:
  T (CLASS::*m_funcPtr)(ARG1, ARG2) ;
  CLASS* m_object;
};

template <typename T, typename ARG1, typename ARG2, typename CLASS>
class StoredConstMemberFunctorPtr2 : public AbstractFunctor2<T, ARG1, ARG2>
{
public:
  StoredConstMemberFunctorPtr2(T (CLASS::*funcPtr)(ARG1, ARG2) const, CLASS const* object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute(ARG1 arg1, ARG2 arg2)
  {
    return (m_object->*m_funcPtr)(arg1, arg2);
  }
private:
  T (CLASS::*m_funcPtr)(ARG1, ARG2) const;
  CLASS const* m_object;
};

template<typename T, typename ARG1, typename ARG2>
AbstractFunctor2<T, ARG1, ARG2>* newFunctor2(T (*functionPointer)(ARG1, ARG2))
{
  return new StoredFunctor2<T, ARG1, ARG2, T (*)(ARG1, ARG2)>(functionPointer);
}

template <typename T, typename ARG1, typename ARG2, typename CLASS>
AbstractFunctor2<T, ARG1, ARG2>* newFunctor2(const CLASS& object, T (CLASS::*funcPtr)(ARG1, ARG2))
{
  return new StoredMemberFunctor2<T, ARG1, ARG2, CLASS>(funcPtr, object);
}

template <typename T, typename ARG1, typename ARG2, typename CLASS>
AbstractFunctor2<T, ARG1, ARG2>* newFunctor2(const CLASS& object, T (CLASS::*funcPtr)(ARG1, ARG2) const)
{
  return new StoredConstMemberFunctor2<T, ARG1, ARG2, CLASS>(funcPtr, object);
}

template <typename T, typename ARG1, typename ARG2, typename CLASS>
AbstractFunctor2<T, ARG1, ARG2>* newFunctor2(CLASS* object, T (CLASS::*funcPtr)(ARG1, ARG2))
{
  return new StoredMemberFunctorPtr2<T, ARG1, ARG2, CLASS>(funcPtr, object);
}

template <typename T, typename ARG1, typename ARG2, typename CLASS>
AbstractFunctor2<T, ARG1, ARG2>* newFunctor2(const CLASS* object, T (CLASS::*funcPtr)(ARG1, ARG2) const)
{
  return new StoredConstMemberFunctorPtr2<T, ARG1, ARG2, CLASS>(funcPtr, object);
}

} // namespace cpp

#endif // CPPTOOLS_NEW_FUNCTOR2_H

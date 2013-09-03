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

#ifndef CPPTOOLS_NEW_FUNCTOR1_H
#define CPPTOOLS_NEW_FUNCTOR1_H

#include "abstract_functor.h"

namespace cpp {

template<typename T, typename ARG, typename FUNCTION_PTR>
struct StoredFunctor1 : public AbstractFunctor1<T, ARG>
{
  StoredFunctor1(FUNCTION_PTR funcPtr)
    : m_funcPtr(funcPtr) { }
  T execute(ARG arg) { return m_funcPtr(arg); }
  FUNCTION_PTR m_funcPtr;
};

template<typename T, typename ARG, typename FUNCTION_PTR>
struct StoredFunctorPtr1 : public AbstractFunctor1<T, ARG>
{
  StoredFunctorPtr1(FUNCTION_PTR* funcPtr)
    : m_funcPtr(funcPtr) { }
  T execute(ARG arg) { return m_funcPtr(arg); }
  FUNCTION_PTR* m_funcPtr;
};

template <typename T, typename ARG, typename CLASS>
class StoredMemberFunctor1 : public AbstractFunctor1<T, ARG>
{
public:
  StoredMemberFunctor1(T (CLASS::*funcPtr)(ARG) , const CLASS& object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute(ARG arg)
  {
    return (m_object.*m_funcPtr)(arg);
  }
private:
  T (CLASS::*m_funcPtr)(ARG);
  CLASS m_object;
};

template <typename T, typename ARG, typename CLASS>
class StoredConstMemberFunctor1 : public AbstractFunctor1<T, ARG>
{
public:
  StoredConstMemberFunctor1(T (CLASS::*funcPtr)(ARG) const, const CLASS& object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute(ARG arg)
  {
    return (m_object.*m_funcPtr)(arg);
  }
private:
  T (CLASS::*m_funcPtr)(ARG) const;
  const CLASS m_object;
};

template <typename T, typename ARG, typename CLASS>
class StoredMemberFunctorPtr1 : public AbstractFunctor1<T, ARG>
{
public:
  StoredMemberFunctorPtr1(T (CLASS::*funcPtr)(ARG) , CLASS* object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute(ARG arg)
  {
    return (m_object->*m_funcPtr)(arg);
  }
private:
  T (CLASS::*m_funcPtr)(ARG) ;
  CLASS* m_object;
};

template <typename T, typename ARG, typename CLASS>
class StoredConstMemberFunctorPtr1 : public AbstractFunctor1<T, ARG>
{
public:
  StoredConstMemberFunctorPtr1(T (CLASS::*funcPtr)(ARG) const, CLASS const* object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute(ARG arg)
  {
    return (m_object->*m_funcPtr)(arg);
  }
private:
  T (CLASS::*m_funcPtr)(ARG) const;
  CLASS const* m_object;
};

template<typename T, typename ARG>
AbstractFunctor1<T, ARG>* newFunctor1(T (*functionPointer)(ARG))
{
  return new StoredFunctor1<T, ARG, T (*)(ARG)>(functionPointer);
}

template <typename T, typename ARG, typename CLASS>
AbstractFunctor1<T, ARG>* newFunctor1(const CLASS& object, T (CLASS::*funcPtr)(ARG))
{
  return new StoredMemberFunctor1<T, ARG, CLASS>(funcPtr, object);
}

template <typename T, typename ARG, typename CLASS>
AbstractFunctor1<T, ARG>* newFunctor1(const CLASS& object, T (CLASS::*funcPtr)(ARG) const)
{
  return new StoredConstMemberFunctor1<T, ARG, CLASS>(funcPtr, object);
}

template <typename T, typename ARG, typename CLASS>
AbstractFunctor1<T, ARG>* newFunctor1(CLASS* object, T (CLASS::*funcPtr)(ARG))
{
  return new StoredMemberFunctorPtr1<T, ARG, CLASS>(funcPtr, object);
}

template <typename T, typename ARG, typename CLASS>
AbstractFunctor1<T, ARG>* newFunctor1(const CLASS* object, T (CLASS::*funcPtr)(ARG) const)
{
  return new StoredConstMemberFunctorPtr1<T, ARG, CLASS>(funcPtr, object);
}

} // namespace cpp

#endif // CPPTOOLS_NEW_FUNCTOR1_H

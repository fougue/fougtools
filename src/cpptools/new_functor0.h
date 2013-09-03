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

// Generated code, do not edit!
#ifndef CPPTOOLS_NEW_FUNCTOR0_H
#define CPPTOOLS_NEW_FUNCTOR0_H

#include "abstract_functor.h"
#include "generic_stored_functor.h"

namespace cpp {

template<typename T, typename FUNCTION_PTR>
struct StoredFunctor0_0 : public AbstractFunctor0<T>
{
  StoredFunctor0_0(FUNCTION_PTR funcPtr)
    : m_funcPtr(funcPtr) { }
  T execute() { return m_funcPtr(); }
  FUNCTION_PTR m_funcPtr;

};

template<typename T, typename FUNCTION_PTR>
struct StoredFunctorPtr0_0 : public AbstractFunctor0<T>
{
  StoredFunctorPtr0_0(FUNCTION_PTR* funcPtr)
    : m_funcPtr(funcPtr) { }
  T execute() { return m_funcPtr(); }
  FUNCTION_PTR* m_funcPtr;

};

template <typename T, typename CLASS>
class StoredMemberFunctor0_0 : public AbstractFunctor0<T>
{
public:
  StoredMemberFunctor0_0(T (CLASS::*funcPtr)() , const CLASS& object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute()
  {
    return (m_object.*m_funcPtr)();
  }
private:
  T (CLASS::*m_funcPtr)() ;
  CLASS m_object;

};

template <typename T, typename CLASS>
class StoredConstMemberFunctor0_0 : public AbstractFunctor0<T>
{
public:
  StoredConstMemberFunctor0_0(T (CLASS::*funcPtr)() const, const CLASS& object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute()
  {
    return (m_object.*m_funcPtr)();
  }
private:
  T (CLASS::*m_funcPtr)() const;
  const CLASS m_object;

};

template <typename T, typename CLASS>
class StoredMemberFunctorPtr0_0 : public AbstractFunctor0<T>
{
public:
  StoredMemberFunctorPtr0_0(T (CLASS::*funcPtr)() , CLASS* object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute()
  {
    return (m_object->*m_funcPtr)();
  }
private:
  T (CLASS::*m_funcPtr)() ;
  CLASS* m_object;

};

template <typename T, typename CLASS>
class StoredConstMemberFunctorPtr0_0 : public AbstractFunctor0<T>
{
public:
  StoredConstMemberFunctorPtr0_0(T (CLASS::*funcPtr)() const, CLASS const* object)
    : m_funcPtr(funcPtr), m_object(object) { }

  T execute()
  {
    return (m_object->*m_funcPtr)();
  }
private:
  T (CLASS::*m_funcPtr)() const;
  CLASS const* m_object;

};

template<typename T, typename FUNCTION_PTR, typename ARG1>
struct StoredFunctor0_1 : public AbstractFunctor0<T>
{
  StoredFunctor0_1(FUNCTION_PTR funcPtr, const ARG1 &arg1)
    : m_funcPtr(funcPtr), m_arg1(arg1) { }
  T execute() { return m_funcPtr(m_arg1); }
  FUNCTION_PTR m_funcPtr;
  ARG1 m_arg1;
};

template<typename T, typename FUNCTION_PTR, typename ARG1>
struct StoredFunctorPtr0_1 : public AbstractFunctor0<T>
{
  StoredFunctorPtr0_1(FUNCTION_PTR* funcPtr, const ARG1 &arg1)
    : m_funcPtr(funcPtr), m_arg1(arg1) { }
  T execute() { return m_funcPtr(m_arg1); }
  FUNCTION_PTR* m_funcPtr;
  ARG1 m_arg1;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
class StoredMemberFunctor0_1 : public AbstractFunctor0<T>
{
public:
  StoredMemberFunctor0_1(T (CLASS::*funcPtr)(PARAM1) , const CLASS& object, const ARG1 &arg1)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1) { }

  T execute()
  {
    return (m_object.*m_funcPtr)(m_arg1);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1) ;
  CLASS m_object;
  ARG1 m_arg1;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
class StoredConstMemberFunctor0_1 : public AbstractFunctor0<T>
{
public:
  StoredConstMemberFunctor0_1(T (CLASS::*funcPtr)(PARAM1) const, const CLASS& object, const ARG1 &arg1)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1) { }

  T execute()
  {
    return (m_object.*m_funcPtr)(m_arg1);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1) const;
  const CLASS m_object;
  ARG1 m_arg1;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
class StoredMemberFunctorPtr0_1 : public AbstractFunctor0<T>
{
public:
  StoredMemberFunctorPtr0_1(T (CLASS::*funcPtr)(PARAM1) , CLASS* object, const ARG1 &arg1)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1) { }

  T execute()
  {
    return (m_object->*m_funcPtr)(m_arg1);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1) ;
  CLASS* m_object;
  ARG1 m_arg1;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
class StoredConstMemberFunctorPtr0_1 : public AbstractFunctor0<T>
{
public:
  StoredConstMemberFunctorPtr0_1(T (CLASS::*funcPtr)(PARAM1) const, CLASS const* object, const ARG1 &arg1)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1) { }

  T execute()
  {
    return (m_object->*m_funcPtr)(m_arg1);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1) const;
  CLASS const* m_object;
  ARG1 m_arg1;
};

template<typename T, typename FUNCTION_PTR, typename ARG1, typename ARG2>
struct StoredFunctor0_2 : public AbstractFunctor0<T>
{
  StoredFunctor0_2(FUNCTION_PTR funcPtr, const ARG1 &arg1, const ARG2 &arg2)
    : m_funcPtr(funcPtr), m_arg1(arg1), m_arg2(arg2) { }
  T execute() { return m_funcPtr(m_arg1, m_arg2); }
  FUNCTION_PTR m_funcPtr;
  ARG1 m_arg1; ARG2 m_arg2;
};

template<typename T, typename FUNCTION_PTR, typename ARG1, typename ARG2>
struct StoredFunctorPtr0_2 : public AbstractFunctor0<T>
{
  StoredFunctorPtr0_2(FUNCTION_PTR* funcPtr, const ARG1 &arg1, const ARG2 &arg2)
    : m_funcPtr(funcPtr), m_arg1(arg1), m_arg2(arg2) { }
  T execute() { return m_funcPtr(m_arg1, m_arg2); }
  FUNCTION_PTR* m_funcPtr;
  ARG1 m_arg1; ARG2 m_arg2;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
class StoredMemberFunctor0_2 : public AbstractFunctor0<T>
{
public:
  StoredMemberFunctor0_2(T (CLASS::*funcPtr)(PARAM1, PARAM2) , const CLASS& object, const ARG1 &arg1, const ARG2 &arg2)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1), m_arg2(arg2) { }

  T execute()
  {
    return (m_object.*m_funcPtr)(m_arg1, m_arg2);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1, PARAM2) ;
  CLASS m_object;
  ARG1 m_arg1; ARG2 m_arg2;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
class StoredConstMemberFunctor0_2 : public AbstractFunctor0<T>
{
public:
  StoredConstMemberFunctor0_2(T (CLASS::*funcPtr)(PARAM1, PARAM2) const, const CLASS& object, const ARG1 &arg1, const ARG2 &arg2)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1), m_arg2(arg2) { }

  T execute()
  {
    return (m_object.*m_funcPtr)(m_arg1, m_arg2);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1, PARAM2) const;
  const CLASS m_object;
  ARG1 m_arg1; ARG2 m_arg2;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
class StoredMemberFunctorPtr0_2 : public AbstractFunctor0<T>
{
public:
  StoredMemberFunctorPtr0_2(T (CLASS::*funcPtr)(PARAM1, PARAM2) , CLASS* object, const ARG1 &arg1, const ARG2 &arg2)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1), m_arg2(arg2) { }

  T execute()
  {
    return (m_object->*m_funcPtr)(m_arg1, m_arg2);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1, PARAM2) ;
  CLASS* m_object;
  ARG1 m_arg1; ARG2 m_arg2;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
class StoredConstMemberFunctorPtr0_2 : public AbstractFunctor0<T>
{
public:
  StoredConstMemberFunctorPtr0_2(T (CLASS::*funcPtr)(PARAM1, PARAM2) const, CLASS const* object, const ARG1 &arg1, const ARG2 &arg2)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1), m_arg2(arg2) { }

  T execute()
  {
    return (m_object->*m_funcPtr)(m_arg1, m_arg2);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1, PARAM2) const;
  CLASS const* m_object;
  ARG1 m_arg1; ARG2 m_arg2;
};

template<typename T, typename FUNCTION_PTR, typename ARG1, typename ARG2, typename ARG3>
struct StoredFunctor0_3 : public AbstractFunctor0<T>
{
  StoredFunctor0_3(FUNCTION_PTR funcPtr, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
    : m_funcPtr(funcPtr), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }
  T execute() { return m_funcPtr(m_arg1, m_arg2, m_arg3); }
  FUNCTION_PTR m_funcPtr;
  ARG1 m_arg1; ARG2 m_arg2; ARG3 m_arg3;
};

template<typename T, typename FUNCTION_PTR, typename ARG1, typename ARG2, typename ARG3>
struct StoredFunctorPtr0_3 : public AbstractFunctor0<T>
{
  StoredFunctorPtr0_3(FUNCTION_PTR* funcPtr, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
    : m_funcPtr(funcPtr), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }
  T execute() { return m_funcPtr(m_arg1, m_arg2, m_arg3); }
  FUNCTION_PTR* m_funcPtr;
  ARG1 m_arg1; ARG2 m_arg2; ARG3 m_arg3;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
class StoredMemberFunctor0_3 : public AbstractFunctor0<T>
{
public:
  StoredMemberFunctor0_3(T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) , const CLASS& object, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }

  T execute()
  {
    return (m_object.*m_funcPtr)(m_arg1, m_arg2, m_arg3);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1, PARAM2, PARAM3) ;
  CLASS m_object;
  ARG1 m_arg1; ARG2 m_arg2; ARG3 m_arg3;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
class StoredConstMemberFunctor0_3 : public AbstractFunctor0<T>
{
public:
  StoredConstMemberFunctor0_3(T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, const CLASS& object, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }

  T execute()
  {
    return (m_object.*m_funcPtr)(m_arg1, m_arg2, m_arg3);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1, PARAM2, PARAM3) const;
  const CLASS m_object;
  ARG1 m_arg1; ARG2 m_arg2; ARG3 m_arg3;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
class StoredMemberFunctorPtr0_3 : public AbstractFunctor0<T>
{
public:
  StoredMemberFunctorPtr0_3(T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) , CLASS* object, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }

  T execute()
  {
    return (m_object->*m_funcPtr)(m_arg1, m_arg2, m_arg3);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1, PARAM2, PARAM3) ;
  CLASS* m_object;
  ARG1 m_arg1; ARG2 m_arg2; ARG3 m_arg3;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
class StoredConstMemberFunctorPtr0_3 : public AbstractFunctor0<T>
{
public:
  StoredConstMemberFunctorPtr0_3(T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, CLASS const* object, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
    : m_funcPtr(funcPtr), m_object(object), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }

  T execute()
  {
    return (m_object->*m_funcPtr)(m_arg1, m_arg2, m_arg3);
  }
private:
  T (CLASS::*m_funcPtr)(PARAM1, PARAM2, PARAM3) const;
  CLASS const* m_object;
  ARG1 m_arg1; ARG2 m_arg2; ARG3 m_arg3;
};

template<typename T>
AbstractFunctor0<T>* newFunctor0(T (*functionPointer)())
{
  return new StoredFunctor0_0<T, T (*)()>(functionPointer);
}

template<typename T, typename PARAM1, typename ARG1>
AbstractFunctor0<T>* newFunctor0(T (*functionPointer)(PARAM1), const ARG1 &arg1)
{
  return new StoredFunctor0_1<T, T (*)(PARAM1), ARG1>(functionPointer, arg1);
}

template<typename T, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor0<T>* newFunctor0(T (*functionPointer)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
{
  return new StoredFunctor0_2<T, T (*)(PARAM1, PARAM2), ARG1, ARG2>(functionPointer, arg1, arg2);
}

template<typename T, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor0<T>* newFunctor0(T (*functionPointer)(PARAM1, PARAM2, PARAM3), const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
  return new StoredFunctor0_3<T, T (*)(PARAM1, PARAM2, PARAM3), ARG1, ARG2, ARG3>(functionPointer, arg1, arg2, arg3);
}


template <typename T, typename CLASS>
AbstractFunctor0<T>* newFunctor0(const CLASS& object, T (CLASS::*funcPtr)())
{
  return new StoredMemberFunctor0_0<T, CLASS>(funcPtr, object);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
AbstractFunctor0<T>* newFunctor0(const CLASS& object, T (CLASS::*funcPtr)(PARAM1), const ARG1 &arg1)
{
  return new StoredMemberFunctor0_1<T, CLASS, PARAM1, ARG1>(funcPtr, object, arg1);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor0<T>* newFunctor0(const CLASS& object, T (CLASS::*funcPtr)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
{
  return new StoredMemberFunctor0_2<T, CLASS, PARAM1, ARG1, PARAM2, ARG2>(funcPtr, object, arg1, arg2);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor0<T>* newFunctor0(const CLASS& object, T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3), const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
  return new StoredMemberFunctor0_3<T, CLASS, PARAM1, ARG1, PARAM2, ARG2, PARAM3, ARG3>(funcPtr, object, arg1, arg2, arg3);
}


template <typename T, typename CLASS>
AbstractFunctor0<T>* newFunctor0(const CLASS& object, T (CLASS::*funcPtr)() const)
{
  return new StoredConstMemberFunctor0_0<T, CLASS>(funcPtr, object);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
AbstractFunctor0<T>* newFunctor0(const CLASS& object, T (CLASS::*funcPtr)(PARAM1) const, const ARG1 &arg1)
{
  return new StoredConstMemberFunctor0_1<T, CLASS, PARAM1, ARG1>(funcPtr, object, arg1);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor0<T>* newFunctor0(const CLASS& object, T (CLASS::*funcPtr)(PARAM1, PARAM2) const, const ARG1 &arg1, const ARG2 &arg2)
{
  return new StoredConstMemberFunctor0_2<T, CLASS, PARAM1, ARG1, PARAM2, ARG2>(funcPtr, object, arg1, arg2);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor0<T>* newFunctor0(const CLASS& object, T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
  return new StoredConstMemberFunctor0_3<T, CLASS, PARAM1, ARG1, PARAM2, ARG2, PARAM3, ARG3>(funcPtr, object, arg1, arg2, arg3);
}


template <typename T, typename CLASS>
AbstractFunctor0<T>* newFunctor0(CLASS* object, T (CLASS::*funcPtr)())
{
  return new StoredMemberFunctorPtr0_0<T, CLASS>(funcPtr, object);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
AbstractFunctor0<T>* newFunctor0(CLASS* object, T (CLASS::*funcPtr)(PARAM1), const ARG1 &arg1)
{
  return new StoredMemberFunctorPtr0_1<T, CLASS, PARAM1, ARG1>(funcPtr, object, arg1);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor0<T>* newFunctor0(CLASS* object, T (CLASS::*funcPtr)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
{
  return new StoredMemberFunctorPtr0_2<T, CLASS, PARAM1, ARG1, PARAM2, ARG2>(funcPtr, object, arg1, arg2);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor0<T>* newFunctor0(CLASS* object, T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3), const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
  return new StoredMemberFunctorPtr0_3<T, CLASS, PARAM1, ARG1, PARAM2, ARG2, PARAM3, ARG3>(funcPtr, object, arg1, arg2, arg3);
}


template <typename T, typename CLASS>
AbstractFunctor0<T>* newFunctor0(const CLASS* object, T (CLASS::*funcPtr)() const)
{
  return new StoredConstMemberFunctorPtr0_0<T, CLASS>(funcPtr, object);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
AbstractFunctor0<T>* newFunctor0(const CLASS* object, T (CLASS::*funcPtr)(PARAM1) const, const ARG1 &arg1)
{
  return new StoredConstMemberFunctorPtr0_1<T, CLASS, PARAM1, ARG1>(funcPtr, object, arg1);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor0<T>* newFunctor0(const CLASS* object, T (CLASS::*funcPtr)(PARAM1, PARAM2) const, const ARG1 &arg1, const ARG2 &arg2)
{
  return new StoredConstMemberFunctorPtr0_2<T, CLASS, PARAM1, ARG1, PARAM2, ARG2>(funcPtr, object, arg1, arg2);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor0<T>* newFunctor0(const CLASS* object, T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
  return new StoredConstMemberFunctorPtr0_3<T, CLASS, PARAM1, ARG1, PARAM2, ARG2, PARAM3, ARG3>(funcPtr, object, arg1, arg2, arg3);
}


} // namespace cpp

#endif // CPPTOOLS_NEW_FUNCTOR0_H

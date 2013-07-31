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
#ifndef CPPTOOLS_NEW_FUNCTOR_H
#define CPPTOOLS_NEW_FUNCTOR_H

#include "abstract_functor.h"

namespace cpp {

template<typename T, typename FUNCTION_PTR>
struct StoredFunctor0 : public AbstractFunctor<T>
{
  StoredFunctor0(FUNCTION_PTR funcPtr)
    : m_funcPtr(funcPtr) { }
  T execute() { return m_funcPtr(); }
  FUNCTION_PTR m_funcPtr;

};

template<typename T, typename FUNCTION_PTR>
struct StoredFunctorPtr0 : public AbstractFunctor<T>
{
  StoredFunctorPtr0(FUNCTION_PTR* funcPtr)
    : m_funcPtr(funcPtr) { }
  T execute() { return m_funcPtr(); }
  FUNCTION_PTR* m_funcPtr;

};

template <typename T, typename CLASS>
class StoredMemberFunctor0 : public AbstractFunctor<T>
{
public:
  StoredMemberFunctor0(T (CLASS::*funcPtr)() , const CLASS& object)
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
class StoredConstMemberFunctor0 : public AbstractFunctor<T>
{
public:
  StoredConstMemberFunctor0(T (CLASS::*funcPtr)() const, const CLASS& object)
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
class StoredMemberFunctorPtr0 : public AbstractFunctor<T>
{
public:
  StoredMemberFunctorPtr0(T (CLASS::*funcPtr)() , CLASS* object)
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
class StoredConstMemberFunctorPtr0 : public AbstractFunctor<T>
{
public:
  StoredConstMemberFunctorPtr0(T (CLASS::*funcPtr)() const, CLASS const* object)
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
struct StoredFunctor1 : public AbstractFunctor<T>
{
  StoredFunctor1(FUNCTION_PTR funcPtr, const ARG1 &arg1)
    : m_funcPtr(funcPtr), m_arg1(arg1) { }
  T execute() { return m_funcPtr(m_arg1); }
  FUNCTION_PTR m_funcPtr;
  ARG1 m_arg1;
};

template<typename T, typename FUNCTION_PTR, typename ARG1>
struct StoredFunctorPtr1 : public AbstractFunctor<T>
{
  StoredFunctorPtr1(FUNCTION_PTR* funcPtr, const ARG1 &arg1)
    : m_funcPtr(funcPtr), m_arg1(arg1) { }
  T execute() { return m_funcPtr(m_arg1); }
  FUNCTION_PTR* m_funcPtr;
  ARG1 m_arg1;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
class StoredMemberFunctor1 : public AbstractFunctor<T>
{
public:
  StoredMemberFunctor1(T (CLASS::*funcPtr)(PARAM1) , const CLASS& object, const ARG1 &arg1)
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
class StoredConstMemberFunctor1 : public AbstractFunctor<T>
{
public:
  StoredConstMemberFunctor1(T (CLASS::*funcPtr)(PARAM1) const, const CLASS& object, const ARG1 &arg1)
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
class StoredMemberFunctorPtr1 : public AbstractFunctor<T>
{
public:
  StoredMemberFunctorPtr1(T (CLASS::*funcPtr)(PARAM1) , CLASS* object, const ARG1 &arg1)
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
class StoredConstMemberFunctorPtr1 : public AbstractFunctor<T>
{
public:
  StoredConstMemberFunctorPtr1(T (CLASS::*funcPtr)(PARAM1) const, CLASS const* object, const ARG1 &arg1)
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
struct StoredFunctor2 : public AbstractFunctor<T>
{
  StoredFunctor2(FUNCTION_PTR funcPtr, const ARG1 &arg1, const ARG2 &arg2)
    : m_funcPtr(funcPtr), m_arg1(arg1), m_arg2(arg2) { }
  T execute() { return m_funcPtr(m_arg1, m_arg2); }
  FUNCTION_PTR m_funcPtr;
  ARG1 m_arg1; ARG2 m_arg2;
};

template<typename T, typename FUNCTION_PTR, typename ARG1, typename ARG2>
struct StoredFunctorPtr2 : public AbstractFunctor<T>
{
  StoredFunctorPtr2(FUNCTION_PTR* funcPtr, const ARG1 &arg1, const ARG2 &arg2)
    : m_funcPtr(funcPtr), m_arg1(arg1), m_arg2(arg2) { }
  T execute() { return m_funcPtr(m_arg1, m_arg2); }
  FUNCTION_PTR* m_funcPtr;
  ARG1 m_arg1; ARG2 m_arg2;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
class StoredMemberFunctor2 : public AbstractFunctor<T>
{
public:
  StoredMemberFunctor2(T (CLASS::*funcPtr)(PARAM1, PARAM2) , const CLASS& object, const ARG1 &arg1, const ARG2 &arg2)
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
class StoredConstMemberFunctor2 : public AbstractFunctor<T>
{
public:
  StoredConstMemberFunctor2(T (CLASS::*funcPtr)(PARAM1, PARAM2) const, const CLASS& object, const ARG1 &arg1, const ARG2 &arg2)
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
class StoredMemberFunctorPtr2 : public AbstractFunctor<T>
{
public:
  StoredMemberFunctorPtr2(T (CLASS::*funcPtr)(PARAM1, PARAM2) , CLASS* object, const ARG1 &arg1, const ARG2 &arg2)
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
class StoredConstMemberFunctorPtr2 : public AbstractFunctor<T>
{
public:
  StoredConstMemberFunctorPtr2(T (CLASS::*funcPtr)(PARAM1, PARAM2) const, CLASS const* object, const ARG1 &arg1, const ARG2 &arg2)
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
struct StoredFunctor3 : public AbstractFunctor<T>
{
  StoredFunctor3(FUNCTION_PTR funcPtr, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
    : m_funcPtr(funcPtr), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }
  T execute() { return m_funcPtr(m_arg1, m_arg2, m_arg3); }
  FUNCTION_PTR m_funcPtr;
  ARG1 m_arg1; ARG2 m_arg2; ARG3 m_arg3;
};

template<typename T, typename FUNCTION_PTR, typename ARG1, typename ARG2, typename ARG3>
struct StoredFunctorPtr3 : public AbstractFunctor<T>
{
  StoredFunctorPtr3(FUNCTION_PTR* funcPtr, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
    : m_funcPtr(funcPtr), m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) { }
  T execute() { return m_funcPtr(m_arg1, m_arg2, m_arg3); }
  FUNCTION_PTR* m_funcPtr;
  ARG1 m_arg1; ARG2 m_arg2; ARG3 m_arg3;
};

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
class StoredMemberFunctor3 : public AbstractFunctor<T>
{
public:
  StoredMemberFunctor3(T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) , const CLASS& object, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
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
class StoredConstMemberFunctor3 : public AbstractFunctor<T>
{
public:
  StoredConstMemberFunctor3(T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, const CLASS& object, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
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
class StoredMemberFunctorPtr3 : public AbstractFunctor<T>
{
public:
  StoredMemberFunctorPtr3(T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) , CLASS* object, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
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
class StoredConstMemberFunctorPtr3 : public AbstractFunctor<T>
{
public:
  StoredConstMemberFunctorPtr3(T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, CLASS const* object, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
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
AbstractFunctor<T>* newFunctor(T (*functionPointer)())
{
  return new StoredFunctor0<T, T (*)()>(functionPointer);
}

template<typename T, typename PARAM1, typename ARG1>
AbstractFunctor<T>* newFunctor(T (*functionPointer)(PARAM1), const ARG1 &arg1)
{
  return new StoredFunctor1<T, T (*)(PARAM1), ARG1>(functionPointer, arg1);
}

template<typename T, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor<T>* newFunctor(T (*functionPointer)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
{
  return new StoredFunctor2<T, T (*)(PARAM1, PARAM2), ARG1, ARG2>(functionPointer, arg1, arg2);
}

template<typename T, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor<T>* newFunctor(T (*functionPointer)(PARAM1, PARAM2, PARAM3), const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
  return new StoredFunctor3<T, T (*)(PARAM1, PARAM2, PARAM3), ARG1, ARG2, ARG3>(functionPointer, arg1, arg2, arg3);
}


template <typename T, typename CLASS>
AbstractFunctor<T>* newFunctor(const CLASS& object, T (CLASS::*funcPtr)())
{
    return new StoredMemberFunctor0<T, CLASS>(funcPtr, object);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
AbstractFunctor<T>* newFunctor(const CLASS& object, T (CLASS::*funcPtr)(PARAM1), const ARG1 &arg1)
{
    return new StoredMemberFunctor1<T, CLASS, PARAM1, ARG1>(funcPtr, object, arg1);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor<T>* newFunctor(const CLASS& object, T (CLASS::*funcPtr)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
{
    return new StoredMemberFunctor2<T, CLASS, PARAM1, ARG1, PARAM2, ARG2>(funcPtr, object, arg1, arg2);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor<T>* newFunctor(const CLASS& object, T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3), const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
    return new StoredMemberFunctor3<T, CLASS, PARAM1, ARG1, PARAM2, ARG2, PARAM3, ARG3>(funcPtr, object, arg1, arg2, arg3);
}


template <typename T, typename CLASS>
AbstractFunctor<T>* newFunctor(const CLASS& object, T (CLASS::*funcPtr)() const)
{
    return new StoredConstMemberFunctor0<T, CLASS>(funcPtr, object);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
AbstractFunctor<T>* newFunctor(const CLASS& object, T (CLASS::*funcPtr)(PARAM1) const, const ARG1 &arg1)
{
    return new StoredConstMemberFunctor1<T, CLASS, PARAM1, ARG1>(funcPtr, object, arg1);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor<T>* newFunctor(const CLASS& object, T (CLASS::*funcPtr)(PARAM1, PARAM2) const, const ARG1 &arg1, const ARG2 &arg2)
{
    return new StoredConstMemberFunctor2<T, CLASS, PARAM1, ARG1, PARAM2, ARG2>(funcPtr, object, arg1, arg2);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor<T>* newFunctor(const CLASS& object, T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
    return new StoredConstMemberFunctor3<T, CLASS, PARAM1, ARG1, PARAM2, ARG2, PARAM3, ARG3>(funcPtr, object, arg1, arg2, arg3);
}


template <typename T, typename CLASS>
AbstractFunctor<T>* newFunctor(CLASS* object, T (CLASS::*funcPtr)())
{
    return new StoredMemberFunctorPtr0<T, CLASS>(funcPtr, object);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
AbstractFunctor<T>* newFunctor(CLASS* object, T (CLASS::*funcPtr)(PARAM1), const ARG1 &arg1)
{
    return new StoredMemberFunctorPtr1<T, CLASS, PARAM1, ARG1>(funcPtr, object, arg1);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor<T>* newFunctor(CLASS* object, T (CLASS::*funcPtr)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
{
    return new StoredMemberFunctorPtr2<T, CLASS, PARAM1, ARG1, PARAM2, ARG2>(funcPtr, object, arg1, arg2);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor<T>* newFunctor(CLASS* object, T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3), const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
    return new StoredMemberFunctorPtr3<T, CLASS, PARAM1, ARG1, PARAM2, ARG2, PARAM3, ARG3>(funcPtr, object, arg1, arg2, arg3);
}


template <typename T, typename CLASS>
AbstractFunctor<T>* newFunctor(const CLASS* object, T (CLASS::*funcPtr)() const)
{
    return new StoredConstMemberFunctorPtr0<T, CLASS>(funcPtr, object);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1>
AbstractFunctor<T>* newFunctor(const CLASS* object, T (CLASS::*funcPtr)(PARAM1) const, const ARG1 &arg1)
{
    return new StoredConstMemberFunctorPtr1<T, CLASS, PARAM1, ARG1>(funcPtr, object, arg1);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
AbstractFunctor<T>* newFunctor(const CLASS* object, T (CLASS::*funcPtr)(PARAM1, PARAM2) const, const ARG1 &arg1, const ARG2 &arg2)
{
    return new StoredConstMemberFunctorPtr2<T, CLASS, PARAM1, ARG1, PARAM2, ARG2>(funcPtr, object, arg1, arg2);
}

template <typename T, typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
AbstractFunctor<T>* newFunctor(const CLASS* object, T (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
{
    return new StoredConstMemberFunctorPtr3<T, CLASS, PARAM1, ARG1, PARAM2, ARG2, PARAM3, ARG3>(funcPtr, object, arg1, arg2, arg3);
}

} // namespace cpp

#endif // CPPTOOLS_NEW_FUNCTOR_H

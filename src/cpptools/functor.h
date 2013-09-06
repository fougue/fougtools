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

#ifndef CPPTOOLS_FUNCTOR_H
#define CPPTOOLS_FUNCTOR_H

#include <cstddef>
#include <cstring>

#include "basic_shared_pointer.h"
#include "functor0_bind.h"

namespace cpp {

// Based on "CALLBACKS IN C++ USING TEMPLATE FUNCTORS" by Rich Hickey
// http://www.tutok.sk/fastgl/callback.html

//! Typeless representation of a function and optional object
class FunctorBase{
public:
  typedef void (FunctorBase::*MemberFunctionPtr)();

  FunctorBase()
    : m_callee(NULL),
      m_func(NULL)
  { }

  FunctorBase(const void *c, const void *f, std::size_t sz)
  {
    if (c != NULL) {// must be callee/memfunc
      m_callee = (void *)c;
      std::memcpy(m_memFunc, f, sz);
    }
    else { //must be ptr-to-func
      m_func = f;
    }
  }

  // For evaluation in conditionals
  bool isValid() const
  {
    return m_func != NULL || m_callee != NULL;
  }

  ////////////////////////////////////////////////////////////////
  // Note: this code depends on all ptr-to-mem-funcs being same size
  // If that is not the case then make memFunc as large as largest
  ////////////////////////////////////////////////////////////////

  void* m_callee;
  union
  {
    const void* m_func;
    char m_memFunc[sizeof(MemberFunctionPtr)];
  };
};

//! Functor0
template <typename RESULT_TYPE>
class Functor0 : protected FunctorBase
{
public:
  typedef RESULT_TYPE result_type;

  Functor0()
    : m_thunk(NULL)
  { }

  RESULT_TYPE execute() const
  {
    return m_thunk(*this);
  }

  RESULT_TYPE operator()() const
  {
    return m_thunk(*this);
  }

  using FunctorBase::isValid;

  // Free function
  template<typename TRT>
  static Functor0 make(TRT (*f)())
  {
    return Functor0(&Functor0::freeFunctionThunk<TRT (*)()>, NULL, (const void*)f, 0);
  }

  // Member function
  template<typename CLASS, typename TRT, class CALL_TYPE>
  static Functor0 make(CLASS* object, TRT (CALL_TYPE::* const &f)())
  {
    typedef TRT (CALL_TYPE::*MemFunc)();
    return Functor0(&Functor0::classMemberFunctionThunk<CLASS, MemFunc>, object, &f, sizeof(MemFunc));
  }

  // Const member function
  template<typename CLASS, typename TRT, class CALL_TYPE>
  static Functor0 make(const CLASS* object, TRT (CALL_TYPE::* const &f)() const)
  {
    typedef TRT (CALL_TYPE::*MemFunc)() const;
    return Functor0(&Functor0::classMemberFunctionThunk<CLASS, MemFunc>, object, &f, sizeof(MemFunc));
  }

  // Free function binders
  template<typename PARAM1, typename ARG1>
  static Functor0 make(RESULT_TYPE (*funcPtr)(PARAM1), const ARG1 &arg1)
  {
    return Functor0(internal::newFunctor0(funcPtr, arg1));
  }

  template<typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
  static Functor0 make(RESULT_TYPE (*funcPtr)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
  {
    return Functor0(internal::newFunctor0(funcPtr, arg1, arg2));
  }

  template<typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
  static Functor0 make(RESULT_TYPE (*funcPtr)(PARAM1, PARAM2, PARAM3), const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
  {
    return Functor0(internal::newFunctor0(funcPtr, arg1, arg2, arg3));
  }

  // Member function binders
  template <typename CLASS, typename PARAM1, typename ARG1>
  static Functor0 make(CLASS* object, RESULT_TYPE (CLASS::*funcPtr)(PARAM1), const ARG1 &arg1)
  {
    return Functor0(internal::newFunctor0(object, funcPtr, arg1));
  }

  template <typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
  static Functor0 make(CLASS* object, RESULT_TYPE (CLASS::*funcPtr)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
  {
    return Functor0(internal::newFunctor0(object, funcPtr, arg1, arg2));
  }

  template <typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
  static Functor0 make(CLASS* object, RESULT_TYPE (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3), const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
  {
    return Functor0(internal::newFunctor0(object, funcPtr, arg1, arg2, arg3));
  }

  // Const member function binders
  template <typename CLASS, typename PARAM1, typename ARG1>
  static Functor0 make(const CLASS* object, RESULT_TYPE (CLASS::*funcPtr)(PARAM1) const, const ARG1 &arg1)
  {
    return Functor0(internal::newFunctor0(object, funcPtr, arg1));
  }

  template <typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
  static Functor0 make(const CLASS* object, RESULT_TYPE (CLASS::*funcPtr)(PARAM1, PARAM2) const, const ARG1 &arg1, const ARG2 &arg2)
  {
    return Functor0(internal::newFunctor0(object, funcPtr, arg1, arg2));
  }

  template <typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2, typename PARAM3, typename ARG3>
  static Functor0 make(const CLASS* object, RESULT_TYPE (CLASS::*funcPtr)(PARAM1, PARAM2, PARAM3) const, const ARG1 &arg1, const ARG2 &arg2, const ARG3 &arg3)
  {
    return Functor0(internal::newFunctor0(object, funcPtr, arg1, arg2, arg3));
  }

  // Implementation
private:
  typedef RESULT_TYPE (*Thunk)(const Functor0&);
  Functor0(Thunk t, const void* c, const void* f, std::size_t sz)
    : FunctorBase(c, f, sz),
      m_thunk(t)
  { }

  typedef internal::AbstractFunctor0<RESULT_TYPE> FunctorBind0;
  Functor0(FunctorBind0* funcBind)
    : FunctorBase(NULL, NULL, 0),
      m_thunk(&Functor0::functorBindThunk),
      m_funcBindPtr(funcBind)
  { }

  template<typename CLASS, typename MEM_FUNC>
  static RESULT_TYPE classMemberFunctionThunk(const Functor0& ftor)
  {
    CLASS* callee = (CLASS*)ftor.m_callee;
    MEM_FUNC &memFunc(*(MEM_FUNC*)(void *)(ftor.m_memFunc));
    return (callee->*memFunc)();
  }

  template<typename FUNC>
  static RESULT_TYPE freeFunctionThunk(const Functor0& ftor)
  {
    return (FUNC(ftor.m_func))();
  }

  static RESULT_TYPE functorBindThunk(const Functor0& ftor)
  {
    return ftor.m_funcBindPtr->execute();
  }

  Thunk m_thunk;
  BasicSharedPointer<FunctorBind0> m_funcBindPtr;
};

//! Functor1
template <typename RESULT_TYPE, typename ARG_TYPE>
class Functor1 : protected FunctorBase
{
public:
  typedef RESULT_TYPE result_type;
  typedef ARG_TYPE argument_type;

  Functor1()
    : m_thunk(NULL)
  { }

  RESULT_TYPE execute(ARG_TYPE arg) const
  {
    return m_thunk(*this, arg);
  }

  RESULT_TYPE operator()(ARG_TYPE arg) const
  {
    return m_thunk(*this, arg);
  }

  using FunctorBase::isValid;

  // Free function
  template<typename TRT, typename TARG>
  static Functor1 make(TRT (*f)(TARG))
  {
    return Functor1(&Functor1::freeFunctionThunk<TRT (*)(TARG)>, NULL, (const void*)f, 0);
  }

  // Member function
  template<typename CLASS, typename TRT, typename TARG, class CALL_TYPE>
  static Functor1 make(CLASS* object, TRT (CALL_TYPE::* const &f)(TARG))
  {
    typedef TRT (CALL_TYPE::*MemFunc)(TARG);
    return Functor1(&Functor1::classMemberFunctionThunk<CLASS, MemFunc>, object, &f, sizeof(MemFunc));
  }

  // Const member function
  template<typename CLASS, typename TRT, typename TARG, class CALL_TYPE>
  static Functor1 make(const CLASS* object, TRT (CALL_TYPE::* const &f)(TARG) const)
  {
    typedef TRT (CALL_TYPE::*MemFunc)(TARG) const;
    return Functor1(&Functor1::classMemberFunctionThunk<CLASS, MemFunc>, object, &f, sizeof(MemFunc));
  }

private:
  typedef RESULT_TYPE (*Thunk)(const FunctorBase&, ARG_TYPE);
  Functor1(Thunk t, const void* c, const void* f, std::size_t sz)
    : FunctorBase(c, f, sz),
      m_thunk(t)
  { }

  template<typename CLASS, typename MEM_FUNC>
  static RESULT_TYPE classMemberFunctionThunk(const FunctorBase& ftor, ARG_TYPE arg)
  {
    CLASS* callee = (CLASS*)ftor.m_callee;
    MEM_FUNC &memFunc(*(MEM_FUNC*)(void *)(ftor.m_memFunc));
    return (callee->*memFunc)(arg);
  }

  template<typename FUNC>
  static RESULT_TYPE freeFunctionThunk(const FunctorBase& ftor, ARG_TYPE arg)
  {
    return (FUNC(ftor.m_func))(arg);
  }

  Thunk m_thunk;
};

//! Functor2
template <typename RESULT_TYPE, typename ARG1_TYPE, typename ARG2_TYPE>
class Functor2 : protected FunctorBase
{
public:
  typedef RESULT_TYPE result_type;
  typedef ARG1_TYPE first_argument_type;
  typedef ARG2_TYPE second_argument_type;

  Functor2()
    : m_thunk(NULL)
  { }

  RESULT_TYPE execute(ARG1_TYPE arg1, ARG2_TYPE arg2) const
  {
    return m_thunk(*this, arg1, arg2);
  }

  RESULT_TYPE operator()(ARG1_TYPE arg1, ARG2_TYPE arg2) const
  {
    return m_thunk(*this, arg1, arg2);
  }

  using FunctorBase::isValid;

  // Free function
  template<typename TRT, typename TARG1, typename TARG2>
  static Functor2 make(TRT (*f)(TARG1, TARG2))
  {
    return Functor2(&Functor2::freeFunctionThunk<TRT (*)(TARG1, TARG2)>, NULL, (const void*)f, 0);
  }

  // Member function
  template<typename CLASS, typename TRT, typename TARG1, typename TARG2, class CALL_TYPE>
  static Functor2 make(CLASS* object, TRT (CALL_TYPE::* const &f)(TARG1, TARG2))
  {
    typedef TRT (CALL_TYPE::*MemFunc)(TARG1, TARG2);
    return Functor2(&Functor2::classMemberFunctionThunk<CLASS, MemFunc>, object, &f, sizeof(MemFunc));
  }

  // Const member function
  template<typename CLASS, typename TRT, typename TARG1, typename TARG2, class CALL_TYPE>
  static Functor2 make(const CLASS* object, TRT (CALL_TYPE::* const &f)(TARG1, TARG2) const)
  {
    typedef TRT (CALL_TYPE::*MemFunc)(TARG1, TARG2) const;
    return Functor2(&Functor2::classMemberFunctionThunk<CLASS, MemFunc>, object, &f, sizeof(MemFunc));
  }

private:
  typedef RESULT_TYPE (*Thunk)(const FunctorBase&, ARG1_TYPE, ARG2_TYPE);
  Functor2(Thunk t, const void* c, const void* f, std::size_t sz)
    : FunctorBase(c, f, sz),
      m_thunk(t)
  { }

  template<typename CLASS, typename MEM_FUNC>
  static RESULT_TYPE classMemberFunctionThunk(const FunctorBase& ftor, ARG1_TYPE arg1, ARG2_TYPE arg2)
  {
    CLASS* callee = (CLASS*)ftor.m_callee;
    MEM_FUNC &memFunc(*(MEM_FUNC*)(void *)(ftor.m_memFunc));
    return (callee->*memFunc)(arg1, arg2);
  }

  template<typename FUNC>
  static RESULT_TYPE freeFunctionThunk(const FunctorBase& ftor, ARG1_TYPE arg1, ARG2_TYPE arg2)
  {
    return (FUNC(ftor.m_func))(arg1, arg2);
  }

  Thunk m_thunk;
};

} // namespace cpp

#endif // CPPTOOLS_FUNCTOR_H

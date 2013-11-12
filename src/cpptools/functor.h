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

namespace cpp {

/*!
 * \class FunctorBase
 * \brief Typeless representation of a function and optional object
 *
 * Based on "CALLBACKS IN C++ USING TEMPLATE FUNCTORS" by Rich Hickey
 * http://www.tutok.sk/fastgl/callback.html
 *
 * Don't use this class directly, use Functor0, Functor1 and Functor2 instead.
 *
 * \headerfile functor.h <cpptools/functor.h>
 * \ingroup cpptools
 */

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


/*!
 * \class Functor1
 * \brief Unary (single argument) functors that can be called as f(x)
 *
 * \headerfile functor.h <cpptools/functor.h>
 * \ingroup cpptools
 */

template <typename RESULT, typename ARG>
class Functor1 : protected FunctorBase
{
public:
  typedef RESULT result_type;
  typedef ARG argument_type;

  Functor1()
    : m_thunk(NULL)
  { }

  RESULT execute(ARG arg) const
  {
    return m_thunk(*this, arg);
  }

  RESULT operator()(ARG arg) const
  {
    return m_thunk(*this, arg);
  }

  using FunctorBase::isValid;

  // Free function
  template<typename TRT, typename TARG>
  Functor1(TRT (*f)(TARG))
    : FunctorBase(NULL, (const void*)f, 0),
      m_thunk(&Functor1::freeFunctionThunk<TRT (*)(TARG)>)
  { }

  // Member function
  template<typename CLASS, typename TRT, typename TARG, class CALL_TYPE>
  Functor1(CLASS* object, TRT (CALL_TYPE::* const &f)(TARG))
    : FunctorBase(object, &f, sizeof(TRT (CALL_TYPE::*)(TARG))),
      m_thunk(&Functor1::classMemberFunctionThunk<CLASS, TRT (CALL_TYPE::*)(TARG)>)
  { }

  // Const member function
  template<typename CLASS, typename TRT, typename TARG, class CALL_TYPE>
  Functor1(const CLASS* object, TRT (CALL_TYPE::* const &f)(TARG) const)
    : FunctorBase(object, &f, sizeof(TRT (CALL_TYPE::*)(TARG) const)),
      m_thunk(&Functor1::classMemberFunctionThunk<CLASS, TRT (CALL_TYPE::*)(TARG) const>)
  { }

private:
  template<typename CLASS, typename MEM_FUNC>
  static RESULT classMemberFunctionThunk(const FunctorBase& ftor, ARG arg)
  {
    CLASS* callee = (CLASS*)ftor.m_callee;
    MEM_FUNC &memFunc(*(MEM_FUNC*)(void *)(ftor.m_memFunc));
    return (callee->*memFunc)(arg);
  }

  template<typename FUNC>
  static RESULT freeFunctionThunk(const FunctorBase& ftor, ARG arg)
  {
    return (FUNC(ftor.m_func))(arg);
  }

  typedef RESULT (*Thunk)(const FunctorBase&, ARG);
  Thunk m_thunk;
};

/*!
 * \class Functor2
 * \brief Binary (two arguments) functors that can be called as f(x,y)
 *
 * \headerfile functor.h <cpptools/functor.h>
 * \ingroup cpptools
 */

template <typename RESULT, typename ARG1, typename ARG2>
class Functor2 : protected FunctorBase
{
public:
  typedef RESULT result_type;
  typedef ARG1 first_argument_type;
  typedef ARG2 second_argument_type;

  Functor2()
    : m_thunk(NULL)
  { }

  RESULT execute(ARG1 arg1, ARG2 arg2) const
  {
    return m_thunk(*this, arg1, arg2);
  }

  RESULT operator()(ARG1 arg1, ARG2 arg2) const
  {
    return m_thunk(*this, arg1, arg2);
  }

  using FunctorBase::isValid;

  // Free function
  template<typename TRT, typename TARG1, typename TARG2>
  Functor2(TRT (*f)(TARG1, TARG2))
    : FunctorBase(NULL, (const void*)f, 0),
      m_thunk(&Functor2::freeFunctionThunk<TRT (*)(TARG1, TARG2)>)
  { }

  // Member function
  template<typename CLASS, typename TRT, typename TARG1, typename TARG2, class CALL_TYPE>
  Functor2(CLASS* object, TRT (CALL_TYPE::* const &f)(TARG1, TARG2))
    : FunctorBase(object, &f, sizeof(TRT (CALL_TYPE::*)(TARG1, TARG2))),
      m_thunk(&Functor2::classMemberFunctionThunk<CLASS, TRT (CALL_TYPE::*)(TARG1, TARG2)>)
  { }

  // Const member function
  template<typename CLASS, typename TRT, typename TARG1, typename TARG2, class CALL_TYPE>
  Functor2(const CLASS* object, TRT (CALL_TYPE::* const &f)(TARG1, TARG2) const)
    : FunctorBase(object, &f, sizeof(TRT (CALL_TYPE::*)(TARG1, TARG2) const)),
      m_thunk(&Functor2::classMemberFunctionThunk<CLASS, TRT (CALL_TYPE::*)(TARG1, TARG2) const>)
  { }

private:

  template<typename CLASS, typename MEM_FUNC>
  static RESULT classMemberFunctionThunk(const FunctorBase& ftor, ARG1 arg1, ARG2 arg2)
  {
    CLASS* callee = (CLASS*)ftor.m_callee;
    MEM_FUNC &memFunc(*(MEM_FUNC*)(void *)(ftor.m_memFunc));
    return (callee->*memFunc)(arg1, arg2);
  }

  template<typename FUNC>
  static RESULT freeFunctionThunk(const FunctorBase& ftor, ARG1 arg1, ARG2 arg2)
  {
    return (FUNC(ftor.m_func))(arg1, arg2);
  }

  typedef RESULT (*Thunk)(const FunctorBase&, ARG1, ARG2);
  Thunk m_thunk;
};

//! @cond INCLUDE_INTERNAL
namespace internal {

template<typename RESULT>
class AbstractStoredFunctorCall
{
public:
  virtual ~AbstractStoredFunctorCall()
  { }

  virtual RESULT execute() const = 0;
};

template<typename RESULT, typename PARAM, typename ARG>
class StoredFunctor1Call : public AbstractStoredFunctorCall<RESULT>
{
public:
  StoredFunctor1Call(const Functor1<RESULT, PARAM>& func1, const ARG& arg)
    : m_func1(func1),
      m_arg(arg)
  { }

  RESULT execute() const
  { return m_func1(m_arg); }

private:
  Functor1<RESULT, PARAM> m_func1;
  ARG m_arg;
};

template<typename RESULT, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
class StoredFunctor2Call : public AbstractStoredFunctorCall<RESULT>
{
public:
  StoredFunctor2Call(const Functor2<RESULT, PARAM1, PARAM2>& func2, const ARG1& arg1, const ARG2& arg2)
    : m_func2(func2),
      m_arg1(arg1),
      m_arg2(arg2)
  { }

  RESULT execute() const
  { return m_func2(m_arg1, m_arg2); }

private:
  Functor2<RESULT, PARAM1, PARAM2> m_func2;
  ARG1 m_arg1;
  ARG2 m_arg2;
};

} // namespace internal
//! @endcond

/*!
 * \class Functor0
 * \brief Generator (no argument) functors that can be called as f()
 *
 * Functor0 also provides Functor1 and Functor2 arguments binding, e.g. a Functor1 can be
 * transformed to a Functor0, its argument is considered then as a constant.
 *
 * \headerfile functor.h <cpptools/functor.h>
 * \ingroup cpptools
 */

template <typename RESULT>
class Functor0 : protected FunctorBase
{
public:
  typedef RESULT result_type;

  Functor0()
    : m_thunk(NULL)
  { }

  RESULT execute() const
  {
    return m_thunk(*this);
  }

  RESULT operator()() const
  {
    return m_thunk(*this);
  }

  using FunctorBase::isValid;

  // Free function
  template<typename TRT>
  Functor0(TRT (*f)())
    : FunctorBase(NULL, (const void*)f, 0),
      m_thunk(&Functor0::freeFunctionThunk<TRT (*)()>)
  { }

  // Member function
  template<typename CLASS, typename TRT, class CALL_TYPE>
  Functor0(CLASS* object, TRT (CALL_TYPE::* const &f)())
    : FunctorBase(object, &f, sizeof(TRT (CALL_TYPE::*)())),
      m_thunk(Functor0::classMemberFunctionThunk<CLASS, TRT (CALL_TYPE::*)()>)
  { }

  // Const member function
  template<typename CLASS, typename TRT, class CALL_TYPE>
  Functor0(CLASS* object, TRT (CALL_TYPE::* const &f)() const)
    : FunctorBase(object, &f, sizeof(TRT (CALL_TYPE::*)() const)),
      m_thunk(Functor0::classMemberFunctionThunk<CLASS, TRT (CALL_TYPE::*)() const>)
  { }

  // Free function binders
  template<typename PARAM1, typename ARG1>
  Functor0(RESULT (*funcPtr)(PARAM1), const ARG1 &arg1)
    : m_thunk(&Functor0::functorBindThunk),
      m_funcBindPtr(new internal::StoredFunctor1Call<RESULT, PARAM1, ARG1>(
                      Functor1<RESULT, PARAM1>(funcPtr), arg1))
  { }

  template<typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
  Functor0(RESULT (*funcPtr)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
    : m_thunk(&Functor0::functorBindThunk),
      m_funcBindPtr(new internal::StoredFunctor2Call<RESULT, PARAM1, ARG1, PARAM2, ARG2>(
                      Functor2<RESULT, PARAM1, PARAM2>(funcPtr), arg1, arg2))
  { }

  // Member function binders
  template <typename CLASS, typename PARAM1, typename ARG1>
  Functor0(CLASS* object, RESULT (CLASS::*funcPtr)(PARAM1), const ARG1 &arg1)
    : m_thunk(&Functor0::functorBindThunk),
      m_funcBindPtr(new internal::StoredFunctor1Call<RESULT, PARAM1, ARG1>(
                      Functor1<RESULT, PARAM1>(object, funcPtr), arg1))
  { }

  template <typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
  Functor0(CLASS* object, RESULT (CLASS::*funcPtr)(PARAM1, PARAM2), const ARG1 &arg1, const ARG2 &arg2)
    : m_thunk(&Functor0::functorBindThunk),
      m_funcBindPtr(new internal::StoredFunctor2Call<RESULT, PARAM1, ARG1, PARAM2, ARG2>(
                      Functor2<RESULT, PARAM1, PARAM2>(object, funcPtr), arg1, arg2))
  { }

  // Const member function binders
  template <typename CLASS, typename PARAM1, typename ARG1>
  Functor0(const CLASS* object, RESULT (CLASS::*funcPtr)(PARAM1) const, const ARG1 &arg1)
    : m_thunk(&Functor0::functorBindThunk),
      m_funcBindPtr(new internal::StoredFunctor1Call<RESULT, PARAM1, ARG1>(
                      Functor1<RESULT, PARAM1>(object, funcPtr), arg1))
  { }

  template <typename CLASS, typename PARAM1, typename ARG1, typename PARAM2, typename ARG2>
  Functor0(const CLASS* object, RESULT (CLASS::*funcPtr)(PARAM1, PARAM2) const, const ARG1 &arg1, const ARG2 &arg2)
    : m_thunk(&Functor0::functorBindThunk),
      m_funcBindPtr(new internal::StoredFunctor2Call<RESULT, PARAM1, ARG1, PARAM2, ARG2>(
                      Functor2<RESULT, PARAM1, PARAM2>(object, funcPtr), arg1, arg2))
  { }

  // Implementation
private:
  template<typename CLASS, typename MEM_FUNC>
  static RESULT classMemberFunctionThunk(const Functor0& ftor)
  {
    CLASS* callee = (CLASS*)ftor.m_callee;
    MEM_FUNC &memFunc(*(MEM_FUNC*)(void *)(ftor.m_memFunc));
    return (callee->*memFunc)();
  }

  template<typename FUNC>
  static RESULT freeFunctionThunk(const Functor0& ftor)
  {
    return (FUNC(ftor.m_func))();
  }

  static RESULT functorBindThunk(const Functor0& ftor)
  {
    return ftor.m_funcBindPtr->execute();
  }

  typedef RESULT (*Thunk)(const Functor0&);
  typedef internal::AbstractStoredFunctorCall<RESULT> FunctorBind0;
  Thunk m_thunk;
  BasicSharedPointer<FunctorBind0> m_funcBindPtr;
};

} // namespace cpp

#endif // CPPTOOLS_FUNCTOR_H

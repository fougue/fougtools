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

#ifndef CPPTOOLS_FUNCTIONAL_H
#define CPPTOOLS_FUNCTIONAL_H

#include <functional>

namespace cpp {

template<typename FUNCTOR1>
struct Binder
{
  // -- STL compatibility
  typedef void argument_type;
  typedef typename FUNCTOR1::result_type result_type;

  typedef typename FUNCTOR1::argument_type functor_argument_type;

  Binder(FUNCTOR1 functor1, functor_argument_type arg);
  result_type operator()();

private:
  FUNCTOR1 m_functor1;
  functor_argument_type m_arg;
};

template<typename FUNCTOR1>
Binder<FUNCTOR1> bind(FUNCTOR1 functor1, typename FUNCTOR1::argument_type arg);



// --
// -- Implementation
// --

template<typename FUNCTOR1>
Binder<FUNCTOR1>::Binder(FUNCTOR1 functor1, functor_argument_type arg)
  : m_functor1(functor1), m_arg(arg)
{
}

template<typename FUNCTOR1>
typename FUNCTOR1::result_type Binder<FUNCTOR1>::operator()()
{
  return m_functor1(m_arg);
}

template<typename FUNCTOR1>
Binder<FUNCTOR1> bind(FUNCTOR1 functor1, typename FUNCTOR1::argument_type arg)
{
  return Binder<FUNCTOR1>(functor1, arg);
}

} // namespace cpp

#endif // CPPTOOLS_FUNCTIONAL_H

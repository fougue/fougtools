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

#ifndef CPPTOOLS_IDENTIFIER_H
#define CPPTOOLS_IDENTIFIER_H

namespace cpp {

template<typename _T_>
class Identifier
{
public:
  explicit Identifier();
  explicit Identifier(_T_ v);
  _T_ value() const;
  void setValue(_T_ v);
private:
  _T_ _value;
};

typedef Identifier<int> IntIdentifier;
typedef Identifier<long> LongIdentifier;
typedef Identifier<unsigned int> UIntIdentifier;
typedef Identifier<unsigned long> ULongIdentifier;

// --
// -- Implementation
// --

template<typename _T_>
Identifier<_T_>::Identifier() :
  _value(static_cast<_T_>(0))
{
}

template<typename _T_>
Identifier<_T_>::Identifier(_T_ v) :
  _value(v)
{
}

template<typename _T_>
_T_ Identifier<_T_>::value() const
{
  return this->_value;
}

template<typename _T_>
void Identifier<_T_>::setValue(_T_ v)
{
  this->_value = v;
}

} // namespace cpp

#endif // CPPTOOLS_IDENTIFIER_H

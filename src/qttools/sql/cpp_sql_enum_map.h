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

#ifndef QTTOOLS_CPP_SQL_ENUM_MAP_H
# define QTTOOLS_CPP_SQL_ENUM_MAP_H

# include <cassert>
# include <map>
# include <QtCore/QHash>
# include <QtCore/QPair>
# include <QtCore/QString>
# include <QtCore/QVector>

namespace qttools {

template<typename _CPP_ENUM_>
class SqlCppEnumMap
{
public:
  SqlCppEnumMap<_CPP_ENUM_>();
  SqlCppEnumMap<_CPP_ENUM_>(const std::map<_CPP_ENUM_, const char*>& enumMap);

  void addMapping(_CPP_ENUM_ cppVal, const QString& sqlVal);

  int size() const;
  int index(_CPP_ENUM_ cppVal) const;

  _CPP_ENUM_ cppValue(int i) const;
  _CPP_ENUM_ cppValue(const QString& sqlVal) const;
  QString sqlValue(_CPP_ENUM_ cppVal) const;

  SqlCppEnumMap<_CPP_ENUM_>& operator=(const std::map<_CPP_ENUM_, const char*>& enumMap);

private:
  QHash<_CPP_ENUM_, QString> _cppSqlMap;
  QHash<QString, _CPP_ENUM_> _sqlCppMap;
  QVector<_CPP_ENUM_> _intMap;
};

} // namespace qttools



// --
// -- Implementation
// --

# include <algorithm>
# include <cassert>

namespace qttools {

template<typename _CPP_ENUM_>
SqlCppEnumMap<_CPP_ENUM_>::SqlCppEnumMap()
{
}

template<typename _CPP_ENUM_>
SqlCppEnumMap<_CPP_ENUM_>::SqlCppEnumMap(const std::map<_CPP_ENUM_, const char*>& enumMap)
{
  typename std::map<_CPP_ENUM_, const char*>::const_iterator iEnum;
  for (iEnum = enumMap.begin(); iEnum != enumMap.end(); ++iEnum)
    this->addMapping(iEnum->first, iEnum->second);
}

template<typename _CPP_ENUM_>
void SqlCppEnumMap<_CPP_ENUM_>::addMapping(_CPP_ENUM_ cppVal, const QString& sqlVal)
{
  _cppSqlMap[cppVal] = sqlVal;
  _sqlCppMap[sqlVal] = cppVal;
  _intMap.append(cppVal);
}

template<typename _CPP_ENUM_>
int SqlCppEnumMap<_CPP_ENUM_>::size() const
{
  return _intMap.size();
}

template<typename _CPP_ENUM_>
int SqlCppEnumMap<_CPP_ENUM_>::index(_CPP_ENUM_ cppVal) const
{
  return std::find(_intMap.begin(), _intMap.end(), cppVal) - _intMap.begin();
}

template<typename _CPP_ENUM_>
_CPP_ENUM_ SqlCppEnumMap<_CPP_ENUM_>::cppValue(int i) const
{
  assert(i < _intMap.size());
  return _intMap[i];
}

template<typename _CPP_ENUM_>
_CPP_ENUM_ SqlCppEnumMap<_CPP_ENUM_>::cppValue(const QString& sqlVal) const
{
  assert(_sqlCppMap.contains(sqlVal));
  return _sqlCppMap.find(sqlVal).value();
}

template<typename _CPP_ENUM_>
QString SqlCppEnumMap<_CPP_ENUM_>::sqlValue(_CPP_ENUM_ cppVal) const
{
  assert(_cppSqlMap.contains(cppVal));
  return _cppSqlMap[cppVal];
}

template<typename _CPP_ENUM_>
SqlCppEnumMap<_CPP_ENUM_>& SqlCppEnumMap<_CPP_ENUM_>::operator=(
    const std::map<_CPP_ENUM_, const char*>& enumMap)
{
  _cppSqlMap.clear();
  _sqlCppMap.clear();
  _intMap.clear();
  _intMap.resize(0);
  typename std::map<_CPP_ENUM_, const char*>::const_iterator iEnum;
  for (iEnum = enumMap.begin(); iEnum != enumMap.end(); ++iEnum)
    this->addMapping(iEnum->first, iEnum->second);
}

} // namespace qttools

#endif // QTTOOLS_CPP_SQL_ENUM_MAP_H

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
#define QTTOOLS_CPP_SQL_ENUM_MAP_H

#include <map>
#include <QtCore/QHash>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QVector>

namespace qttools {

template<typename CPP_ENUM>
class SqlCppEnumMap
{
public:
  SqlCppEnumMap<CPP_ENUM>();
  SqlCppEnumMap<CPP_ENUM>(const std::map<CPP_ENUM, const char*>& enumMap);

  void addMapping(CPP_ENUM cppVal, const QString& sqlVal);

  int size() const;
  int index(CPP_ENUM cppVal) const;

  CPP_ENUM cppValue(int i) const;
  CPP_ENUM cppValue(const QString& sqlVal) const;
  QString sqlValue(CPP_ENUM cppVal) const;

  SqlCppEnumMap<CPP_ENUM>& operator=(const std::map<CPP_ENUM, const char*>& enumMap);

private:
  QHash<CPP_ENUM, QString> m_cppSqlMap;
  QHash<QString, CPP_ENUM> m_sqlCppMap;
  QVector<CPP_ENUM> m_intMap;
};

} // namespace qttools

// --
// -- Implementation
// --

#include <algorithm>

namespace qttools {

template<typename CPP_ENUM>
SqlCppEnumMap<CPP_ENUM>::SqlCppEnumMap()
{
}

template<typename CPP_ENUM>
SqlCppEnumMap<CPP_ENUM>::SqlCppEnumMap(const std::map<CPP_ENUM, const char*>& enumMap)
{
  typename std::map<CPP_ENUM, const char*>::const_iterator iEnum;
  for (iEnum = enumMap.begin(); iEnum != enumMap.end(); ++iEnum)
    this->addMapping(iEnum->first, iEnum->second);
}

template<typename CPP_ENUM>
void SqlCppEnumMap<CPP_ENUM>::addMapping(CPP_ENUM cppVal, const QString& sqlVal)
{
  m_cppSqlMap.insert(cppVal, sqlVal);
  m_sqlCppMap.insert(sqlVal, cppVal);
  m_intMap.append(cppVal);
}

template<typename CPP_ENUM>
int SqlCppEnumMap<CPP_ENUM>::size() const
{
  return m_intMap.size();
}

template<typename CPP_ENUM>
int SqlCppEnumMap<CPP_ENUM>::index(CPP_ENUM cppVal) const
{
  return std::find(m_intMap.begin(), m_intMap.end(), cppVal) - m_intMap.begin();
}

template<typename CPP_ENUM>
CPP_ENUM SqlCppEnumMap<CPP_ENUM>::cppValue(int i) const
{
  Q_ASSERT(i < m_intMap.size());
  return m_intMap.at(i);
}

template<typename CPP_ENUM>
CPP_ENUM SqlCppEnumMap<CPP_ENUM>::cppValue(const QString& sqlVal) const
{
  Q_ASSERT(m_sqlCppMap.contains(sqlVal));
  return m_sqlCppMap.find(sqlVal).value();
}

template<typename CPP_ENUM>
QString SqlCppEnumMap<CPP_ENUM>::sqlValue(CPP_ENUM cppVal) const
{
  Q_ASSERT(m_cppSqlMap.contains(cppVal));
  return m_cppSqlMap.value(cppVal);
}

template<typename CPP_ENUM>
SqlCppEnumMap<CPP_ENUM>& SqlCppEnumMap<CPP_ENUM>::operator=(const std::map<CPP_ENUM, const char*>& enumMap)
{
  m_cppSqlMap.clear();
  m_sqlCppMap.clear();
  m_intMap.clear();
  m_intMap.resize(0);
  typename std::map<CPP_ENUM, const char*>::const_iterator iEnum;
  for (iEnum = enumMap.begin(); iEnum != enumMap.end(); ++iEnum)
    this->addMapping(iEnum->first, iEnum->second);
}

} // namespace qttools

#endif // QTTOOLS_CPP_SQL_ENUM_MAP_H

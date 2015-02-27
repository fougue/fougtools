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

#pragma once

#include "../../cpptools/hash_fnv.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <unordered_map>
#include <vector>

namespace qttools {

template<typename CPP_ENUM>
class SqlCppEnumMap
{
public:
    SqlCppEnumMap<CPP_ENUM>();

    void addMapping(CPP_ENUM cppVal, const char* sqlVal);

    std::size_t size() const;
    std::size_t index(CPP_ENUM cppVal) const;

    CPP_ENUM cppValueAt(std::size_t i) const;
    CPP_ENUM cppValue(const char* sqlVal) const;
    const char* sqlValue(CPP_ENUM cppVal) const;

private:
    struct StrEqual
    {
        bool operator()(const char* lhs, const char* rhs) const;
    };

    typedef cpp::hash_fnv_1a<> StrHash;

    struct CppSql
    {
        CPP_ENUM cpp;
        const char* sql;
    };
    typename std::vector<CppSql>::const_iterator findCppSql(CPP_ENUM cppVal) const
    {
        auto it = std::find_if(m_mapVec.begin(), m_mapVec.end(),
                               [=] (const CppSql& val) { return val.cpp == cppVal; } );
        assert(it != m_mapVec.end());
        return it;
    }

    std::unordered_map<const char*, CPP_ENUM, StrHash, StrEqual> m_sqlCppMap;
    std::vector<CppSql> m_mapVec;
};

} // namespace qttools

// --
// -- Implementation
// --

#include <algorithm>

namespace qttools {

/*! \class SqlCppEnumMap
 *  \brief Provides C++ mapping of a SQL enumerated type
 *
 * \headerfile cpp_sql_enum_map.h <qttools/sql/cpp_sql_enum_map.h>
 * \ingroup qttools_sql
 */

template<typename CPP_ENUM>
SqlCppEnumMap<CPP_ENUM>::SqlCppEnumMap()
{
}

template<typename CPP_ENUM>
void SqlCppEnumMap<CPP_ENUM>::addMapping(CPP_ENUM cppVal, const char *sqlVal)
{
    m_sqlCppMap.emplace(sqlVal, cppVal);
    CppSql val;
    val.cpp = cppVal;
    val.sql = sqlVal;
    m_mapVec.push_back(val);
}

template<typename CPP_ENUM>
std::size_t SqlCppEnumMap<CPP_ENUM>::size() const
{
    return m_mapVec.size();
}

template<typename CPP_ENUM>
std::size_t SqlCppEnumMap<CPP_ENUM>::index(CPP_ENUM cppVal) const
{
    return this->findCppSql(cppVal) - m_mapVec.begin();
}

template<typename CPP_ENUM>
CPP_ENUM SqlCppEnumMap<CPP_ENUM>::cppValueAt(std::size_t i) const
{
    assert(i < m_mapVec.size());
    return m_mapVec.at(i).cpp;
}

template<typename CPP_ENUM>
CPP_ENUM SqlCppEnumMap<CPP_ENUM>::cppValue(const char *sqlVal) const
{
    auto it = m_sqlCppMap.find(sqlVal);
    assert(it != m_sqlCppMap.cend());
    return (*it).second;
}

template<typename CPP_ENUM>
const char *SqlCppEnumMap<CPP_ENUM>::sqlValue(CPP_ENUM cppVal) const
{
    auto it = this->findCppSql(cppVal);
    return (*it).sql;
}

template<typename CPP_ENUM>
bool SqlCppEnumMap<CPP_ENUM>::StrEqual::operator()(const char *lhs, const char *rhs) const
{
    return std::strcmp(lhs, rhs) == 0;
}

} // namespace qttools

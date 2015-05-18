/****************************************************************************
**  FougTools
**  Copyright Fougue (1 Mar. 2011)
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
****************************************************************************/

#pragma once

#include "hash_fnv.h"

#include <unordered_map>
#include <vector>

namespace cpp {

/*! \brief Provides mapping between a C++ enum type values and C strings
 *
 *  \code
 *      enum class Status {
 *          Started,
 *          Running,
 *          Finished
 *      };
 *
 *      cpp::EnumStringMap<Status> statusStrMap;
 *      statusStrMap.map(Status::Started,  "status_started");
 *      statusStrMap.map(Status::Running,  "status_running");
 *      statusStrMap.map(Status::Finished, "status_finished");
 *      assert(statusStrMap.value("status_running") == Status::Running);
 *      assert(std::strcmp(statusStrMap.string(Status::Running), "status_running") == 0);
 *  \endcode
 *
 *  \headerfile enum_string_map.h <cpptools/enum_string_map.h>
 *  \ingroup cpptools
 */
template<typename ENUM>
class EnumStringMap
{
public:
    typedef std::pair<ENUM, const char*> Mapping;

    EnumStringMap();

    void map(ENUM eval, const char* str);

    std::size_t size() const;
    std::size_t index(ENUM eval) const;

    ENUM valueAt(std::size_t i) const;
    ENUM value(const char* str) const;
    const char* string(ENUM eval) const;

    Mapping mapping(std::size_t i) const;

private:
    struct StrEqual
    {
        bool operator()(const char* lhs, const char* rhs) const;
    };

    typedef cpp::hash_fnv_1a<> StrHash;

    typename std::vector<Mapping>::const_iterator findCppSql(ENUM eval) const;

    std::unordered_map<const char*, ENUM, StrHash, StrEqual> m_strEnumMap;
    std::vector<Mapping> m_mappingVec;
};

} // namespace cpp

// --
// -- Implementation
// --

#include <algorithm>
#include <cassert>
#include <cstring>

namespace cpp {

template<typename ENUM>
EnumStringMap<ENUM>::EnumStringMap()
{
}

template<typename ENUM>
void EnumStringMap<ENUM>::map(ENUM eval, const char* str)
{
    m_strEnumMap.emplace(str, eval);
    m_mappingVec.emplace_back(eval, str);
}

template<typename ENUM>
std::size_t EnumStringMap<ENUM>::size() const
{
    return m_mappingVec.size();
}

template<typename ENUM>
std::size_t EnumStringMap<ENUM>::index(ENUM eval) const
{
    return this->findCppSql(eval) - m_mappingVec.begin();
}

template<typename ENUM>
ENUM EnumStringMap<ENUM>::valueAt(std::size_t i) const
{
    assert(i < m_mappingVec.size());
    return m_mappingVec.at(i).first;
}

template<typename ENUM>
ENUM EnumStringMap<ENUM>::value(const char *str) const
{
    auto it = m_strEnumMap.find(str);
    assert(it != m_strEnumMap.cend());
    return (*it).second;
}

template<typename ENUM>
const char *EnumStringMap<ENUM>::string(ENUM eval) const
{
    auto it = this->findCppSql(eval);
    return (*it).second;
}

template<typename ENUM>
typename EnumStringMap<ENUM>::Mapping EnumStringMap<ENUM>::mapping(std::size_t i) const
{
    assert(i < m_mappingVec.size());
    return m_mappingVec.at(i);
}

template<typename ENUM>
typename std::vector<typename EnumStringMap<ENUM>::Mapping>::const_iterator
EnumStringMap<ENUM>::findCppSql(ENUM eval) const
{
    auto it = std::find_if(m_mappingVec.cbegin(), m_mappingVec.cend(),
                           [=] (const Mapping& map) { return map.first == eval; } );
    assert(it != m_mappingVec.cend());
    return it;
}

template<typename ENUM>
bool EnumStringMap<ENUM>::StrEqual::operator()(const char *lhs, const char *rhs) const
{
    return std::strcmp(lhs, rhs) == 0;
}

} // namespace cpp

/****************************************************************************
**
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
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

class QObject;

#include "core.h"
#include <vector>

namespace qtcore {

class QTTOOLS_CORE_EXPORT QObjectUtils
{
public:
    static void forwardSignal(
            const QObject* sender, const QObject* resender, const char* signal);

    template<typename PARENT_TYPE>
    static const PARENT_TYPE* constFindParent(const QObject* object);

    template<typename PARENT_TYPE>
    static PARENT_TYPE* findParent(QObject* object);

    template<typename QOBJECT, typename ENUM>
    static ENUM toQEnumValue(const char* enumName, int value);

    template<typename QOBJECT, typename ENUM>
    static std::vector<ENUM> allQEnumValues(const char* enumName);
};

} // namespace qtcore

// --
// -- Implementation
// --

#include <QtCore/QObject>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaEnum>
#include <cassert>

namespace qtcore {

template<typename PARENT_TYPE>
const PARENT_TYPE* QObjectUtils::constFindParent(const QObject* object)
{
    return findParent<PARENT_TYPE>(const_cast<QObject*>(object));
}

template<typename PARENT_TYPE>
PARENT_TYPE* QObjectUtils::findParent(QObject* object)
{
    QObject* it = object;
    while (it != NULL && qobject_cast<PARENT_TYPE*>(it) == NULL)
        it = it->parent();
    return qobject_cast<PARENT_TYPE*>(it);
}

//! Safe cast of an integer to a Q_ENUM value
template<typename QOBJECT, typename ENUM>
ENUM QObjectUtils::toQEnumValue(const char* enumName, int value)
{
    const QMetaObject& metaObj = QOBJECT::staticMetaObject;
    const int enumIndex = metaObj.indexOfEnumerator(enumName);
    if (enumIndex != -1) {
        const QMetaEnum metaEnum = metaObj.enumerator(enumIndex);
        if (metaEnum.valueToKey(value) != nullptr)
            return static_cast<ENUM>(value);
    }
    assert(false);
    return static_cast<ENUM>(value);
}

/*! \brief All enumerator values of QOBJECT::ENUM returned in a single array
 *
 *  \tparam QOBJECT A QObject type, or a class marked at least with Q_GADGET (eg. QLocale)
 *  \tparam ENUM An enum type, declared in QOBJECT and marked with Q_ENUM (eg. QLocale::Country)
 *  \param enumName Name of the enumerator type (eg. "Country" for QLocale::Country)
 */
template<typename QOBJECT, typename ENUM>
std::vector<ENUM> QObjectUtils::allQEnumValues(const char* enumName)
{
    std::vector<ENUM> enumValueVec;
    const int enumIndex = QOBJECT::staticMetaObject.indexOfEnumerator(enumName);
    if (enumIndex != -1) {
        const QMetaEnum metaEnum = QOBJECT::staticMetaObject.enumerator(enumIndex);
        enumValueVec.reserve(metaEnum.keyCount());
        for (int i = 0; i < metaEnum.keyCount(); ++i) {
            const int enumValueAsInt = metaEnum.value(i);
            if (enumValueAsInt != -1)
                enumValueVec.push_back(static_cast<ENUM>(enumValueAsInt));
        }
    }
    return enumValueVec;
}

} // namespace qtcore

/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
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

#include "core.h"
#include <QtCore/QString>

namespace qtcore {

/*! \class QStringUtils
 *  \brief Provides a collection of tools around QString
 *  \headerfile qstring_utils.h <qttools/core/qstring_utils.h>
 *  \ingroup qttools_core
 */
class QTTOOLS_CORE_EXPORT QStringUtils
{
public:
    /*! Shorter equivalent to QString::compare(s1, s2, Qt::CaseInsensitive) */
    inline static bool iequals(const QString& s1, const QString& s2);

    //! \overload
    inline static bool iequals(const QString& s1, QLatin1String s2);
    //! \overload
    inline static bool iequals(QLatin1String s1, const QString& s2);
    //! \overload
    inline static bool iequals(const QString& s1, const QStringRef& s2);
    //! \overload
    inline static bool iequals(const QStringRef& s1, const QString& s2);
};

/*! Functor wrapper around QString::localeAwareCompare(lhs, rhs) == 0
 *  \headerfile qstring_utils.h <qttools/core/qstring_utils.h>
 *  \ingroup qttools_core
 */
struct QTTOOLS_CORE_EXPORT QStringLocaleAwareEqual
{
    inline bool operator()(const QString& lhs, const QString& rhs) const
    { return QString::localeAwareCompare(lhs, rhs) == 0; }
};

/*! Functor wrapper around QString::localeAwareCompare(lhs, rhs) != 0
 *  \headerfile qstring_utils.h <qttools/core/qstring_utils.h>
 *  \ingroup qttools_core
 */
struct QTTOOLS_CORE_EXPORT QStringLocaleAwareNotEqual
{
    inline bool operator()(const QString& lhs, const QString& rhs) const
    { return QString::localeAwareCompare(lhs, rhs) != 0; }
};

/*! Functor wrapper around QString::localeAwareCompare(lhs, rhs) < 0
 *  \headerfile qstring_utils.h <qttools/core/qstring_utils.h>
 *  \ingroup qttools_core
 */
struct QTTOOLS_CORE_EXPORT QStringLocaleAwareLess
{
    inline bool operator()(const QString& lhs, const QString& rhs) const
    { return QString::localeAwareCompare(lhs, rhs) < 0; }
};

/*! Functor wrapper around QString::localeAwareCompare(lhs, rhs) <= 0
 *  \headerfile qstring_utils.h <qttools/core/qstring_utils.h>
 *  \ingroup qttools_core
 */
struct QTTOOLS_CORE_EXPORT QStringLocaleAwareLessEqual
{
    inline bool operator()(const QString& lhs, const QString& rhs) const
    { return QString::localeAwareCompare(lhs, rhs) <= 0; }
};

/*! Functor wrapper around QString::localeAwareCompare(lhs, rhs) > 0
 *  \headerfile qstring_utils.h <qttools/core/qstring_utils.h>
 *  \ingroup qttools_core
 */
struct QTTOOLS_CORE_EXPORT QStringLocaleAwareGreater
{
    inline bool operator()(const QString& lhs, const QString& rhs) const
    { return QString::localeAwareCompare(lhs, rhs) > 0; }
};

/*! Functor wrapper around QString::localeAwareCompare(lhs, rhs) >= 0
 *  \headerfile qstring_utils.h <qttools/core/qstring_utils.h>
 *  \ingroup qttools_core
 */
struct QTTOOLS_CORE_EXPORT QStringLocaleAwareGreaterEqual
{
    inline bool operator()(const QString& lhs, const QString& rhs) const
    { return QString::localeAwareCompare(lhs, rhs) >= 0; }
};


// --
// -- Implementation
// --

bool QStringUtils::iequals(const QString &s1, const QString &s2)
{
    return QString::compare(s1, s2, Qt::CaseInsensitive) == 0;
}

bool QStringUtils::iequals(const QString &s1, QLatin1String s2)
{
    return QString::compare(s1, s2, Qt::CaseInsensitive) == 0;
}

bool QStringUtils::iequals(QLatin1String s1, const QString &s2)
{
    return QString::compare(s1, s2, Qt::CaseInsensitive) == 0;
}

bool QStringUtils::iequals(const QString& s1, const QStringRef& s2)
{
    return QString::compare(s1, s2, Qt::CaseInsensitive) == 0;
}

bool QStringUtils::iequals(const QStringRef& s1, const QString& s2)
{
    // There is no QString::compare(QStringRef, QString) overload
    return QString::compare(s2, s1, Qt::CaseInsensitive) == 0;
}

} // namespace qtcore

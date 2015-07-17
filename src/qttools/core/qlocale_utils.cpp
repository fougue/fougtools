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

#include "qlocale_utils.h"

#include "qobject_utils.h"

#include <QtCore/QMetaObject>
#include <QtCore/QMetaEnum>

namespace qtcore {

/*! \class QLocaleUtils
 *  \brief Provides a collection of tools around QLocale
 *  \headerfile qlocale_utils.h <qttools/core/qlocale_utils.h>
 *  \ingroup qttools_core
 *
 */

//! Safe cast of an integer to QLocale::MeasurementSystem
QLocale::MeasurementSystem QLocaleUtils::toMeasurementSystem(int measSys)
{
    return QObjectUtils::toQEnumValue<QLocale, QLocale::MeasurementSystem>(
                "MeasurementSystem", measSys);
}

//! Safe cast of an integer to QLocale::Country
QLocale::Country QLocaleUtils::toCountry(int code)
{
    return QObjectUtils::toQEnumValue<QLocale, QLocale::Country>("Country", code);
}

//! All enumerator values of QLocale::Country returned in a single array
std::vector<QLocale::Country> QLocaleUtils::allCountries()
{
    return QObjectUtils::allQEnumValues<QLocale, QLocale::Country>("Country");
}

} // namespace qtcore

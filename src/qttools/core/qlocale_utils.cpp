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

#include "qlocale_utils.h"

#include <QtCore/QMetaObject>
#include <QtCore/QMetaEnum>

namespace qttools {

/*! \class QLocaleUtils
 *  \brief Provides a collection of tools around QLocale
 *  \headerfile qlocale_utils.h <qttools/core/qlocale_utils.h>
 *  \ingroup qttools_core
 *
 */

//! Safe cast of an integer to QLocale::MeasurementSystem
QLocale::MeasurementSystem QLocaleUtils::toMeasurementSystem(int measSys)
{
    switch (measSys) {
    case QLocale::MetricSystem : return QLocale::MetricSystem;
#if QT_VERSION > 0x050000
    case QLocale::ImperialUKSystem : return QLocale::ImperialUKSystem;
#endif // QT_VERSION
    case QLocale::ImperialSystem : return QLocale::ImperialSystem;
    default : return QLocale::MetricSystem;
    }
}

//! Safe cast of an integer to QLocale::Country
QLocale::Country QLocaleUtils::toCountry(int code)
{
    const QMetaObject& localeMetaObj = QLocale::staticMetaObject;
    const int countryEnumIndex = localeMetaObj.indexOfEnumerator("Country");
    if (countryEnumIndex != -1) {
        const QMetaEnum countryEnum = localeMetaObj.enumerator(countryEnumIndex);
        if (countryEnum.valueToKey(code) != nullptr)
            return static_cast<QLocale::Country>(code);
    }
    return QLocale::AnyCountry;
}

//! All enumerator values of QLocale::Country returned in a single array
QVector<QLocale::Country> QLocaleUtils::allCountries()
{
    QVector<QLocale::Country> countryVec;
    const int countryEnumIndex = QLocale::staticMetaObject.indexOfEnumerator("Country");
    if (countryEnumIndex != -1) {
        const QMetaEnum countryEnum = QLocale::staticMetaObject.enumerator(countryEnumIndex);
        for (int i = 0; i < countryEnum.keyCount(); ++i) {
            const int countryEnumValue = countryEnum.value(i);
            if (countryEnumValue != -1) {
                const QLocale::Country country = static_cast<QLocale::Country>(countryEnumValue);
                if (!countryVec.contains(country))
                    countryVec.append(country);
            }
        }
    }
    return countryVec;
}

} // namespace qttools

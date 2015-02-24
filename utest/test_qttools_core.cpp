#include "test_qttools_core.h"

#include "../src/qttools/core/qlocale_utils.h"

#include <QtCore/QtDebug>
#include <QtCore/QTime>

void TestQtToolsCore::QLocaleUtils_test()
{
    QCOMPARE(static_cast<int>(QLocale::France), 74);
    QCOMPARE(qttools::QLocaleUtils::toCountry(74), QLocale::France);
    //  foreach (auto country, qttools::QLocaleTools::allCountries()) {
    //    qDebug() << QLocale::countryToString(country);
    //  }
}

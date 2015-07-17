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
#include <QtCore/QLocale>
#include <vector>

namespace qtcore {

class QTTOOLS_CORE_EXPORT QLocaleUtils
{
public:
    static QLocale::MeasurementSystem toMeasurementSystem(int measSys);

    static QLocale::Country toCountry(int code);
    static std::vector<QLocale::Country> allCountries();
};

} // namespace qtcore

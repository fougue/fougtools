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

#include "sql.h"
#include <QtCore/QList>
#include <QtCore/QVariant>

namespace qtsql {

class QTTOOLS_SQL_EXPORT CompositeTypeHelper
{
private:
    CompositeTypeHelper();

public:
    static QString toRow(const QList<QVariant>& values);
    static QStringList toValues(const QString& row);
};

} // namespace qtsql

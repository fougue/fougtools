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

#include "composite_type_helper.h"
#include <QtCore/QRegExp>
#include <QtCore/QStringList>
#include <QtCore/QtDebug>

namespace qtsql {

/*!
 * \class CompositeTypeHelper
 * \brief Provides helper services for the management of SQL composite types
 *
 * \headerfile composite_type_helper.h <qttools/sql/composite_type_helper.h>
 * \ingroup qttools_sql
 */

QString CompositeTypeHelper::toRow(const QList<QVariant>& values)
{
    QStringList valuesStr;
    foreach (const QVariant& value, values) {
        switch (value.type()) {
        case QVariant::Char:
        case QVariant::String:
            valuesStr += QString("\"%1\"").arg(value.toString());
            break;
        case QVariant::ULongLong:
        case QVariant::UInt:
        case QVariant::Int:
        case QVariant::LongLong:
        case QVariant::Double:
            valuesStr += QString("%1").arg(value.toString());
            break;
        case QVariant::Bool: {
            valuesStr += (value.toBool() ? QLatin1String("TRUE") : QLatin1String("FALSE"));
            break;
        }
        default: {
#ifndef QT_NO_DEBUG_OUTPUT
            qWarning() << "CompositeTypeHelper::toRow() : type not supported"
                       << " (value :" << value << ")";
#endif // !QT_NO_DEBUG_OUTPUT
            break;
        }
        } // end switch()
    } // end foreach()
    return QString("(%1)").arg(valuesStr.join(QLatin1String(",")));
}

QStringList CompositeTypeHelper::toValues(const QString& row)
{
    QString sqlRow = row;
    sqlRow.replace(QRegExp(QLatin1String("^\\(")), QString());
    sqlRow.replace(QRegExp(QLatin1String("\\)$")), QString());
    return sqlRow.split(QLatin1Char(','));
}

} // namespace qtsql

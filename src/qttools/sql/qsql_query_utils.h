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
#include <stdexcept>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

namespace qtsql {

class QTTOOLS_SQL_EXPORT SqlQueryError : public std::runtime_error
{
public:
    SqlQueryError(const QSqlQuery& qry);
    SqlQueryError(const QSqlError& err);
    ~SqlQueryError() throw();

    QSqlError sqlError() const;

private:
    QSqlError m_sqlError;
};

QTTOOLS_SQL_EXPORT
QSqlQuery execSqlCode(const QString& sqlCode, const QSqlDatabase& db);
QTTOOLS_SQL_EXPORT
QSqlQuery execSqlCodeInTransaction(const QString& sqlCode, QSqlDatabase db);

QTTOOLS_SQL_EXPORT
void throwIfError(const QSqlQuery& qry);

} // namespace qtsql

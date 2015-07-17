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

#include "qsql_query_utils.h"

#include <QtCore/QVariant>

namespace qtsql {

/*!
 * \class SqlQueryError
 * \brief Provides a std::runtime_error that can convey a QSqlError object
 *
 * \headerfile qsql_query_utils.h <qttools/sql/qsql_query_utils.h>
 * \ingroup qttools_sql
 */

SqlQueryError::SqlQueryError(const QSqlQuery& qry)
    : std::runtime_error(qry.lastError().text().toStdString()),
      m_sqlError(qry.lastError())
{
}

SqlQueryError::SqlQueryError(const QSqlError& err)
    : std::runtime_error(err.text().toStdString()),
      m_sqlError(err)
{
}

SqlQueryError::~SqlQueryError() throw()
{
}

QSqlError SqlQueryError::sqlError() const
{
    return m_sqlError;
}

/*! \brief Execute SQL statements in \p code use databse connection \p db
 *  \note Does nothing if \p sqlCode is empty
 *  \throws SqlQueryError if no connection to database or if SQL exec fails (SQL query has error)
 */
QSqlQuery execSqlCode(const QString& sqlCode, const QSqlDatabase& db)
{
    if (sqlCode.trimmed().isEmpty())
        return QSqlQuery(QString(), db);

    if (!db.isValid() || !db.isOpen()) {
        throw SqlQueryError(QSqlError(QLatin1String("db is not valid or not open"),
                                      QLatin1String(""),
                                      QSqlError::ConnectionError));
    }

    QSqlQuery qry = db.exec(sqlCode);
    qtsql::throwIfError(qry);
    return qry;
}

/*! \brief Same as qtsql::execSqlCode() but execution performs inside a transaction
 *  \note Any SqlQueryError exceptions thrown by qtsql::execSqlCode() is catched (transaction
 *        is rolled back then)
 */
QSqlQuery execSqlCodeInTransaction(const QString& sqlCode, QSqlDatabase db)
{
    db.transaction();

    QSqlQuery sqlQry;
    try {
        sqlQry = qtsql::execSqlCode(sqlCode, db);
        db.commit();
    }
    catch (const SqlQueryError& err) {
        Q_UNUSED(err);
        db.rollback();
        throw;
    }
    return sqlQry;
}

//! Throw SqlQueryError if SQL query \p qry has error
void throwIfError(const QSqlQuery& qry)
{
    if (qry.lastError().type() != QSqlError::NoError)
        throw SqlQueryError(qry);
}

} // namespace qtsql

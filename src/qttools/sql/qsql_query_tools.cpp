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

#include "qsql_query_tools.h"

#include <QtCore/QVariant>

namespace qttools {

/*!
 * \class SqlQueryError
 * \brief Provides a std::runtime_error that can convey a QSqlError object
 *
 * \headerfile qsql_query_tools.h <qttools/sql/qsql_query_tools.h>
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
  qttools::throwIfError(qry);
  return qry;
}

/*! \brief Same as qttools::execSqlCode() but execution performs inside a transaction
 *  \note Any SqlQueryError exceptions thrown by qttools::execSqlCode() is catched (transaction
 *        is rolled back then)
 */
QSqlQuery execSqlCodeInTransaction(const QString& sqlCode, QSqlDatabase db)
{
  db.transaction();

  QSqlQuery sqlQry;
  try {
    sqlQry = qttools::execSqlCode(sqlCode, db);
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

} // namespace qttools

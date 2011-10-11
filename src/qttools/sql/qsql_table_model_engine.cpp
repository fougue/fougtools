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

#include "qttools/sql/qsql_table_model_engine.h"

#include <QtSql/QSqlDriver>
#include <QtSql/QSqlField>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include "qttools/sql/database_manager.h"

namespace qttools {

/*! \class QSqlTableModelEnginePrivate
 *  \brief Internal (pimpl of QSqlTableModelEngine)
 *
 */
class QSqlTableModelEnginePrivate
{
public:
  QSqlTableModelEnginePrivate(QSqlTableModel* pModel,
                              DatabaseManager* databaseMgr) :
    dbMgr(databaseMgr),
    model(pModel),
    pkey(),
    sqlCode()
  {
  }

  QSqlIndex primaryKeyValue(const QSqlRecord& rec) const
  {
    QSqlIndex pkeyVal = this->pkey;
    for (int i = 0; i < pkeyVal.count(); ++i) {
      const QString fieldName = pkeyVal.fieldName(i);
      pkeyVal.setValue(fieldName, rec.value(fieldName));
    }
    return pkeyVal;
  }

  QSqlDatabase database() const
  {
    return this->dbMgr->database();
  }

  QString tableName() const
  {
    return this->model->tableName();
  }

  DatabaseManager* dbMgr;
  QSqlTableModel* model;
  QSqlIndex pkey;
  QString sqlCode;
};



/*! \class QSqlTableModelEngine
 *  \brief Provides an alternative engine for SQL code generation, working as
 *         a team mate with a QSqlTableModel
 *
 *  QSqlTableModelEngine is a workaround for QSqlTableModel lacks concerning
 *  SQL code generation (bug with \c NULL values, error-prone SQL statements
 *  caching, ...)
 */

QSqlTableModelEngine::QSqlTableModelEngine(QSqlTableModel* model,
                                           DatabaseManager* dbMgr) :
  d_ptr(new QSqlTableModelEnginePrivate(model, dbMgr))
{
}

QSqlTableModelEngine::~QSqlTableModelEngine()
{
  Q_D(QSqlTableModelEngine);
  delete d;
}

QSqlTableModel* QSqlTableModelEngine::model() const
{
  Q_D(const QSqlTableModelEngine);
  return d->model;
}

void QSqlTableModelEngine::clear()
{
  Q_D(QSqlTableModelEngine);
  d->sqlCode.clear();
}

QSqlError QSqlTableModelEngine::lastError() const
{
  Q_D(const QSqlTableModelEngine);
  return d->database().lastError();
}

bool QSqlTableModelEngine::exec()
{
  Q_D(const QSqlTableModelEngine);
  const QSqlQuery resQry = d->dbMgr->execSqlCode(d->sqlCode);
  this->clear();
  return resQry.lastError().type() == QSqlError::NoError;
}

QString QSqlTableModelEngine::sqlCode() const
{
  Q_D(const QSqlTableModelEngine);
  return d->sqlCode;
}

void QSqlTableModelEngine::setPrimaryKeyColumn(int col)
{
  Q_D(QSqlTableModelEngine);
  const QSqlDriver* driver = d->database().driver();
  if (driver != 0) {
    const QSqlRecord rec = driver->record(d->tableName());
    QSqlIndex pkey;
    pkey.append(rec.field(col));
    d->pkey = pkey;
  }
}

void QSqlTableModelEngine::sqlInsert(int modelRow)
{
  Q_D(QSqlTableModelEngine);
  const QSqlDriver* driver = d->database().driver();
  if (driver == 0)
    return;
  const QSqlRecord rowRec = this->model()->record(modelRow);
  d->sqlCode += driver->sqlStatement(QSqlDriver::InsertStatement,
                                      d->tableName(), rowRec, false) + ";\n\n";
}

void QSqlTableModelEngine::sqlUpdate(int modelRow)
{
  Q_D(QSqlTableModelEngine);
  const QSqlDriver* driver = d->database().driver();
  if (driver == 0 || d->pkey.isEmpty())
    return;
  const QSqlRecord rowRec = d->model->record(modelRow);
  const QSqlIndex pKeyVal = d->primaryKeyValue(rowRec);
  d->sqlCode +=
      driver->sqlStatement(QSqlDriver::UpdateStatement,
                           d->tableName(), rowRec, false) + "\n    " +
      driver->sqlStatement(QSqlDriver::WhereStatement,
                           d->tableName(), pKeyVal, false) + ";\n\n";
}

void QSqlTableModelEngine::sqlUpdateField(int modelRow, int modelColumn,
                                          const QVariant& v)
{
  QHash<int, QVariant> fieldValues;
  fieldValues[modelColumn] = v;
  this->sqlUpdateFields(modelRow, fieldValues);
}

void QSqlTableModelEngine::sqlUpdateFields(
    int modelRow, const QHash<int, QVariant>& fieldValues)
{
  Q_D(QSqlTableModelEngine);
  const QSqlDriver* driver = d->database().driver();
  if (driver == 0 || d->pkey.isEmpty())
    return;
  const QSqlRecord modelRec = this->model()->record(modelRow);
  QSqlRecord rec;
  QHashIterator<int, QVariant> fieldIt(fieldValues);
  while (fieldIt.hasNext()) {
    fieldIt.next();
    this->model()->setData(this->model()->index(modelRow, fieldIt.key()),
                           fieldIt.value());
    rec.append(modelRec.field(fieldIt.key()));
    rec.setValue(rec.count() - 1, fieldIt.value());
  }
  const QSqlIndex pKeyVal = d->primaryKeyValue(modelRec);
  d->sqlCode +=
      driver->sqlStatement(QSqlDriver::UpdateStatement,
                           d->tableName(), rec, false) + "\n    " +
      driver->sqlStatement(QSqlDriver::WhereStatement,
                           d->tableName(), pKeyVal, false) + ";\n\n";
}

void QSqlTableModelEngine::sqlDelete(int modelRow)
{
  Q_D(QSqlTableModelEngine);
  const QSqlDriver* driver = d->database().driver();
  if (driver == 0 || d->pkey.isEmpty())
    return;
  const QSqlRecord rowRec = this->model()->record(modelRow);
  const QSqlIndex pKeyVal = d->primaryKeyValue(rowRec);
  d->sqlCode +=
      driver->sqlStatement(QSqlDriver::DeleteStatement,
                           d->tableName(), pKeyVal, false) + "\n    " +
      driver->sqlStatement(QSqlDriver::WhereStatement,
                           d->tableName(), pKeyVal, false) + ";\n\n";
}

/*! \brief Add a user-defined SQL statement to the list of SQL commands that
 *         will be executed on call to exec()
 *
 */
void QSqlTableModelEngine::sqlStatement(const QString& sqlStmt)
{
  Q_D(QSqlTableModelEngine);
  d->sqlCode += sqlStmt + ";\n\n";
}

} // namespace qttools

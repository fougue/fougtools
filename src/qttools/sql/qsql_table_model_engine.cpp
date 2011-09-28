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
  _d(new QSqlTableModelEnginePrivate(model, dbMgr))
{
}

QSqlTableModelEngine::~QSqlTableModelEngine()
{
  delete _d;
}

QSqlTableModel* QSqlTableModelEngine::model() const
{
  return _d->model;
}

void QSqlTableModelEngine::clear()
{
  _d->sqlCode.clear();
}

QSqlError QSqlTableModelEngine::lastError() const
{
  return _d->database().lastError();
}

bool QSqlTableModelEngine::exec()
{
  const QSqlQuery resQry = _d->dbMgr->execSqlCode(_d->sqlCode);
  this->clear();
  return resQry.lastError().type() == QSqlError::NoError;
}

void QSqlTableModelEngine::setPrimaryKeyColumn(int col)
{
  const QSqlDriver* driver = _d->database().driver();
  if (driver != 0) {
    const QSqlRecord rec = driver->record(_d->tableName());
    QSqlIndex pkey;
    pkey.append(rec.field(col));
    _d->pkey = pkey;
  }
}

void QSqlTableModelEngine::sqlInsert(int modelRow)
{
  const QSqlDriver* driver = _d->database().driver();
  if (driver == 0)
    return;
  const QSqlRecord rowRec = this->model()->record(modelRow);
  _d->sqlCode += driver->sqlStatement(QSqlDriver::InsertStatement,
                                      _d->tableName(), rowRec, false) + ";\n\n";
}

void QSqlTableModelEngine::sqlUpdate(int modelRow)
{
  const QSqlDriver* driver = _d->database().driver();
  if (driver == 0 || _d->pkey.isEmpty())
    return;
  const QSqlRecord rowRec = _d->model->record(modelRow);
  const QSqlIndex pKeyVal = _d->primaryKeyValue(rowRec);
  _d->sqlCode +=
      driver->sqlStatement(QSqlDriver::UpdateStatement,
                           _d->tableName(), rowRec, false) + "\n    " +
      driver->sqlStatement(QSqlDriver::WhereStatement,
                           _d->tableName(), pKeyVal, false) + ";\n\n";
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
  const QSqlDriver* driver = _d->database().driver();
  if (driver == 0 || _d->pkey.isEmpty())
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
  const QSqlIndex pKeyVal = _d->primaryKeyValue(modelRec);
  _d->sqlCode +=
      driver->sqlStatement(QSqlDriver::UpdateStatement,
                           _d->tableName(), rec, false) + "\n    " +
      driver->sqlStatement(QSqlDriver::WhereStatement,
                           _d->tableName(), pKeyVal, false) + ";\n\n";
}

void QSqlTableModelEngine::sqlDelete(int modelRow)
{
  const QSqlDriver* driver = _d->database().driver();
  if (driver == 0 || _d->pkey.isEmpty())
    return;
  const QSqlRecord rowRec = this->model()->record(modelRow);
  const QSqlIndex pKeyVal = _d->primaryKeyValue(rowRec);
  _d->sqlCode +=
      driver->sqlStatement(QSqlDriver::DeleteStatement,
                           _d->tableName(), pKeyVal, false) + "\n    " +
      driver->sqlStatement(QSqlDriver::WhereStatement,
                           _d->tableName(), pKeyVal, false) + ";\n\n";
}

/*! \brief Add a user-defined SQL statement to the list of SQL commands that
 *         will be executed on call to exec()
 *
 */
void QSqlTableModelEngine::sqlStatement(const QString& sqlStmt)
{
  _d->sqlCode += sqlStmt + ";\n\n";
}

} // namespace qttools

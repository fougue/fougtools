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

#include "qttools/sql/database_manager.h"

#include <cassert>
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QUuid>
#include "cpptools/memory_utils.h"
#include "qttools/sql/qsql_query_tools.h"

namespace qttools {

/*! \class DatabaseManagerPrivate
 *  \brief Internal (pimpl of DatabaseManager)
 */
class DatabaseManagerPrivate
{
public:
  DatabaseManagerPrivate(const QSqlDatabase& refDb)
    : m_refDatabase(refDb)
  {
    assert(QThread::currentThread() != 0);
    m_databases.insert(QThread::currentThread(), refDb);
  }

  QHash<const QThread*, QSqlDatabase> m_databases;
  QSqlDatabase m_refDatabase;
  QMutex m_mutex;
};

/*! \class DatabaseManager
 *  \brief
 */

DatabaseManager::DatabaseManager(const QSqlDatabase& refDb)
  : d_ptr(new DatabaseManagerPrivate(refDb))
{
}

DatabaseManager::~DatabaseManager()
{
  Q_D(DatabaseManager);
  delete d;
}

const QSqlDatabase& DatabaseManager::referenceDatabase() const
{
  Q_D(const DatabaseManager);
  return d->m_refDatabase;
}

bool DatabaseManager::isDatabaseOpen(const QThread* inThread) const
{
  return this->hasDatabase(inThread) && this->database(inThread).isOpen();
}

bool DatabaseManager::hasDatabase(const QThread* inThread) const
{
  Q_D(const DatabaseManager);
  return d->m_databases.contains(inThread);
}

QSqlDatabase DatabaseManager::database(const QThread* inThread) const
{
  Q_D(const DatabaseManager);
  assert(this->hasDatabase(inThread));
  return d->m_databases.value(inThread);
}

QSqlDatabase DatabaseManager::createDatabase(const QThread* inThread)
{
  Q_D(DatabaseManager);
  if (this->hasDatabase(inThread))
    return this->database(inThread);

  QMutexLocker locker(&(d->m_mutex));
  Q_UNUSED(locker);

  QSqlDatabase newDb = QSqlDatabase::cloneDatabase(this->referenceDatabase(),
                                                   QString("thread 0x%1--%2")
                                                   .arg(cpp::scalarAddress(inThread), 0, 16)
                                                   .arg(QUuid::createUuid().toString()));
  if (newDb.isValid())
    newDb.open();
  d->m_databases.insert(inThread, newDb);
  return newDb;
}

QSqlQuery DatabaseManager::execSqlCode(const QString& sqlCode, const QThread* inThread) const
{
  return qttools::execSqlCode(sqlCode, this->database(inThread));
}

QSqlQuery DatabaseManager::execSqlCodeInTransaction(const QString& sqlCode,
                                                    const QThread* inThread) const
{
  return qttools::execSqlCodeInTransaction(sqlCode, this->database(inThread));
}

} // namespace qttools

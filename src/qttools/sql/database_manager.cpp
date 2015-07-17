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

#include "database_manager.h"

#include "../../cpptools/memory_utils.h"

#include <cstdio>
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QTextStream>
#include <QtCore/QUuid>
#include "qsql_query_utils.h"

namespace qtsql {

/*! \class DatabaseManager::Private
 *  \brief Internal (pimpl of DatabaseManager)
 */
class DatabaseManager::Private
{
public:
    Private(const QSqlDatabase& refDb)
        : m_refDatabase(refDb),
          m_isSqlOutputEnabled(false)
    {
        Q_ASSERT(QThread::currentThread() != NULL);
        m_databases.insert(QThread::currentThread(), refDb);
    }

    QHash<const QThread*, QSqlDatabase> m_databases;
    QSqlDatabase m_refDatabase;
    QMutex m_mutex;
    bool m_isSqlOutputEnabled;
    QTextStream m_sqlOutStream;
};

/*!
 * \class DatabaseManager
 * \brief Provides threading and SQL logging control over QSqlDatabase
 *
 * \headerfile database_manager.h <qttools/sql/database_manager.h>
 * \ingroup qttools_sql
 */

/*! \brief Construct a DatabaseManager object with \p refDb as reference database
 *
 * The reference database is used in createDatabase() when cloning the database for the needs of
 * a new QThread
 */
DatabaseManager::DatabaseManager(const QSqlDatabase& refDb)
    : d(new Private(refDb))
{
}

DatabaseManager::~DatabaseManager()
{
    delete d;
}

//! The reference database used when cloning QSqlDatabase in createDatabase()
const QSqlDatabase& DatabaseManager::referenceDatabase() const
{
    return d->m_refDatabase;
}

bool DatabaseManager::isDatabaseOpen(const QThread* inThread) const
{
    return this->hasDatabase(inThread) && this->database(inThread).isOpen();
}

bool DatabaseManager::hasDatabase(const QThread* inThread) const
{
    return d->m_databases.contains(inThread);
}

QSqlDatabase DatabaseManager::database(const QThread* inThread) const
{
    Q_ASSERT(this->hasDatabase(inThread));
    return d->m_databases.value(inThread);
}

QSqlDatabase DatabaseManager::createDatabase(const QThread* inThread)
{
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
    this->logSql(sqlCode, inThread);
    return qtsql::execSqlCode(sqlCode, this->database(inThread));
}

QSqlQuery DatabaseManager::execSqlCodeInTransaction(const QString& sqlCode,
                                                    const QThread* inThread) const
{
    this->logSql(sqlCode, inThread);
    return qtsql::execSqlCodeInTransaction(sqlCode, this->database(inThread));
}

bool DatabaseManager::isSqlOutputEnabled() const
{
    return d->m_isSqlOutputEnabled;
}

void DatabaseManager::setSqlOutputEnabled(bool on)
{
    d->m_isSqlOutputEnabled = on;
}

QIODevice* DatabaseManager::sqlOutputDevice() const
{
    return d->m_sqlOutStream.device();
}

void DatabaseManager::setSqlOutputDevice(QIODevice* device)
{
    if (d->m_sqlOutStream.device() != device)
        d->m_sqlOutStream.setDevice(device);
}

void DatabaseManager::logSql(const QString &sqlCode, const QThread *inThread) const
{
    if (sqlCode.trimmed().isEmpty())
        return;

    if (d->m_isSqlOutputEnabled && d->m_sqlOutStream.device() != NULL) {
        const QString threadObjectName = inThread != NULL ? inThread->objectName() : QString();
        d->m_sqlOutStream << QString("[thread%1 0x%2] %3")
                             .arg(threadObjectName)
                             .arg(QString::number(reinterpret_cast<std::size_t>(inThread), 16))
                             .arg(sqlCode)
                          << endl;
    }
}

} // namespace qtsql

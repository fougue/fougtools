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
#include <QtCore/QThread>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
class QIODevice;

namespace qtsql {

class QTTOOLS_SQL_EXPORT DatabaseManager
{
public:
    DatabaseManager(const QSqlDatabase& refDb);
    virtual ~DatabaseManager();

    bool isDatabaseOpen(const QThread* inThread = QThread::currentThread()) const;
    bool hasDatabase(const QThread* inThread = QThread::currentThread()) const;

    const QSqlDatabase& referenceDatabase() const;
    QSqlDatabase database(const QThread* inThread = QThread::currentThread()) const;
    virtual QSqlDatabase createDatabase(const QThread* inThread = QThread::currentThread());

    virtual QSqlQuery execSqlCode(const QString& sqlCode,
                                  const QThread* inThread = QThread::currentThread()) const;
    virtual QSqlQuery execSqlCodeInTransaction(const QString& sqlCode,
                                               const QThread* inThread = QThread::currentThread()) const;

    // SQL output
    bool isSqlOutputEnabled() const;
    void setSqlOutputEnabled(bool on);

    QIODevice* sqlOutputDevice() const;
    void setSqlOutputDevice(QIODevice* device);

protected:
    virtual void logSql(const QString& sqlCode, const QThread* inThread) const;

private:
    class Private;
    Private* const d;
};

} // namespace qtsql

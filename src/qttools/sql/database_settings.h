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

class QSettings;
class QSqlDatabase;

#include "sql.h"
#include <QtCore/QByteArray>
#include <QtCore/QHash>
#include <QtCore/QVariant>
#include <functional>

namespace qtsql {

class QTTOOLS_SQL_EXPORT DatabaseSettings
{
public:
    typedef std::function<QByteArray (const QByteArray&)> CipherFunction;
    typedef QHash<QString, QVariant> ValuesHash;

    DatabaseSettings();

    const QString& host() const;
    void setHost(const QString& host);

    QString databaseName() const;
    void setDatabaseName(const QString& dbName);

    int port() const;
    void setPort(int port);

    const QString& userName() const;
    void setUserName(const QString& userName);

    const QString& password() const;
    void setPassword(const QString& password);

    void applyTo(QSqlDatabase* db) const;

    void load(const QSettings* settings,
              CipherFunction&& pwdCipherFunc,
              const ValuesHash& defValues = ValuesHash());
    void write(QSettings* settings,
               CipherFunction&& pwdCipherFunc) const;

private:
    QString m_host;
    QString m_dbName;
    int m_port;
    QString m_userName;
    QString m_password;
};

} // namespace qtsql

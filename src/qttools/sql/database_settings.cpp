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

#include "database_settings.h"

#include <QtCore/QSettings>
#include <QtSql/QSqlDatabase>

namespace qtsql {

/*!
 * \class DatabaseSettings
 * \brief Settings to connect to a database. Settings can be loaded and saved from/to a QSettings
 *
 * \headerfile database_settings.h <qttools/sql/database_settings.h>
 * \ingroup qttools_sql
 */

DatabaseSettings::DatabaseSettings()
    : m_port(0)
{
}

/*! \sa QSqlDatabase::setHostName()
 */
void DatabaseSettings::setHost(const QString& host)
{
    m_host = host;
}

/*! \sa QSqlDatabase::hostName()
 */
const QString& DatabaseSettings::host() const
{
    return m_host;
}

/*! \sa QSqlDatabase::setDatabaseName()
 */
void DatabaseSettings::setDatabaseName(const QString& dbName)
{
    m_dbName = dbName;
}

/*! \sa QSqlDatabase::databaseName()
 */
QString DatabaseSettings::databaseName() const
{
    return m_dbName;
}

/*! \sa QSqlDatabase::setPort()
 */
void DatabaseSettings::setPort(int port)
{
    m_port = port;
}

/*! \sa QSqlDatabase::port()
 */
int DatabaseSettings::port() const
{
    return m_port;
}

/*! \sa QSqlDatabase::setUserName()
 */
void DatabaseSettings::setUserName(const QString& userName)
{
    m_userName = userName;
}

/*! \sa QSqlDatabase::userName()
 */
const QString& DatabaseSettings::userName() const
{
    return m_userName;
}

/*! \sa QSqlDatabase::setPassword()
 */
void DatabaseSettings::setPassword(const QString& password)
{
    m_password = password;
}

/*! \sa QSqlDatabase::password()
 */
const QString& DatabaseSettings::password() const
{
    return m_password;
}

/*! \brief Load settings from the persistent storage
 *  \param pwdCipherFunc Function used to decrypt the password. If \c null then
 *         the default password is returned (see parameter \p defValues)
 *  \param defValues Default values when all or some persistent settings could not be retrieved
 */
void DatabaseSettings::load(const QSettings* settings,
                            CipherFunction&& pwdCipherFunc,
                            const ValuesHash& defValues)
{
    if (settings == NULL)
        return;

    const QString defHost = defValues.value("host").toString();
    const QString defDbName = defValues.value("name").toString();
    const int defPort = defValues.value("port").toInt();
    const QString defUser = defValues.value("user").toString();
    const QString defPwd = defValues.value("password").toString();

    this->setHost(settings->value("database/host", defHost).toString());
    this->setDatabaseName(settings->value("database/name", defDbName).toString());
    this->setPort(settings->value("database/port", defPort).toInt());
    this->setUserName(settings->value("database/user", defUser).toString());

    if (pwdCipherFunc && settings->contains("database/password")) {
        const QByteArray decryptedPwd =
                pwdCipherFunc(settings->value("database/password").toByteArray());
        this->setPassword(decryptedPwd);
    }
    else {
        this->setPassword(defPwd);
    }
}

/*! \brief Write settings to persistent storage
 *  \param pwdCipherFunc Function used to encrypt the password. If \c null then an
 *         empty password is stored. Otherwise the password() is reprensented as
 *         a UTF-8 byte array and passed to pwdCipherFunc
 */
void DatabaseSettings::write(QSettings* settings, CipherFunction&& pwdCipherFunc) const
{
    if (settings == NULL)
        return;

    settings->setValue("database/host", this->host());
    settings->setValue("database/name", this->databaseName());
    settings->setValue("database/port", this->port());
    settings->setValue("database/user", this->userName());

    if (pwdCipherFunc) {
        const QByteArray pwd = this->password().toUtf8();
        settings->setValue("database/password", pwdCipherFunc(pwd));
    }
    else {
        settings->setValue("database/password", QString());
    }
}

/*! \brief Apply the current settings to a QSqlDatabase instance
 *  \note It does not close/open the connection of \p db
 */
void DatabaseSettings::applyTo(QSqlDatabase* db) const
{
    if (db != NULL) {
        db->setDatabaseName(this->databaseName());
        db->setHostName(this->host());
        db->setPort(this->port());
        db->setUserName(this->userName());
        db->setPassword(this->password());
    }
}

} // namespace qtsql

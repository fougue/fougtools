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

#include "database_connection_settings.h"

#include "../core/abstract_cipher.h"

#include <QtCore/QSettings>
#include <QtSql/QSqlDatabase>

namespace qttools {

/*! \class DatabaseConnectionSettings
 *  \brief Settings to connect to a database. Settings can be loaded and saved from/to a QSettings
 *
 */

DatabaseConnectionSettings::DatabaseConnectionSettings()
  : m_port(0)
{
}

/*! \sa QSqlDatabase::setHostName()
 */
void DatabaseConnectionSettings::setHost(const QString& host)
{
  m_host = host;
}

/*! \sa QSqlDatabase::hostName()
 */
QString DatabaseConnectionSettings::host() const
{
  return m_host;
}

/*! \sa QSqlDatabase::setDatabaseName()
 */
void DatabaseConnectionSettings::setDatabaseName(const QString& dbName)
{
  m_dbName = dbName;
}

/*! \sa QSqlDatabase::databaseName()
 */
QString DatabaseConnectionSettings::databaseName() const
{
  return m_dbName;
}

/*! \sa QSqlDatabase::setPort()
 */
void DatabaseConnectionSettings::setPort(int port)
{
  m_port = port;
}

/*! \sa QSqlDatabase::port()
 */
int DatabaseConnectionSettings::port() const
{
  return m_port;
}

/*! \sa QSqlDatabase::setUserName()
 */
void DatabaseConnectionSettings::setUserName(const QString& userName)
{
  m_userName = userName;
}

/*! \sa QSqlDatabase::userName()
 */
QString DatabaseConnectionSettings::userName() const
{
  return m_userName;
}

/*! \sa QSqlDatabase::setPassword()
 */
void DatabaseConnectionSettings::setPassword(const QString& password)
{
  m_password = password;
}

/*! \sa QSqlDatabase::password()
 */
QString DatabaseConnectionSettings::password() const
{
  return m_password;
}

/*! \brief Load settings from the persistent storage
 *  \param passwordCipher Encrypt/decrypt algorithm used to decrypt the password. If \c null then
 *         the default password is returned (see parameter \p defValues)
 *  \param settingsGroup Group to be used when query persistent settings (\sa
 *         QSettings::beginGroup() )
 *  \param defValues Default values when all or some persistent settings could not be retrieved
 */
void DatabaseConnectionSettings::load(const AbstractCipher* passwordCipher,
                                      const QString& settingsGroup,
                                      const SettingsMap& defValues)
{
  const QString defHost = defValues.value("host").toString();
  const QString defDbName = defValues.value("name").toString();
  const int defPort = defValues.value("port").toInt();
  const QString defUser = defValues.value("user").toString();
  const QString defPwd = defValues.value("password").toString();

  QSettings settings;
  if (!settingsGroup.isEmpty())
    settings.beginGroup(settingsGroup);

  this->setHost(settings.value("host", defHost).toString());
  this->setDatabaseName(settings.value("name", defDbName).toString());
  this->setPort(settings.value("port", defPort).toInt());
  this->setUserName(settings.value("user", defUser).toString());

  if (passwordCipher != 0 && settings.contains("password")) {
    const QByteArray decryptedPwd =
        passwordCipher->decrypted(settings.value("password").toByteArray());
    this->setPassword(decryptedPwd);
  }
  else {
    this->setPassword(defPwd);
  }

  if (!settingsGroup.isEmpty())
    settings.endGroup();
}

/*! \brief Write settings to persistent storage
 *  \param passwordCipher Encrypt/decrypt algorithm used to encrypt the password. If \c null then an
 *         empty password is stored. Otherwise the password() is reprensented as a UTF-8 byte array
 *         and passed to to AbstractCipher::encrypted()
 *  \param settingsGroup Group to be used when specifying persistent settings
 *         (\sa QSettings::beginGroup())
 */
void DatabaseConnectionSettings::write(const AbstractCipher* passwordCipher,
                                       const QString& settingsGroup) const
{
  QSettings settings;

  if (!settingsGroup.isEmpty())
    settings.beginGroup(settingsGroup);

  settings.setValue("host", this->host());
  settings.setValue("name", this->databaseName());
  settings.setValue("port", this->port());
  settings.setValue("user", this->userName());

  if (passwordCipher != 0) {
    const QByteArray pwd = this->password().toUtf8();
    settings.setValue("password", passwordCipher->encrypted(pwd));
  }
  else {
    settings.setValue("password", QString());
  }

  if (!settingsGroup.isEmpty())
    settings.endGroup();
}

/*! \brief Apply the current settings to a QSqlDatabase instance
 *  \note It does not close/open the connection of \p db
 */
void DatabaseConnectionSettings::configureDatabase(QSqlDatabase* db) const
{
  if (db == 0)
    return;

  db->setDatabaseName(this->databaseName());
  db->setHostName(this->host());
  db->setPort(this->port());
  db->setUserName(this->userName());
  db->setPassword(this->password());
}

} // namespace qttools

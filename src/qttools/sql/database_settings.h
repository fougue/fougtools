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

#pragma once

class QSettings;
class QSqlDatabase;

#include "sql.h"
#include <QtCore/QByteArray>
#include <QtCore/QHash>
#include <QtCore/QVariant>
#include <functional>

namespace qttools {

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

} // namespace qttools

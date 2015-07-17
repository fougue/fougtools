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

#include "network.h"
#include <QtCore/QString>

namespace qtnetwork {

class QTTOOLS_NETWORK_EXPORT SmtpAccount
{
public:
    enum AuthenticationMethod
    {
        NoAuthentication, // Anonymous
        LoginAuthentication,
        PlainAuthentication,
        CramMd5Authentication
    };

    enum ConnectionSecurity
    {
        NoSecurity,
        StartTlsSecurity,
        SslTlsSecurity
    };

    SmtpAccount();

    QString host() const;
    void setHost(const QString& name);

    int port() const;
    void setPort(int p);

    AuthenticationMethod authenticationMethod() const;
    void setAuthenticationMethod(AuthenticationMethod method);

    ConnectionSecurity connectionSecurity() const;
    void setConnectionSecurity(ConnectionSecurity connSecurity);

    QString userName() const;
    void setUserName(const QString& uname);

    QString password() const;
    void setPassword(const QString& pwd);

    static AuthenticationMethod toAuthenticationMethod(int id, bool* ok = NULL);
    static ConnectionSecurity toConnectionSecurity(int id, bool* ok = NULL);

private:
    QString m_host;
    int m_port;
    AuthenticationMethod m_authMethod;
    ConnectionSecurity m_connSecurity;
    QString m_userName;
    QString m_password;
};

} // namespace qtnetwork

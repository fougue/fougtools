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

#include "smtp_account.h"

namespace qtnetwork {

/*!
 * \class SmtpAccount
 * \brief Provides a convenient interface to define the user account to connect to a SMTP server
 *
 * \headerfile smtp_account.h <qttools/network/smtp_account.h>
 * \ingroup qttools_network
 */

SmtpAccount::SmtpAccount()
    : m_port(25),
      m_authMethod(NoAuthentication),
      m_connSecurity(NoSecurity)
{
}

QString SmtpAccount::host() const
{
    return m_host;
}

void SmtpAccount::setHost(const QString& name)
{
    m_host = name;
}

int SmtpAccount::port() const
{
    return m_port;
}

void SmtpAccount::setPort(int p)
{
    m_port = p;
}

SmtpAccount::AuthenticationMethod SmtpAccount::authenticationMethod() const
{
    return m_authMethod;
}

void SmtpAccount::setAuthenticationMethod(AuthenticationMethod method)
{
    m_authMethod = method;
}

SmtpAccount::ConnectionSecurity SmtpAccount::connectionSecurity() const
{
    return m_connSecurity;
}

void SmtpAccount::setConnectionSecurity(ConnectionSecurity connSecurity)
{
    m_connSecurity = connSecurity;
}

QString SmtpAccount::userName() const
{
    return m_userName;
}

void SmtpAccount::setUserName(const QString& uname)
{
    m_userName = uname;
}

QString SmtpAccount::password() const
{
    return m_password;
}

void SmtpAccount::setPassword(const QString& pwd)
{
    m_password = pwd;
}

/*! \brief Convert integer \p id to a value of SmtpAccount::AuthenticationMethod
 *
 *  If \p ok is not null, it will contain the result state of the conversion
 *
 *  \retval SmtpAccount::NoAuthentication If \p id does not match the enum
 */
SmtpAccount::AuthenticationMethod SmtpAccount::toAuthenticationMethod(int id, bool* ok)
{
    if (ok != NULL)
        *ok = SmtpAccount::NoAuthentication <= id && id <= SmtpAccount::CramMd5Authentication;

    switch (id) {
    case SmtpAccount::NoAuthentication:      return SmtpAccount::NoAuthentication;
    case SmtpAccount::LoginAuthentication:   return SmtpAccount::LoginAuthentication;
    case SmtpAccount::PlainAuthentication:   return SmtpAccount::PlainAuthentication;
    case SmtpAccount::CramMd5Authentication: return SmtpAccount::CramMd5Authentication;
    default: return SmtpAccount::NoAuthentication;
    }
}

/*! \brief Convert integer \p id to a value of SmtpAccount::ConnectionSecurity
 *
 *  If \p ok is not null, it will contain the result state of the conversion
 *
 *  \retval SmtpAccount::NoSecurity If \p id does not match the enum
 */
SmtpAccount::ConnectionSecurity SmtpAccount::toConnectionSecurity(int id, bool* ok)
{
    if (ok != NULL)
        *ok = SmtpAccount::NoSecurity <= id && id <= SmtpAccount::SslTlsSecurity;

    switch (id) {
    case SmtpAccount::NoSecurity:       return SmtpAccount::NoSecurity;
    case SmtpAccount::StartTlsSecurity: return SmtpAccount::StartTlsSecurity;
    case SmtpAccount::SslTlsSecurity:   return SmtpAccount::SslTlsSecurity;
    default: return SmtpAccount::NoSecurity;
    }
}

} // namespace qtnetwork

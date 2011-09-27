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

#include "smtp_account.h"

namespace qttools {

/*! \class SmtpAccount
 *  \brief Provides a convenient interface to define the user account to connect
 *         to a SMTP server
 */

SmtpAccount::SmtpAccount() :
  _port(25),
  _authMethod(NoAuthentication),
  _connSecurity(NoSecurity)
{
}

QString SmtpAccount::host() const
{
  return _host;
}

void SmtpAccount::setHost(const QString& name)
{
  _host = name;
}

int SmtpAccount::port() const
{
  return _port;
}

void SmtpAccount::setPort(int p)
{
  _port = p;
}

SmtpAccount::AuthenticationMethod SmtpAccount::authenticationMethod() const
{
  return _authMethod;
}

void SmtpAccount::setAuthenticationMethod(AuthenticationMethod method)
{
  _authMethod = method;
}

SmtpAccount::ConnectionSecurity SmtpAccount::connectionSecurity() const
{
  return _connSecurity;
}

void SmtpAccount::setConnectionSecurity(ConnectionSecurity connSecurity)
{
  _connSecurity = connSecurity;
}

QString SmtpAccount::userName() const
{
  return _userName;
}

void SmtpAccount::setUserName(const QString& uname)
{
  _userName = uname;
}

QString SmtpAccount::password() const
{
  return _password;
}

void SmtpAccount::setPassword(const QString& pwd)
{
  _password = pwd;
}

/*! \brief Convert integer \p id to a value of SmtpAccount::AuthenticationMethod
 *
 *  If \p ok is not null, it will contain the result state of the conversion
 *
 *  \retval SmtpAccount::NoAuthentication If \p id does not match the enum
 */
SmtpAccount::AuthenticationMethod SmtpAccount::toAuthenticationMethod(int id, bool* ok)
{
  if (ok != 0)
    *ok = SmtpAccount::NoAuthentication <= id && id <= SmtpAccount::CramMd5Authentication;

  switch (id)
  {
  case SmtpAccount::NoAuthentication : return SmtpAccount::NoAuthentication;
  case SmtpAccount::LoginAuthentication : return SmtpAccount::LoginAuthentication;
  case SmtpAccount::PlainAuthentication : return SmtpAccount::PlainAuthentication;
  case SmtpAccount::CramMd5Authentication : return SmtpAccount::CramMd5Authentication;
  default : return SmtpAccount::NoAuthentication;
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
  if (ok != 0)
    *ok = SmtpAccount::NoSecurity <= id && id <= SmtpAccount::SslTlsSecurity;

  switch (id)
  {
  case SmtpAccount::NoSecurity : return SmtpAccount::NoSecurity;
  case SmtpAccount::StartTlsSecurity : return SmtpAccount::StartTlsSecurity;
  case SmtpAccount::SslTlsSecurity : return SmtpAccount::SslTlsSecurity;
  default : return SmtpAccount::NoSecurity;
  }
}

} // namespace qttools

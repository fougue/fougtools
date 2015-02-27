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

#include "mail_send.h"

#include "message.h"
#include "smtp_account.h"
#include <QtCore/QRegExp>
#include <QtNetwork/QNetworkProxy>
#ifndef QT_NO_SSL
# include <QtNetwork/QSslSocket>
#else
# define QTTOOLS_MAILSEND_SSL_WARNING \
    __FILE__": SSL is disabled in Qt, qtnetwork::MailSend will use regular QTcpSocket"
# if defined(Q_CC_GNU)
#  warning QTTOOLS_MAILSEND_SSL_WARNING
# elif defined(Q_CC_MSVC)
#  pragma message(QTTOOLS_MAILSEND_SSL_WARNING)
# endif
# include <QtNetwork/QTcpSocket>
#endif // !QT_NO_SSL

#ifdef QTTOOLS_MAILSEND_TRACE
# include <QtCore/QtDebug>
#endif // QTTOOLS_MAILSEND_TRACE

namespace qtnetwork {

/*! \class MailSend::Private
 *  \brief Private (pimpl of MailSend)
 */

class MailSend::Private : public QObject
{
    Q_OBJECT

public:
    Private()
#ifndef QT_NO_SSL
        : m_socket(new QSslSocket(this)),
      #else
        : m_socket(new QTcpSocket(this)),
      #endif // !QT_NO_SSL
          m_timeout(30000)
    {
    }

    bool sendSmtpCommand(const QByteArray& cmd, int expectedCode)
    {
#ifdef QTTOOLS_MAILSEND_TRACE
        qDebug() << "C :" << cmd;
#endif // QTTOOLS_MAILSEND_TRACE
        if (m_socket->write(cmd + "\r\n") == -1) {
            //: %1: SMTP client command
            m_error = tr("Failed to write command '%1'").arg(QString(cmd));
            return false;
        }
        if (!m_socket->waitForBytesWritten(m_timeout)) {
            //: %1: SMTP client command
            m_error = tr("Failed to write command '%1' (timeout)").arg(QString(cmd));
            return false;
        }
        if (!m_socket->waitForReadyRead(m_timeout)) {
            //: %1: SMTP client command
            m_error = tr("Failed to read response for command '%1' (timeout)").arg(QString(cmd));
            return false;
        }

        const QByteArray response(m_socket->readAll());
#ifdef QTTOOLS_MAILSEND_TRACE
        qDebug() << "S:" << response;
#endif // QTTOOLS_MAILSEND_TRACE
        QRegExp codeRx(QLatin1String("^\\s*([0-9]+)"));
        const int responseCode = codeRx.indexIn(response) != -1 ? codeRx.cap(1).toInt() : -1;
        if (responseCode == -1) {
            //: %1: SMTP server response
            m_error = tr("Invalid response format '%1'").arg(QString(response));
        }
        else if (responseCode != expectedCode) {
            //: %1 and %2: SMTP server response codes   %3: whole SMTP server response
            m_error = tr("Unexpected response code, got %1 instead of %2\n%3")
                    .arg(responseCode).arg(expectedCode).arg(QString(response));
        }
        return responseCode == expectedCode && responseCode != -1;
    }

    bool sendSmtpCommand(const char* cmd, int expectedCode)
    {
        return this->sendSmtpCommand(QByteArray(cmd), expectedCode);
    }

#ifndef QT_NO_SSL
    QSslSocket* m_socket;
#else
    QTcpSocket* m_socket;
#endif // !QT_NO_SSL

    SmtpAccount m_smtpAccount;
    int m_timeout;
    QString m_error;

private slots:
    void onProxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* auth)
    {
        Q_UNUSED(proxy);
        Q_UNUSED(auth);
    }
};

/*!
 * \class MailSend
 * \brief Provides service to send messages through SMTP
 *
 * \headerfile mail_send.h <qttools/network/mail_send.h>
 * \ingroup qttools_network
 */

MailSend::MailSend()
    : d(new Private)
{
}

MailSend::~MailSend()
{
    d->m_socket->disconnectFromHost();
    delete d;
}

/*! \brief Maximum waiting delay when operating with the SMTP server
 *
 *  The time out is \c 30 seconds by default
 *
 *  \sa setTimeout()
 */
int MailSend::timeout() const
{
    return d->m_timeout;
}

void MailSend::setTimeout(int msecs)
{
    d->m_timeout = msecs;
}

/*! \brief Try to connect to SMTP server using \p account
 *
 *  On failure, the error can be reported by errorString()
 *
 *  \return \c true on success \c false otherwise
 */
bool MailSend::connectToSmtpServer(const SmtpAccount& account)
{
    d->m_error.clear();
    d->m_smtpAccount = account;

    // Connect to SMTP server
    d->m_socket->connectToHost(account.host(), account.port());
    if (!d->m_socket->waitForConnected(this->timeout())) {
        //: %1: Error description
        d->m_error = Private::tr("Connection failed (timeout)\n%1").arg(d->m_socket->errorString());
        return false;
    }

    // Start client-side encryption if SSL required
    if (account.connectionSecurity() == SmtpAccount::SslTlsSecurity) {
#ifndef QT_NO_SSL
        d->m_socket->setProtocol(QSsl::AnyProtocol);
        d->m_socket->startClientEncryption();
#else
        d->m_error = Private::tr("SSL support is disabled in Qt");
        return false;
#endif // !QT_NO_SSL
    }

    // Read initial server response
    if (!d->m_socket->waitForReadyRead(this->timeout())) {
        //: %1: Error description
        d->m_error = Private::tr("Failed to read server response after "
                                 "connection\n%1").arg(d->m_socket->errorString());
        return false;
    }
#ifdef QTTOOLS_MAILSEND_TRACE
    qDebug() << "S:" << d->m_socket->readAll();
#endif // QTTOOLS_MAILSEND_TRACE

    // Hello to the SMTP server
    if (!d->sendSmtpCommand("EHLO qtnetwork::MailSend", 250)) {
        if (!d->sendSmtpCommand("HELO qtnetwork::MailSend", 250))
            return false;
    }

    // Initiate TLS if required
    if (account.connectionSecurity() == SmtpAccount::StartTlsSecurity) {
#ifndef QT_NO_SSL
# if QT_VERSION > 0x050000
        d->m_socket->setProtocol(QSsl::TlsV1_0);
# else
        d->m_socket->setProtocol(QSsl::TlsV1);
# endif // QT_VERSION
        if (!d->sendSmtpCommand("STARTTLS", 220))
            return false;
        d->m_socket->startClientEncryption();
#else
        d->m_error = Private::tr("SSL support is disabled in Qt");
        return false;
#endif // !QT_NO_SSL
    }

    // User authentication
    switch (account.authenticationMethod()) {
    case SmtpAccount::NoAuthentication:
        break;
    case SmtpAccount::LoginAuthentication: {
        if (!d->sendSmtpCommand("AUTH LOGIN", 334))
            return false;
        if (!d->sendSmtpCommand(account.userName().toUtf8().toBase64(), 334))
            return false;
        if (!d->sendSmtpCommand(account.password().toUtf8().toBase64(), 235))
            return false;
        break;
    }
    case SmtpAccount::PlainAuthentication: {
        if (!d->sendSmtpCommand("AUTH PLAIN", 334))
            return false;
        QByteArray auth;
        auth.append(char(0));
        auth.append(account.userName().toUtf8());
        auth.append(char(0));
        auth.append(account.password().toUtf8());
        if (!d->sendSmtpCommand(auth.toBase64(), 235))
            return false;
        break;
    }
    case SmtpAccount::CramMd5Authentication: {
        if (!d->sendSmtpCommand("AUTH CRAM-MD5", 334))
            return false;
        break;
    }
    }
    return true;
}

/*! \brief Try to send message \p msg
 *
 *  On failure, the error can be reported by errorString()
 *
 *  \return \c true on success \c false otherwise
 */
bool MailSend::sendMessage(const Message& msg)
{
    d->m_error.clear();
    if (!d->sendSmtpCommand(QString("MAIL FROM:<%1>").arg(msg.from()).toUtf8(), 250))
        return false;
    foreach (const QString& recipient, msg.to()) {
        if (!d->sendSmtpCommand(QString("RCPT TO:<%2>").arg(recipient).toUtf8(), 250))
            return false;
    }
    if (!d->sendSmtpCommand("DATA", 354))
        return false;
    QString data;
    data.append(QString("Content-type: text/plain; charset=utf-8\r\n"));
    data.append(QString("From: <%1>\r\n").arg(msg.from()));
    data.append(QString("To: <%1>\r\n").arg(msg.to().join(QLatin1String(";"))));
    data.append(QString("Date: %1\r\n").arg(msg.dateTime().toString()));
    data.append(QString("Subject: %1\r\n\r\n").arg(msg.subject()));
    data.append(msg.body() + "\r\n");
    if (!d->sendSmtpCommand(data.toUtf8() + ".", 250))
        return false;
    if (!d->sendSmtpCommand("QUIT", 221))
        return false;
    return true;
}

/*! \brief Description of the last error when operating with the SMTP server
 *  \retval QString() If not any error occurred
 */
QString MailSend::errorString() const
{
    return d->m_error;
}

} // namespace qtnetwork

#include "mail_send.moc"

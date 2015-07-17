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

#include "message.h"

namespace qtnetwork {

/*!
 * \class Message
 * \brief Provides a convenient interface for working with messages
 *
 * \headerfile message.h <qttools/network/message.h>
 * \ingroup qttools_network
 */

Message::Message()
    : m_dateTime(QDateTime::currentDateTime())
{
}

QString Message::from() const
{
    return m_from;
}

void Message::setFrom(const QString& addr)
{
    m_from = addr;
}

QStringList Message::to() const
{
    return m_to;
}

void Message::setTo(const QStringList& recipients)
{
    m_to = recipients;
}

QDateTime Message::dateTime() const
{
    return m_dateTime;
}

void Message::setDateTime(const QDateTime& d)
{
    m_dateTime = d;
}

QString Message::subject() const
{
    return m_subject;
}

void Message::setSubject(const QString& text)
{
    m_subject = text;
}

QString Message::body() const
{
    return m_body;
}

void Message::setBody(const QString& text)
{
    m_body = text;
}

} // namespace qtnetwork

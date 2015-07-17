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
#include <QtCore/QDateTime>
#include <QtCore/QStringList>

namespace qtnetwork {

class QTTOOLS_NETWORK_EXPORT Message
{
public:
    Message();

    QString from() const;
    void setFrom(const QString& addr);

    QStringList to() const;
    void setTo(const QStringList& recipients);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime& d);

    QString subject() const;
    void setSubject(const QString& text);

    QString body() const;
    void setBody(const QString& text);

private:
    QString m_from;
    QStringList m_to;
    QDateTime m_dateTime;
    QString m_subject;
    QString m_body;
};

} // namespace qtnetwork

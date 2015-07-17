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

#include "core.h"
#include <QtCore/Qt>
class QObject;

namespace qtcore {

class QTTOOLS_CORE_EXPORT ScopedConnect
{
public:
    ScopedConnect(const QObject* sender, const char* signal,
                  const QObject* receiver, const char* slot,
                  Qt::ConnectionType type = Qt::UniqueConnection);
    ~ScopedConnect();

private:
    const QObject* m_sender;
    const QObject* m_receiver;
    const char* m_signal;
    const char* m_slot;
};

class QTTOOLS_CORE_EXPORT ScopedDisconnect
{
public:
    ScopedDisconnect(const QObject* sender, const char* signal,
                     const QObject* receiver, const char* slot,
                     Qt::ConnectionType type = Qt::UniqueConnection);
    ~ScopedDisconnect();

private:
    const QObject* m_sender;
    const QObject* m_receiver;
    const char* m_signal;
    const char* m_slot;
    const Qt::ConnectionType m_type;
};

} // namespace qtcore

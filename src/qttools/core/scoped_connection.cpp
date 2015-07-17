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

#include "scoped_connection.h"

#include <QtCore/QObject>

namespace qtcore {

/*!
 * \class ScopedConnect
 * \brief Establishes a signal/slot connection between two QObjects and
 *        automatically breaks it upon destruction
 *
 * \headerfile scoped_connection.h <qttools/core/scoped_connection.h>
 * \ingroup qttools_core
 *
 *
 *  ScopedConnect guarantees that a signal/slot connection will get broken when
 *  the current scope dissapears
 */

ScopedConnect::ScopedConnect(const QObject* sender, const char* signal,
                             const QObject* receiver, const char* slot,
                             Qt::ConnectionType type)
    : m_sender(sender),
      m_receiver(receiver),
      m_signal(signal),
      m_slot(slot)
{
    QObject::connect(sender, signal, receiver, slot, type);
}

ScopedConnect::~ScopedConnect()
{
    QObject::disconnect(m_sender, m_signal, m_receiver, m_slot);
}

/*!
 * \class ScopedDisonnect
 * \brief Breaks a signal/slot connection between two QObjects and automatically
 *        re-establishes it upon destruction
 *
 * \headerfile scoped_connection.h <qttools/core/scoped_connection.h>
 * \ingroup qttools_core
 *
 *  ScopedDisonnect guarantees that a signal/slot connection will get restored
 *  when the current scope dissapears
 */

ScopedDisconnect::ScopedDisconnect(const QObject* sender, const char* signal,
                                   const QObject* receiver, const char* slot,
                                   Qt::ConnectionType type)
    : m_sender(sender),
      m_receiver(receiver),
      m_signal(signal),
      m_slot(slot),
      m_type(type)
{
    QObject::disconnect(sender, signal, receiver, slot);
}

ScopedDisconnect::~ScopedDisconnect()
{
    QObject::connect(m_sender, m_signal, m_receiver, m_slot, m_type);
}

} // namespace qtcore

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

#include "log.h"

#include <QtCore/QList>
#include <QtCore/QLinkedList>
#include <QtCore/QMetaType>
#include <QtCore/QPair>

namespace qttools {

namespace internal {

static QList<qttools::AbstractLogHandler*>* globalLogHandlers()
{
  static QList<qttools::AbstractLogHandler*> object;
  return &object;
}

typedef QPair<qttools::Log::MessageType, QString> PendingLogMessage;
static QLinkedList<PendingLogMessage>* globalPendingMessages()
{
  static QLinkedList<PendingLogMessage> object;
  return &object;
}

static void handleLogMessage(qttools::Log::MessageType msgType, const QString& msg)
{
  if (globalLogHandlers()->isEmpty())
    globalPendingMessages()->append(qMakePair(msgType, msg));
  foreach (qttools::AbstractLogHandler* logHandler, *(globalLogHandlers()))
    logHandler->handle(msgType, msg );
}

} // namespace internal

/*! \struct Log::Stream
 *  \brief Encapsulates a reference-counted QTextStream so a Log object can be quickly copied
 */

struct Log::Stream
{
  Stream(MessageType mType);
  Log::MessageType msgType;
  QString buffer;
  QTextStream ts;
  int refCount;

  template<typename T>
  static Log& defaultQTextStreamOutput(Log& log, T value)
  {
      if (log.m_stream != NULL)
        log.m_stream->ts << value;
      return log.space();
  }
};


Log::Stream::Stream(Log::MessageType mType)
  : msgType(mType),
    ts(&buffer),
    refCount(1)
{
}

/*!
 * \class Log
 * \brief Provides an easy-to-use output stream for logging
 *
 * \headerfile log.h <qttools/core/log.h>
 * \ingroup qttools_core
 *
 * This class is almost a clone of QDebug, but it's focused on logging.\n
 * Also the way messages are handled is different as there can be multiple logging handlers
 * attached (not just one).
 */

/*! \enum Log::MessageType
 *  \brief Types of logging message, with increasing severity
 */

//! \brief Construct a null Log stream, ie. it won't print anything
Log::Log()
  : m_stream(NULL)
{
}

/*! \brief Construct a Log stream for messages of a special type
 */
Log::Log(MessageType msgType)
  : m_stream(new Stream(msgType))
{
}

/*! \brief Construct a copy of the \p other Log stream
 */
Log::Log(const Log& other)
  : m_stream(other.m_stream)
{
  if (m_stream != NULL)
    ++(m_stream->refCount);
}

/*! \brief Flush any pending data to be written and destroys the Log stream
 */
Log::~Log()
{
  if (m_stream != NULL) {
    --(m_stream->refCount);
    if (m_stream->refCount == 0) {
      internal::handleLogMessage(m_stream->msgType, m_stream->buffer.toLocal8Bit().data());
      delete m_stream;
    }
  }
}

/*! \brief Write a space character to the Log stream and return a reference to the stream
 */
Log& Log::space()
{
  if (m_stream != NULL)
    m_stream->ts << ' ';
  return *this;
}

/*! \brief Write the boolean \p t to the log stream and return a reference to the stream
 */
Log& Log::operator<<(bool t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t ? "true" : "false");
}

Log& Log::operator<<(char t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(short t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(unsigned short t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(int t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(unsigned int t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(long t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(unsigned long t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(float t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(double t)
{
  return Log::Stream::defaultQTextStreamOutput(*this, t);
}

Log& Log::operator<<(const char* str)
{
  return Log::Stream::defaultQTextStreamOutput(*this, str);
}

Log& Log::operator<<(const QString& str)
{
  return Log::Stream::defaultQTextStreamOutput(*this, str);
}

void Log::registerMetaTypes()
{
  static bool alreadyRegistered = false;
  if (!alreadyRegistered) {
    qRegisterMetaType<MessageType>("Log::MessageType");
    qRegisterMetaType<MessageType>("qttools::Log::MessageType");
    alreadyRegistered = true;
  }
}

// --
// -- Related functions
// --

/*! \brief
 *  \relates Log
 */
Log debugLog()
{
  return Log(Log::DebugMessage);
}

/*! \brief
 *  \relates Log
 */
Log infoLog()
{
  return Log(Log::InfoMessage);
}

/*! \brief
 *  \relates Log
 */
Log warningLog()
{
  return Log(Log::WarningMessage);
}

/*! \brief
 *  \relates Log
 */
Log criticalLog()
{
  return Log(Log::CriticalMessage);
}

/*! \brief
 *  \relates Log
 */
Log fatalLog()
{
  return Log(Log::FatalMessage);
}

/*!
 * \class AbstractLogHandler
 * \brief Abstract base class of all logging message handlers
 *
 * \headerfile log.h <qttools/core/log.h>
 * \ingroup qttools_core
 */

AbstractLogHandler::AbstractLogHandler()
  : m_autoDetach(false)
{
}

AbstractLogHandler::~AbstractLogHandler()
{
  if (m_autoDetach)
    qttools::detachGlobalLogHandler(this);
}

/*! \fn void AbstractLogHandler::handle(Log::MessageType, const QString&)
 *  \brief Handle logging message \p msg of type \p msgType
 */

/*! \brief Set the log handler to auto-detach mode if \p b is true
 *
 *  If auto-detach is enabled then when the log handler is destroyed it gets automatically detached
 *  from the global list of log handlers.\n
 *  Auto-detach is disabled by default
 */
void AbstractLogHandler::setAutoDetach(bool b)
{
  m_autoDetach = b;
}

/*! \brief Append \p handler to the global list of log handlers
 *
 *  If the internal list of log handlers is empty then all pending log messages are flushed to
 *  \p handler.
 *
 *  Note that log messages are recorded when there is no log handler attached.
 *  In this case a log message is considered as "pending".
 *
 *  \relates Log
 */
void attachGlobalLogHandler(AbstractLogHandler* handler)
{
  if (handler != NULL) {
    if (internal::globalLogHandlers()->isEmpty()
        && !internal::globalPendingMessages()->isEmpty())
    {
      foreach (const internal::PendingLogMessage& msg, *(internal::globalPendingMessages()))
        handler->handle(msg.first, msg.second);
      internal::globalPendingMessages()->clear();
    }
    internal::globalLogHandlers()->append(handler);
  }
}

/*! \brief Remove \p handler from the global list of log handlers
 *  \relates Log
 */
void detachGlobalLogHandler(AbstractLogHandler* handler)
{
  if (handler != NULL)
    internal::globalLogHandlers()->removeAll(handler);
}

/*!
 * \class LogDispatcher
 * \brief Dispatches a logging message as a Qt signal
 *
 * \headerfile log.h <qttools/core/log.h>
 * \ingroup qttools_core
 */

LogDispatcher::LogDispatcher(QObject* parent)
  : QObject(parent)
{
}

/*! \brief Emits the signal log(msgType, msg)
 */
void LogDispatcher::handle(Log::MessageType msgType, const QString& msg)
{
  emit log(msgType, msg);
}

} // namespace qttools

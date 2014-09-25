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

#ifndef QTTOOLS_LOG_H
#define QTTOOLS_LOG_H

#include "core.h"
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTextStream>

namespace qttools {

// --
// -- class Log
// --
class QTTOOLS_CORE_EXPORT Log
{
public:
  enum MessageType
  {
    DebugMessage,
    InfoMessage,
    WarningMessage,
    CriticalMessage,
    FatalMessage
  };

  Log();
  Log(MessageType msgType);
  Log(const Log& other);
  ~Log();

  Log& space();
  Log& operator<<(bool);
  Log& operator<<(char);
  Log& operator<<(short);
  Log& operator<<(unsigned short);
  Log& operator<<(int);
  Log& operator<<(unsigned int);
  Log& operator<<(long);
  Log& operator<<(unsigned long);
  Log& operator<<(qlonglong);
  Log& operator<<(qulonglong);
  Log& operator<<(float);
  Log& operator<<(double);
  Log& operator<<(const char*);
  Log& operator<<(const QString&);

  template <typename T>
  Log& operator<<(const T* ptr);

  static void registerMetaTypes();

private:
  Log& operator=(const Log& other); // disabled

  struct Stream;
  Stream* m_stream;
};

QTTOOLS_CORE_EXPORT Log debugLog();
QTTOOLS_CORE_EXPORT Log infoLog();
QTTOOLS_CORE_EXPORT Log warningLog();
QTTOOLS_CORE_EXPORT Log criticalLog();
QTTOOLS_CORE_EXPORT Log fatalLog();

// --
// -- class AbstractLogHandler
// --
class QTTOOLS_CORE_EXPORT AbstractLogHandler
{
public:
  AbstractLogHandler();
  virtual ~AbstractLogHandler();
  virtual void handle(Log::MessageType msgType, const QString& msg) = 0;
  void setAutoDetach(bool b);
private:
  bool m_autoDetach;
};
QTTOOLS_CORE_EXPORT void attachGlobalLogHandler(AbstractLogHandler* handler);
QTTOOLS_CORE_EXPORT void detachGlobalLogHandler(AbstractLogHandler* handler);

// --
// -- class LogDispatcher
// --
class QTTOOLS_CORE_EXPORT LogDispatcher :
    public QObject,
    public AbstractLogHandler
{
  Q_OBJECT
public:
  LogDispatcher(QObject* parent = NULL);
  void handle(Log::MessageType msgType, const QString& msg);
signals:
  void log(qttools::Log::MessageType msgType, const QString& msg);
};

// --
// -- Implementation
// --

template <typename T>
Log& Log::operator<<(const T* ptr)
{
  return *this << QString("0x%1").arg(reinterpret_cast<std::size_t>(ptr), 0, 16);
}

} // namespace qttools

#endif // QTTOOLS_LOG_H

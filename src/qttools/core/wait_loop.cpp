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

#include "wait_loop.h"

#include <QtCore/QTimerEvent>
#include <QtCore/QtDebug>

namespace qttools {

namespace internal {

// --
// -- WaitLoopTimeOutStopCondition
// --

class WaitLoopTimeOutStopCondition : public QObject, public WaitLoop::StopCondition
{
public:
  WaitLoopTimeOutStopCondition(QObject* parent = NULL);

  void setInterval(int msec);

protected:
  void beginWait();
  void stopWait();
  void timerEvent(QTimerEvent* event);

private:
  int m_interval;
  int m_timerId;
};

} // namespace internal

// --
// -- WaitLoop::Private
// --

class WaitLoop::Private
{
public:
  Private(WaitLoop* backPtr);

  void stopWait();
  void endWaitLoop(WaitLoop::StopCondition* endCond);
  internal::WaitLoopTimeOutStopCondition* timeOutStopCondition() const;

  QEventLoop m_eventLoop;
  QList<WaitLoop::StopCondition*> m_stopConditions;
  WaitLoop::StopCondition* m_exitStopCondition;

private:
  WaitLoop* m_backPtr;
};

// --
// -- WaitLoop::StopCondition::Private
// --

class WaitLoop::StopCondition::Private
{
public:
  Private();

  WaitLoop* m_waitLoop;
};

// --
// -- WaitLoop::StopCondition::Private (Impl)
// --

WaitLoop::StopCondition::Private::Private()
  : m_waitLoop(NULL)
{
}

// --
// -- WaitLoop::Private (Impl)
// --

WaitLoop::Private::Private(WaitLoop *backPtr)
  : m_eventLoop(backPtr),
    m_exitStopCondition(NULL),
    m_backPtr(backPtr)
{
}

void WaitLoop::Private::stopWait()
{
  foreach (WaitLoop::StopCondition* cond, m_stopConditions)
    cond->stopWait();
}

void WaitLoop::Private::endWaitLoop(WaitLoop::StopCondition* endCond)
{
  m_exitStopCondition = endCond;
  this->stopWait();
  if (m_eventLoop.isRunning()) {
    if (endCond == this->timeOutStopCondition())
      m_eventLoop.exit(-1);
    else
      m_eventLoop.quit();
  }
}

internal::WaitLoopTimeOutStopCondition *WaitLoop::Private::timeOutStopCondition() const
{
  if (m_stopConditions.isEmpty())
    return NULL;
  return static_cast<internal::WaitLoopTimeOutStopCondition*>(m_stopConditions.first());
}

namespace internal {

// --
// -- WaitLoopTimeOutStopCondition (Impl)
// --

WaitLoopTimeOutStopCondition::WaitLoopTimeOutStopCondition(QObject* parent)
  : QObject(parent),
    m_interval(-1),
    m_timerId(-1)
{
}

void WaitLoopTimeOutStopCondition::setInterval(int msec)
{
  m_interval = msec;
}

void WaitLoopTimeOutStopCondition::beginWait()
{
  if (m_interval > 0)
    m_timerId = this->startTimer(m_interval);
}

void WaitLoopTimeOutStopCondition::stopWait()
{
  if (m_timerId != -1)
    this->killTimer(m_timerId);
  m_timerId = -1;
}

void WaitLoopTimeOutStopCondition::timerEvent(QTimerEvent* event)
{
  if (event != NULL && event->timerId() == m_timerId)
    this->endWaitLoop();
}

} // namespace internal

// --
// -- WaitLoop::StopCondition (Impl)
// --

WaitLoop::StopCondition::StopCondition()
  : d(new WaitLoop::StopCondition::Private)
{
}

WaitLoop::StopCondition::~StopCondition()
{
  delete d;
}

WaitLoop *WaitLoop::StopCondition::waitLoop() const
{
  return d->m_waitLoop;
}

void WaitLoop::StopCondition::beginWait()
{
}

void WaitLoop::StopCondition::stopWait()
{
}

void WaitLoop::StopCondition::endWaitLoop()
{
  this->stopWait();
  if (d->m_waitLoop != NULL)
    d->m_waitLoop->d->endWaitLoop(this);
}

// --
// -- WaitLoop (Impl)
// --

WaitLoop::WaitLoop(QObject *parent)
  : QObject(parent),
    d(new WaitLoop::Private(this))
{
  this->addStopCondition(new internal::WaitLoopTimeOutStopCondition(this));
}

WaitLoop::~WaitLoop()
{
  d->stopWait();
  d->m_stopConditions.removeFirst(); // TimeOut stop condition is deleted by parent QObject
  //qDeleteAll(d->m_stopConditions);
  delete d;
}

void WaitLoop::addStopCondition(WaitLoop::StopCondition *cond)
{
  if (cond == NULL)
    return;

  cond->d->m_waitLoop = this;
  d->m_stopConditions.append(cond);
}

void WaitLoop::removeStopCondition(WaitLoop::StopCondition *cond)
{
    d->m_stopConditions.removeOne(cond);
}

bool WaitLoop::exec(int msec)
{
  return this->exec(QEventLoop::AllEvents, msec);
}

bool WaitLoop::exec(QEventLoop::ProcessEventsFlags flags, int msec)
{
  d->m_exitStopCondition = NULL;
  d->timeOutStopCondition()->setInterval(msec);
  foreach (StopCondition* cond, d->m_stopConditions) {
    if (d->m_exitStopCondition == NULL)
      cond->beginWait();
    else
      break;
  }

  int exitCode = 0;
  if (d->m_exitStopCondition == NULL)
    exitCode = d->m_eventLoop.exec(flags);
  else
    exitCode = (d->m_exitStopCondition != d->timeOutStopCondition()) ? 0 : -1;

  return exitCode != -1;
}

WaitLoop::StopCondition *WaitLoop::exitStopCondition() const
{
  return d->m_exitStopCondition;
}

} // namespace qttools

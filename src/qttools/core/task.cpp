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

#include "qttools/core/task.h"

#include "cpptools/functional.h"
#include <QtCore/QEventLoop>
#include <QtCore/QMutex>
#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QtCore/QMutexLocker>
#include <QtCore/QTimer>
#include <QtCore/QTimerEvent>
#include <limits>

#include <QtCore/QtDebug>

template<typename LOOP_PREDICATE>
void waitFor(LOOP_PREDICATE loopPredicate, int maxTime = -1)
{
  if (maxTime <= -1)
    maxTime = std::numeric_limits<int>::max();
  QTime time;
  int waitForStopTime = 0;
  time.start();
  while (loopPredicate() && waitForStopTime < maxTime)
    waitForStopTime += time.elapsed() - waitForStopTime;
}

namespace qttools {

/*! \class TaskPrivate
 *  \brief Internal (pimpl for Task)
 */

class TaskPrivate
{
public:
  TaskPrivate();

  bool m_isBoundToThread;
  bool m_isRunning;
  bool m_isWaitingStop;
  bool m_autoDeleteBoundThread;
  int m_loopCount;
  int m_loopInterval;
  QMutex m_mutex;
};

TaskPrivate::TaskPrivate()
  : m_isBoundToThread(false),
    m_isRunning(false),
    m_isWaitingStop(false),
    m_autoDeleteBoundThread(true),
    m_loopCount(1),
    m_loopInterval(50),
    m_mutex(QMutex::Recursive)
{
}

/*! \class Task
 *  \brief Abstract base class for all objects that perform an operation
 */

Task::Task(QObject* parent)
  : QObject(parent),
    d_ptr(new TaskPrivate)
{
}

Task::~Task()
{
  Q_D(Task);
  if (this->thread() != 0 && this->isBoundToThread() && this->autoDeleteBoundThread())
    delete this->thread();
  delete d;
}

bool Task::isRunning() const
{
  Q_D(const Task);
  return d->m_isRunning;
}

bool Task::isWaitingStop() const
{
  Q_D(const Task);
  return d->m_isWaitingStop;
}

bool Task::isBoundToThread() const
{
  Q_D(const Task);
  return d->m_isBoundToThread;
}

bool Task::autoDeleteBoundThread() const
{
  Q_D(const Task);
  return d->m_autoDeleteBoundThread;
}

int Task::loopCount() const
{
  Q_D(const Task);
  return d->m_loopCount;
}

int Task::loopInterval() const
{
  Q_D(const Task);
  return d->m_loopInterval;
}

void Task::bindToThread(QThread* thread)
{
  Q_D(Task);
  if (thread == 0)
    return;

  if (this->isBoundToThread()) {
    disconnect(this->thread(), SIGNAL(started()), this, SLOT(exec()));
    disconnect(this, SIGNAL(finished()), this->thread(), SLOT(quit()));
    disconnect(this, SIGNAL(stopped()), this->thread(), SLOT(quit()));
  }

  this->moveToThread(thread);
  d->m_isBoundToThread = true;
  connect(thread, SIGNAL(started()), this, SLOT(exec()), Qt::UniqueConnection);
  connect(this, SIGNAL(finished()), thread, SLOT(quit()), Qt::UniqueConnection);
  connect(this, SIGNAL(stopped()), thread, SLOT(quit()), Qt::UniqueConnection);
}

void Task::exec()
{
  Q_D(Task);
  if (this->isWaitingStop())
    return this->acknowledgeStop();

  d->m_isRunning = true;
  int currLoop = 0;
  QEventLoop eventLoop;
  connect(this, SIGNAL(aboutToStop()), &eventLoop, SLOT(quit()));

  emit started();

  while (!this->isWaitingStop() && (currLoop < this->loopCount() || this->loopCount() < 0)) {
    this->action();
    if (this->loopInterval() > 0 && (currLoop + 1 < this->loopCount() || this->loopCount() < 0)) {
      QTimer::singleShot(this->loopInterval(), &eventLoop, SLOT(quit()));
      eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
      //::waitFor(boost::bind(&::infiniteLoopPredicate), this->loopInterval());
    }
    ++currLoop;
  } // end while()

  if (this->isWaitingStop()) {
    this->acknowledgeStop();
  }
  else {
    d->m_isRunning = false;
    emit finished();
    if (this->isBoundToThread())
      this->thread()->quit();
  }
}

void Task::asynchronousStop()
{
  Q_D(Task);
  //QMutexLocker locker(&d->m_mutex); Q_UNUSED(locker);
  if (this->isWaitingStop() || !this->isRunning())
    return;
  d->m_isWaitingStop = true;
  emit aboutToStop();
}

void Task::stop(int maxTime)
{
  QThread* taskThread = this->thread();

  // Try to stop the task, wait until stop is acknowledged or timed out
  this->asynchronousStop();

  // Wait for task stop
  if (this->isBoundToThread()) {
    ::waitFor(cpp::bind(std::mem_fun(&Task::isRunning), this), maxTime);
    taskThread->quit();
    ::waitFor(cpp::bind(std::mem_fun(&QThread::isRunning), taskThread), maxTime);
  }

  // Handle the case when normal task stop fails
  if (this->isBoundToThread() && taskThread->isRunning()) {
    qDebug() << "Task::stop():" << this << "asynchronous stop failed, task is still running";
    // Task asynchronous stop failed, try to exit the thread's event loop
    taskThread->exit(-1);
    if (!taskThread->isRunning()) {
      // The thread is still running, force unsafe termination
      taskThread->terminate();
      this->acknowledgeStop();
    }
  } // end if (taskThread->isRunning())
}

void Task::setAutoDeleteBoundThread(bool v)
{
  Q_D(Task);
  d->m_autoDeleteBoundThread = v;
}

void Task::setLoopCount(int v)
{
  Q_D(Task);
  d->m_loopCount = v;
}

void Task::setLoopInterval(int msecs)
{
  Q_D(Task);
  d->m_loopInterval = msecs;
}

void Task::acknowledgeStop()
{
  Q_D(Task);
  //QMutexLocker locker(&d->m_mutex); Q_UNUSED(locker);
  d->m_isWaitingStop = false;
  d->m_isRunning = false;
  emit stopped();
  if (this->isBoundToThread())
    this->thread()->quit();
}

} // namespace qttools

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
#include "qttools/core/task_p.h"

#include "cpptools/functional.h"
#include <QtCore/QEventLoop>
#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QtCore/QMutexLocker>
#include <QtCore/QTimer>
#include <QtCore/QTimerEvent>
#include <limits>

#include <QtCore/QtDebug>

namespace {

bool infiniteLoopPredicate()
{
  return true;
}

template<typename _LOOP_PREDICATE_>
void waitFor(_LOOP_PREDICATE_ loopPredicate, int maxTime = -1)
{
  if (maxTime <= -1)
    maxTime = std::numeric_limits<int>::max();
  QTime time;
  int waitForStopTime = 0;
  time.start();
  while (loopPredicate() && waitForStopTime < maxTime)
    waitForStopTime += time.elapsed() - waitForStopTime;
}

} // Anonymous namespace

namespace qttools {

/*! \class TaskPrivate
 *  \brief Internal (pimpl for Task)
 */

TaskPrivate::TaskPrivate() :
  isBoundToThread(false),
  isRunning(false),
  isWaitingStop(false),
  autoDeleteBoundThread(true),
  loopCount(1),
  loopInterval(50),
  mutex(QMutex::Recursive)
{
}



/*! \class Task
 *  \brief Abstract base class for all objects that perform an operation
 */

Task::Task(QObject* parent) :
  QObject(*new TaskPrivate, parent)
{
}

Task::~Task()
{
  if (this->thread() != 0 &&
      this->isBoundToThread() && this->autoDeleteBoundThread())
    delete this->thread();
}

bool Task::isRunning() const
{
  Q_D(const Task);
  return d->isRunning;
}

bool Task::isWaitingStop() const
{
  Q_D(const Task);
  return d->isWaitingStop;
}

bool Task::isBoundToThread() const
{
  Q_D(const Task);
  return d->isBoundToThread;
}

bool Task::autoDeleteBoundThread() const
{
  Q_D(const Task);
  return d->autoDeleteBoundThread;
}

int Task::loopCount() const
{
  Q_D(const Task);
  return d->loopCount;
}

int Task::loopInterval() const
{
  Q_D(const Task);
  return d->loopInterval;
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
  d->isBoundToThread = true;
  connect(thread, SIGNAL(started()), this, SLOT(exec()), Qt::UniqueConnection);
  connect(this, SIGNAL(finished()), thread, SLOT(quit()), Qt::UniqueConnection);
  connect(this, SIGNAL(stopped()), thread, SLOT(quit()), Qt::UniqueConnection);
}

void Task::exec()
{
  Q_D(Task);
  if (this->isWaitingStop())
    return this->acknowledgeStop();

  d->isRunning = true;
  int currLoop = 0;
  QEventLoop eventLoop;
  connect(this, SIGNAL(aboutToStop()), &eventLoop, SLOT(quit()));

  emit started();

  while (!this->isWaitingStop() &&
         (currLoop < this->loopCount() || this->loopCount() < 0)) {
    this->action();
    if (this->loopInterval() > 0 &&
        (currLoop + 1 < this->loopCount() || this->loopCount() < 0)) {
      QTimer::singleShot(this->loopInterval(), &eventLoop, SLOT(quit()));
      eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
      //::waitFor(boost::bind(&::infiniteLoopPredicate), this->loopInterval());
    }
    ++currLoop;
  } // end while()
  if (this->isWaitingStop())
    this->acknowledgeStop();
  else
  {
    d->isRunning = false;
    emit finished();
    if (this->isBoundToThread())
      this->thread()->quit();
  }
}

void Task::asynchronousStop()
{
  Q_D(Task);
  //QMutexLocker locker(&d->mutex); Q_UNUSED(locker);
  if (this->isWaitingStop() || !this->isRunning())
    return;
  d->isWaitingStop = true;
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
    qDebug() << "Task::stop():" << this
             << "asynchronous stop failed, task is still running";
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
  d->autoDeleteBoundThread = v;
}

void Task::setLoopCount(int v)
{
  Q_D(Task);
  d->loopCount = v;
}

void Task::setLoopInterval(int msecs)
{
  Q_D(Task);
  d->loopInterval = msecs;
}

void Task::acknowledgeStop()
{
  Q_D(Task);
  //QMutexLocker locker(&d->mutex); Q_UNUSED(locker);
  d->isWaitingStop = false;
  d->isRunning = false;
  emit stopped();
  if (this->isBoundToThread())
    this->thread()->quit();
}

Task::Task(TaskPrivate& dd, QObject* parent) :
  QObject(dd, parent)
{
}

} // namespace qttools

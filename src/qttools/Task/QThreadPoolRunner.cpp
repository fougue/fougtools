#include "QThreadPoolRunner.h"

#include <QtCore/QThreadPool>

namespace Task {

QThreadPoolRunner::QThreadPoolRunner(Runnable *runnable, int priority)
    : BaseRunner(runnable),
      m_isAbortRequested(false),
      m_priority(priority)
{
    this->setAutoDelete(true);
}

QThreadPoolRunner::~QThreadPoolRunner()
{
    delete this->runnable();
}

void QThreadPoolRunner::run()
{
    this->execRunnableFunc();
}

bool QThreadPoolRunner::isAbortRequested()
{ return m_isAbortRequested; }

void QThreadPoolRunner::requestAbort()
{ m_isAbortRequested = true; }

void QThreadPoolRunner::launch()
{ QThreadPool::globalInstance()->start(this, m_priority); }

} // namespace Task

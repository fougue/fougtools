#pragma once

#include "base_runner.h"

#include <QtCore/QRunnable>
#include <QtCore/QThreadPool>

namespace Task {

/*! \brief Task runner using the global instance of QThreadPool
 *
 *  Internally using QThreadPool::globalInstance()->start(...)
 */
template<>
class Runner<QThreadPool> : public QRunnable, public BaseRunner
{
public:
    /*! \param priority Same meaning as the second parameter of
     *                  QThreadPool::start(QRunnable*, int priority)
     */
    Runner<QThreadPool>(const Manager* mgr, int priority = 0)
        : BaseRunner(mgr),
          m_isAbortRequested(false),
          m_priority(priority)
    {
        this->setAutoDelete(false);
    }

    void run() override // -- QRunnable
    { this->execRunnableFunc(); }

    bool isAbortRequested() override
    { return m_isAbortRequested; }

    void requestAbort() override
    { m_isAbortRequested = true; }

    void launch() override
    { QThreadPool::globalInstance()->start(this, m_priority); }

private:
    bool m_isAbortRequested;
    int m_priority;
};

} // namespace Task

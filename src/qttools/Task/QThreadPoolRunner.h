#pragma once

#include "BaseRunner.h"

#include <QtCore/QRunnable>

namespace Task {

/*! \brief Task runner using the global instance of QThreadPool
 *
 *  Internally using QThreadPool::globalInstance()->start(...)
 */
class QThreadPoolRunner : public QRunnable, public BaseRunner
{
public:
    /*! \param priority Same meaning as the second parameter of
     *                  QThreadPool::start(QRunnable*, int priority)
     */
    QThreadPoolRunner(Runnable* runnable, int priority = 0);
    ~QThreadPoolRunner();

    void run() override; // -- QRunnable

    bool isAbortRequested() override;

    void requestAbort() override;

    void launch() override;

private:
    bool m_isAbortRequested;
    int m_priority;
};

} // namespace Task

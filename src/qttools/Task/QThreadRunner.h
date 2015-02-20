#pragma once

#include "BaseRunner.h"

#include <QtCore/QThread>

namespace Task {

/*! \brief Task runner based on QThread
 */
class QThreadRunner : public QThread, public BaseRunner
{
public:
    QThreadRunner(Runnable* runnable,
                  QThread::Priority priority = QThread::InheritPriority);

    bool isAbortRequested() override;
    void requestAbort() override;

    void launch() override;

protected:
    void run() override; // -- QThread

private:
    QThread::Priority m_priority;
};

} // namespace Task

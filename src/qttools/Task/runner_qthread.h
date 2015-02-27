#pragma once

#include "base_runner.h"

#include <QtCore/QThread>
#include <QtCore/QTimer>

namespace qttask {

/*! \brief Task runner based on QThread
 */
template<>
class Runner<QThread> : public QThread, public BaseRunner
{
public:
    Runner<QThread>(const Manager* mgr, QThread::Priority priority = QThread::InheritPriority)
        : QThread(nullptr),
          BaseRunner(mgr),
          m_priority(priority)
    {
    }

protected:
    bool isAbortRequested() override
    { return this->isInterruptionRequested(); }

    void requestAbort() override
    { this->requestInterruption(); }

    void launch() override
    { this->start(m_priority); }

    void destroy() override
    { this->deleteLater(); }

    void run() override // -- QThread
    {
        QTimer::singleShot(0, [=] {
            this->execRunnableFunc();
            this->quit();
        } );

        this->exec();
    }

private:
    QThread::Priority m_priority;
};

} // namespace qttask

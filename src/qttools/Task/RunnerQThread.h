#pragma once

#include "BaseRunner.h"

#include <QtCore/QThread>
#include <QtCore/QTimer>

namespace Task {

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
        QObject::connect(this, &QThread::finished, this, &QObject::deleteLater);
    }

    bool isAbortRequested() override
    { return this->isInterruptionRequested(); }

    void requestAbort() override
    { this->requestInterruption(); }

    void launch() override
    { this->start(m_priority); }

protected:
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

} // namespace Task

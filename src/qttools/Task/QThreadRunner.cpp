#include "QThreadRunner.h"

#include <QtCore/QTimer>

namespace Task {

QThreadRunner::QThreadRunner(const Manager *mgr, QThread::Priority priority)
    : QThread(nullptr),
      BaseRunner(mgr),
      m_priority(priority)
{
    QObject::connect(this, &QThreadRunner::finished, this, &QObject::deleteLater);
}

bool QThreadRunner::isAbortRequested()
{
    return this->isInterruptionRequested();
}

void QThreadRunner::requestAbort()
{
    this->requestInterruption();
}

void QThreadRunner::launch()
{
    this->start(m_priority);
}

void QThreadRunner::run()
{
    QTimer::singleShot(0, [=] {
        this->execRunnableFunc();
        this->quit();
    } );

    this->exec();
}

} // namespace Task

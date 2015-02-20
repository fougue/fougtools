#include "RunnableSignals.h"

#include "Manager.h"

namespace Task {

RunnableSignals::RunnableSignals(Manager *mgr, const Runnable *runnable, QObject *parent)
    : QObject(parent),
      m_runnable(runnable)
{
    QObject::connect(this, &RunnableSignals::started, mgr, &Manager::started);
    QObject::connect(this, &RunnableSignals::progressStep, mgr, &Manager::progressStep);
    QObject::connect(this, &RunnableSignals::progress, mgr, &Manager::progress);
    QObject::connect(this, &RunnableSignals::message, mgr, &Manager::message);
    QObject::connect(this, &RunnableSignals::ended, mgr, &Manager::ended);
}

} // namespace Task

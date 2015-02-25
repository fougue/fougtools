#include "BaseRunner.h"

#include "Manager.h"

namespace Task {

BaseRunner::BaseRunner(const Manager *mgr)
    : m_mgr(mgr),
      m_taskId(0),
      m_signals(this),
      m_progress(this)
{ }

BaseRunner::~BaseRunner()
{ }

quint64 BaseRunner::taskId() const
{
    return m_taskId;
}

const QString &BaseRunner::taskTitle() const
{
    return m_taskTitle;
}

void BaseRunner::setTaskTitle(const QString &title)
{
    m_taskTitle = title;
}

Progress &BaseRunner::progress()
{
    return m_progress;
}

const Progress &BaseRunner::progress() const
{
    return m_progress;
}

void BaseRunner::run(std::function<void()>&& func)
{
    if (func) {
        m_func = func;
        m_signals.emitAboutToRun();
        launch();
    }
}

BaseRunnerSignals *BaseRunner::qtSignals()
{
    return &m_signals;
}

void BaseRunner::execRunnableFunc()
{
    m_signals.emitStarted(m_taskTitle);
    m_func();
    m_signals.emitEnded();
}

bool BaseRunner::isAbortRequested()
{
    return false;
}

void BaseRunner::requestAbort()
{ }

void BaseRunner::launch()
{ }

} // namespace Task

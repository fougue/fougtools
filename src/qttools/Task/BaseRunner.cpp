#include "BaseRunner.h"

namespace Task {

BaseRunner::BaseRunner(Runnable *runnable)
    : m_signals(runnable->m_mgr, runnable),
      m_runnable(runnable)
{ }

BaseRunner::~BaseRunner()
{ }

void BaseRunner::execRunnableFunc()
{
    m_signals.emitStarted(m_runnable->taskId(), m_runnable->m_taskTitle);
    m_runnable->m_func();
    m_signals.emitEnded(m_runnable->taskId());
}

bool BaseRunner::isAbortRequested()
{ return false; }

void BaseRunner::requestAbort()
{ }

void BaseRunner::launch()
{ }

} // namespace Task

#include "CurrentThreadRunner.h"

namespace Task {

CurrentThreadRunner::CurrentThreadRunner(Runnable *runner)
    : BaseRunner(runner),
      m_isAbortRequested(false)
{ }

bool CurrentThreadRunner::isAbortRequested()
{ return m_isAbortRequested; }

void CurrentThreadRunner::requestAbort()
{ m_isAbortRequested = true; }

void CurrentThreadRunner::launch()
{ this->execRunnableFunc(); }

} // namespace Task

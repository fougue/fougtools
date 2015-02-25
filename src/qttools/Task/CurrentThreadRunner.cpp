#include "CurrentThreadRunner.h"

namespace Task {

CurrentThreadRunner::CurrentThreadRunner(const Manager *mgr)
    : BaseRunner(mgr),
      m_isAbortRequested(false)
{ }

bool CurrentThreadRunner::isAbortRequested()
{ return m_isAbortRequested; }

void CurrentThreadRunner::requestAbort()
{ m_isAbortRequested = true; }

void CurrentThreadRunner::launch()
{ this->execRunnableFunc(); }

} // namespace Task

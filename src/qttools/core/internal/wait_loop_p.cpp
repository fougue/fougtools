#include "../wait_loop.h"
#include "wait_loop_p.h"
#include "wait_loop_time_out_stop_condition.h"

namespace qttools {

WaitLoop::Private::Private(WaitLoop *backPtr)
  : m_eventLoop(backPtr),
    m_exitStopCondition(NULL),
    m_backPtr(backPtr)
{
}

void WaitLoop::Private::stopWait()
{
  foreach (WaitLoop::StopCondition* cond, m_stopConditions)
    cond->stopWait();
}

void WaitLoop::Private::endWaitLoop(WaitLoop_StopCondition* endCond)
{
  m_exitStopCondition = endCond;
  this->stopWait();
  if (m_eventLoop.isRunning()) {
    if (endCond == this->timeOutStopCondition())
      m_eventLoop.exit(-1);
    else
      m_eventLoop.quit();
  }
}

internal::WaitLoopTimeOutStopCondition *WaitLoop::Private::timeOutStopCondition() const
{
  if (!m_stopConditions.isEmpty())
    return static_cast<internal::WaitLoopTimeOutStopCondition*>(m_stopConditions.first());
  return NULL;
}

} // namespace qttools

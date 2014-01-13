#include "wait_loop_time_out_stop_condition.h"

#include <QtCore/QTimerEvent>

namespace qttools {
namespace internal {

WaitLoopTimeOutStopCondition::WaitLoopTimeOutStopCondition(QObject* parent)
  : QObject(parent),
    m_interval(-1),
    m_timerId(-1)
{
}

void WaitLoopTimeOutStopCondition::setInterval(int msec)
{
  m_interval = msec;
}

void WaitLoopTimeOutStopCondition::beginWait()
{
  if (m_interval > 0)
    m_timerId = this->startTimer(m_interval);
}

void WaitLoopTimeOutStopCondition::stopWait()
{
  if (m_timerId != -1)
    this->killTimer(m_timerId);
  m_timerId = -1;
}

void WaitLoopTimeOutStopCondition::timerEvent(QTimerEvent* event)
{
  if (event != NULL && event->timerId() == m_timerId)
    this->endWaitLoop();
}

} // namespace internal
} // namespace qttools

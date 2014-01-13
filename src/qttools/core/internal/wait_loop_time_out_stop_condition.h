#ifndef QTTOOLS_WAIT_LOOP_TIME_OUT_STOP_CONDITION_H
#define QTTOOLS_WAIT_LOOP_TIME_OUT_STOP_CONDITION_H

#include "../wait_loop.h"

#include <QtCore/QObject>
class QTimerEvent;

namespace qttools {
namespace internal {

class WaitLoopTimeOutStopCondition : public QObject, public WaitLoop::StopCondition
{
public:
  WaitLoopTimeOutStopCondition(QObject* parent = NULL);

  void setInterval(int msec);

protected:
  void beginWait();
  void stopWait();
  void timerEvent(QTimerEvent* event);

private:
  int m_interval;
  int m_timerId;
};

} // namespace internal
} // namespace qttools

#endif // QTTOOLS_WAIT_LOOP_TIME_OUT_STOP_CONDITION_H

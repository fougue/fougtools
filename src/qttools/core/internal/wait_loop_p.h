#ifndef QTTOOLS_WAIT_LOOP_P_H
#define QTTOOLS_WAIT_LOOP_P_H

#include <QtCore/QEventLoop>
#include <QtCore/QList>

namespace qttools {

class WaitLoop;
class WaitLoop_StopCondition;

namespace internal { class WaitLoopTimeOutStopCondition; }

class WaitLoop::Private
{
public:
  Private(WaitLoop* backPtr);

  void stopWait();
  void endWaitLoop(WaitLoop_StopCondition* endCond);
  internal::WaitLoopTimeOutStopCondition* timeOutStopCondition() const;

  QEventLoop m_eventLoop;
  QList<WaitLoop_StopCondition*> m_stopConditions;
  WaitLoop_StopCondition* m_exitStopCondition;

private:
  WaitLoop* m_backPtr;
};

} // namespace qttools

#endif // QTTOOLS_WAIT_LOOP_P_H

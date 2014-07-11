#include "test_qttools_core.h"

#include "../src/qttools/core/qlocale_tools.h"
#include "../src/qttools/core/wait_loop.h"

#include <QtCore/QtDebug>
#include <QtCore/QTime>

namespace {

class ImmediateStopCondition : public qttools::WaitLoop::StopCondition
{
protected:
  void beginWait()
  {
    this->endWaitLoop();
  }
};

class TimeOutStopCondition : public QObject, public qttools::WaitLoop::StopCondition
{
public:
  TimeOutStopCondition(int interval)
    : m_timerId(-1),
      m_interval(interval)
  { }

protected:
  void beginWait()
  {
    m_timerId = this->startTimer(m_interval);
  }

  void stopWait()
  {
    this->killTimer(m_timerId);
  }

  void timerEvent(QTimerEvent *)
  {
    this->endWaitLoop();
  }

private:
  int m_timerId;
  int m_interval;
};

} // Anonymous namespace

void TestQtToolsCore::WaitLoop_test()
{
  qttools::WaitLoop waitLoop;

  QTime time;
  time.start();

  QVERIFY(!waitLoop.exec(50));
  QVERIFY(!waitLoop.exec(100));
  QVERIFY(time.elapsed() > 148);
  QVERIFY(time.elapsed() < 152);

  ImmediateStopCondition immStopCond;
  waitLoop.addStopCondition(&immStopCond);
  QVERIFY(waitLoop.exec(100));
  QCOMPARE(waitLoop.exitStopCondition(), &immStopCond);
  waitLoop.removeStopCondition(&immStopCond);

  TimeOutStopCondition timeStopCond1(250);
  waitLoop.addStopCondition(&timeStopCond1);
  QVERIFY(waitLoop.exec());
  QCOMPARE(waitLoop.exitStopCondition(), &timeStopCond1);

  TimeOutStopCondition timeStopCond2(200);
  waitLoop.addStopCondition(&timeStopCond2);
  QVERIFY(waitLoop.exec());
  QCOMPARE(waitLoop.exitStopCondition(), &timeStopCond2);

  waitLoop.removeStopCondition(&timeStopCond1);
  waitLoop.removeStopCondition(&timeStopCond2);
}

void TestQtToolsCore::QLocaleTools_test()
{
  QCOMPARE(static_cast<int>(QLocale::France), 74);
  QCOMPARE(qttools::QLocaleTools::toCountry(74), QLocale::France);
//  foreach (auto country, qttools::QLocaleTools::allCountries()) {
//    qDebug() << QLocale::countryToString(country);
//  }
}

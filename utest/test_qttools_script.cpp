#include "test_qttools_script.h"

#include "../src/qttools/script/calculator.h"
#include "../src/mathtools/consts.h"
#include <cmath>

void TestQtToolsScript::Calculator_test()
{
  qttools::Calculator calc;
  QVERIFY(calc.hasResult() && calc.lastErrorText().isEmpty());

  calc.evaluate("2*3");
  QVERIFY(calc.hasResult());
  QCOMPARE(calc.lastResult(), 6.0);

  calc.evaluate("sin(PI/4)");
  QVERIFY(calc.hasResult());
  QCOMPARE(calc.lastResult(), std::sin(math::pi / 4.0));

  calc.evaluate("4*");
  QVERIFY(!calc.hasResult());
  QVERIFY(!calc.lastErrorText().isEmpty());
  //qDebug() << calc.lastErrorText();
}

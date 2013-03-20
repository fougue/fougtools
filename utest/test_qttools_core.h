#ifndef TEST_QTTOOLS_CORE_H
#define TEST_QTTOOLS_CORE_H

#include <QtTest/QTest>

class TestQtToolsCore : public QObject
{
  Q_OBJECT

private slots:
  void WaitLoop_test();
};

#endif // TEST_QTTOOLS_CORE_H

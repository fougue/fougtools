#ifndef TEST_CPPTOOLS_H
#define TEST_CPPTOOLS_H

#include <QtTest/QTest>

class TestCppTools : public QObject
{
  Q_OBJECT

private slots:
  void quantity_test();
  void quantity_benchmark1();
  void quantity_benchmark2();
};

#endif // TEST_CPPTOOLS_H

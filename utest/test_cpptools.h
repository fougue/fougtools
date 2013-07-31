#ifndef TEST_CPPTOOLS_H
#define TEST_CPPTOOLS_H

#include <QtTest/QTest>

class TestCppTools : public QObject
{
  Q_OBJECT

private slots:
  void AbstractFunctor_test();

  void Quantity_test();
  void Quantity_operators_test();
  void Quantity_benchmark1();
  void Quantity_benchmark2();
};

#endif // TEST_CPPTOOLS_H

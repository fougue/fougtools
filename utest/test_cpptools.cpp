#include "test_cpptools.h"

#include "cpptools/quantity.h"
#include <QtCore/QtDebug>

struct LengthTrait {};
typedef cpp::Quantity<cpp::DoubleNumericTraits, LengthTrait> Length;

struct AngleTrait {};
typedef cpp::Quantity<cpp::DoubleNumericTraits, AngleTrait> Angle;

void TestCppTools::quantity_test()
{
  Length length1(1.);
  Length length2(length1 * 5);
  Length length3;
  length3 = length2;
  //qDebug() << length1 << length2;

  QCOMPARE(sizeof(Length), sizeof(double));

}

void TestCppTools::quantity_benchmark1()
{
  QBENCHMARK {
    Length length;
    for (int i = 0; i < 100000000; ++i)
      length = Length(i + length);
    qDebug() << length;
  }
}

void TestCppTools::quantity_benchmark2()
{
  QBENCHMARK {
    double length = 0;
    for (int i = 0; i < 100000000; ++i)
      length = i + length;
    qDebug() << length;
  }
}

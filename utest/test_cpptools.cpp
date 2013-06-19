#include "test_cpptools.h"

#include "../src/cpptools/quantity.h"
#include <QtCore/QtDebug>

struct LengthTrait {};
typedef cpp::Quantity<cpp::DoubleNumericTraits, LengthTrait> Length;
typedef cpp::Quantity<cpp::IntNumericTraits, LengthTrait> Length_i;

struct AngleTrait {};
typedef cpp::Quantity<cpp::DoubleNumericTraits, AngleTrait> Angle;

void TestCppTools::Quantity_test()
{
  Length length1(1.);
  Length length2(length1 * 5);
  Length length3;
  length3 = length2;
  //qDebug() << length1 << length2;

  QCOMPARE(sizeof(Length), sizeof(double));

}

void TestCppTools::Quantity_operators_test()
{
  QCOMPARE((Length_i(5) + Length_i(10)).value(), 15);
  QCOMPARE((Length_i(5) - Length_i(10)).value(), -5);
  QCOMPARE((Length_i(5) * Length_i(10)).value(), 50);
  QCOMPARE((Length_i(10) / Length_i(5)).value(), 2);

  QCOMPARE((2 * Length_i(10)).value(), 20);
  QCOMPARE((Length_i(15) * 2).value(), 30);
  QCOMPARE((2 * Length_i(15) * 2).value(), 60);
  QCOMPARE((2 + Length_i(15)).value(), 17);
  QCOMPARE((2 - Length_i(15)).value(), 13);
}

void TestCppTools::Quantity_benchmark1()
{
//  QBENCHMARK {
//    Length length;
//    for (int i = 0; i < 100000000; ++i)
//      length = Length(i + length);
//    qDebug() << length.value();
//  }
}

void TestCppTools::Quantity_benchmark2()
{
//  QBENCHMARK {
//    double length = 0;
//    for (int i = 0; i < 100000000; ++i)
//      length = i + length;
//    qDebug() << length;
//  }
}

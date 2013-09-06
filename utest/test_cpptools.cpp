#include "test_cpptools.h"

#include "../src/cpptools/functor.h"
#include "../src/cpptools/quantity.h"
#include <QtCore/QScopedPointer>
#include <QtCore/QtDebug>

// --
// -- Functor<> tests
// --

class Foo
{
public:
  virtual int bar()
  { return 1; }

  int constBar() const
  { return 2; }

  int bar1(double v)
  { return qRound(v); }

  int constBar1(double v) const
  { return qRound(v) + 1; }

  int bar2(float v, double w)
  { return qRound(v + w); }

  int constBar2(float v, double w) const
  { return qRound(v + w) + 1; }
};

class FooHeir : public Foo
{
public:
  int bar()
  { return 3; }
};

int func0()
{ return 4; }

int func1(double v)
{ return qRound(v) * 2; }

int func2(float v, double w)
{ return qRound(v + w) * 2; }

void TestCppTools::Functor_test()
{
  Foo foo;
  FooHeir fooHeir;

  // Functor0<>
  cpp::Functor0<int> ftor0 = cpp::Functor0<int>::make(&foo, &Foo::bar);
  QCOMPARE(ftor0(), 1);

  ftor0 = cpp::Functor0<int>::make(&foo, &Foo::constBar);
  QCOMPARE(ftor0(), 2);

  ftor0 = cpp::Functor0<int>::make(&fooHeir, &Foo::bar);
  QCOMPARE(ftor0(), 3);

  ftor0 = cpp::Functor0<int>::make(&func0);
  QCOMPARE(ftor0(), 4);

  ftor0 = cpp::Functor0<int>::make(&func1, 5.);
  QCOMPARE(ftor0(), 5 * 2);
  ftor0 = cpp::Functor0<int>::make(&func2, 5.1, 7.2);
  QCOMPARE(ftor0(), (5 + 7) * 2);

  ftor0 = cpp::Functor0<int>::make(&foo, &Foo::bar1, 5.2);
  QCOMPARE(ftor0(), 5);
  ftor0 = cpp::Functor0<int>::make(&foo, &Foo::constBar1, 5.3);
  QCOMPARE(ftor0(), 6);

  ftor0 = cpp::Functor0<int>::make(&foo, &Foo::bar2, 5.1, 7.2);
  QCOMPARE(ftor0(), 5 + 7);
  ftor0 = cpp::Functor0<int>::make(&foo, &Foo::constBar2, 5.1, 7.2);
  QCOMPARE(ftor0(), 5 + 7 + 1);

  // Functor1<>
  cpp::Functor1<int, double> ftor1 = cpp::Functor1<int, double>::make(&foo, &Foo::bar1);
  QCOMPARE(ftor1(5.1), 5);

  ftor1 = cpp::Functor1<int, double>::make(&foo, &Foo::constBar1);
  QCOMPARE(ftor1(5.1), 5 + 1);

  ftor1 = cpp::Functor1<int, double>::make(&func1);
  QCOMPARE(ftor1(7.2), 7 * 2);

  // Functor2<>
  cpp::Functor2<int, float, double> ftor2 = cpp::Functor2<int, float, double>::make(&foo, &Foo::bar2);
  QCOMPARE(ftor2(5.1, 7.2), 5 + 7);

  ftor2 = cpp::Functor2<int, float, double>::make(&foo, &Foo::constBar2);
  QCOMPARE(ftor2(5.1, 7.2), 5 + 7 + 1);

  ftor2 = cpp::Functor2<int, float, double>::make(&func2);
  QCOMPARE(ftor2(5.1, 7.2), (5 + 7) * 2);
}


// --
// -- Quantity tests
// --

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

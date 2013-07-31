#include "test_cpptools.h"

#include "../src/cpptools/new_functor.h"
#include "../src/cpptools/quantity.h"
#include <QtCore/QScopedPointer>
#include <QtCore/QtDebug>

// --
// -- AbstractFunctor<> tests
// --

int function0()
{
  return 0;
}

int function1(double arg)
{
  return qRound(arg);
}

class Foo
{
public:
  const char* memberFunction0()
  { return "0"; }

  const char* constMemberFunction0() const
  { return "const0"; }

  const char* memberFunction1(int /*v*/)
  { return "1"; }

  const char* constMemberFunction1(int /*v*/) const
  { return "const1"; }
};

void TestCppTools::AbstractFunctor_test()
{
  // Functions
  typedef cpp::AbstractFunctor<int> IntFunctor;

  QScopedPointer<IntFunctor> func0(cpp::newFunctor(&function0));
  QCOMPARE(func0->execute(), 0);

  QScopedPointer<IntFunctor> func1(cpp::newFunctor(&function1, 1.2));
  QCOMPARE(func1->execute(), 1);

  // Member functions
  typedef cpp::AbstractFunctor<const char*> ConstCStringFunctor;
  Foo foo;
  QScopedPointer<ConstCStringFunctor> mbFunc0(cpp::newFunctor(foo, &Foo::memberFunction0));
  QCOMPARE(mbFunc0->execute(), "0");
  QScopedPointer<ConstCStringFunctor> mbFuncPtr0(cpp::newFunctor(&foo, &Foo::memberFunction0));
  QCOMPARE(mbFuncPtr0->execute(), "0");

  QScopedPointer<ConstCStringFunctor> constMbFunc0(cpp::newFunctor(foo, &Foo::constMemberFunction0));
  QCOMPARE(constMbFunc0->execute(), "const0");
  QScopedPointer<ConstCStringFunctor> constMbFuncPtr0(cpp::newFunctor(&foo, &Foo::constMemberFunction0));
  QCOMPARE(constMbFuncPtr0->execute(), "const0");

  QScopedPointer<ConstCStringFunctor> mbFunc1(cpp::newFunctor(foo, &Foo::memberFunction1, 5));
  QCOMPARE(mbFunc1->execute(), "1");
  QScopedPointer<ConstCStringFunctor> mbFuncPtr1(cpp::newFunctor(&foo, &Foo::memberFunction1, 5));
  QCOMPARE(mbFuncPtr1->execute(), "1");

  QScopedPointer<ConstCStringFunctor> constMbFunc1(cpp::newFunctor(foo, &Foo::constMemberFunction1, 10));
  QCOMPARE(constMbFunc1->execute(), "const1");
  QScopedPointer<ConstCStringFunctor> constMbFuncPtr1(cpp::newFunctor(&foo, &Foo::constMemberFunction1, 10));
  QCOMPARE(constMbFuncPtr1->execute(), "const1");
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

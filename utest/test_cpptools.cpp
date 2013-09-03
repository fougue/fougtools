#include "test_cpptools.h"

#include "../src/cpptools/new_functor.h"
#include "../src/cpptools/new_functor1.h"
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

int function2(double arg1, const int* arg2)
{
  return qRound(arg1) + (arg2 != NULL ? *arg2 : 0);
}

class Foo
{
public:
  QString memberFunction0()
  { return "0"; }

  QString constMemberFunction0() const
  { return "const0"; }

  QString memberFunction1(int v)
  { return QString("1_%1").arg(v); }

  QString constMemberFunction1(int v) const
  { return QString("const1_%1").arg(v); }

  QString memberFunction2(int v, const int* ptr)
  { return QString("2_%1_%2").arg(v).arg(ptr != NULL ? *ptr : 0); }

  QString constMemberFunction2(int v, const int* ptr) const
  { return QString("const2_%1_%2").arg(v).arg(ptr != NULL ? *ptr : 0); }

};

void TestCppTools::AbstractFunctor_test()
{
  // AbstractFunctor<>
  {
    // Functions
    typedef cpp::AbstractFunctor0<int> IntFunctor;

    QScopedPointer<IntFunctor> func0(cpp::newFunctor0(&function0));
    QCOMPARE(func0->execute(), 0);

    QScopedPointer<IntFunctor> func1(cpp::newFunctor0(&function1, 1.2));
    QCOMPARE(func1->execute(), 1);

    // Member functions
    typedef cpp::AbstractFunctor0<QString> QStringFunctor;
    Foo foo;
    QScopedPointer<QStringFunctor> mbFunc0(cpp::newFunctor0(foo, &Foo::memberFunction0));
    QCOMPARE(mbFunc0->execute(), QString("0"));
    QScopedPointer<QStringFunctor> mbFuncPtr0(cpp::newFunctor0(&foo, &Foo::memberFunction0));
    QCOMPARE(mbFuncPtr0->execute(), QString("0"));

    QScopedPointer<QStringFunctor> constMbFunc0(cpp::newFunctor0(foo, &Foo::constMemberFunction0));
    QCOMPARE(constMbFunc0->execute(), QString("const0"));
    QScopedPointer<QStringFunctor> constMbFuncPtr0(cpp::newFunctor0(&foo, &Foo::constMemberFunction0));
    QCOMPARE(constMbFuncPtr0->execute(), QString("const0"));

    QScopedPointer<QStringFunctor> mbFunc1(cpp::newFunctor0(foo, &Foo::memberFunction1, 5));
    QCOMPARE(mbFunc1->execute(), QString("1_5"));
    QScopedPointer<QStringFunctor> mbFuncPtr1(cpp::newFunctor0(&foo, &Foo::memberFunction1, 5));
    QCOMPARE(mbFuncPtr1->execute(), QString("1_5"));

    QScopedPointer<QStringFunctor> constMbFunc1(cpp::newFunctor0(foo, &Foo::constMemberFunction1, 10));
    QCOMPARE(constMbFunc1->execute(), QString("const1_10"));
    QScopedPointer<QStringFunctor> constMbFuncPtr1(cpp::newFunctor0(&foo, &Foo::constMemberFunction1, 10));
    QCOMPARE(constMbFuncPtr1->execute(), QString("const1_10"));

    const int intVal = 7;
    QScopedPointer<QStringFunctor> mbFunc2(cpp::newFunctor0(foo, &Foo::memberFunction2, 5, &intVal));
    QCOMPARE(mbFunc2->execute(), QString("2_5_%1").arg(intVal));
    QScopedPointer<QStringFunctor> mbFuncPtr2(cpp::newFunctor0(&foo, &Foo::memberFunction2, 5, &intVal));
    QCOMPARE(mbFuncPtr2->execute(), QString("2_5_%1").arg(intVal));

    QScopedPointer<QStringFunctor> constMbFunc2(cpp::newFunctor0(foo, &Foo::constMemberFunction2, 10, &intVal));
    QCOMPARE(constMbFunc2->execute(), QString("const2_10_%1").arg(intVal));
    QScopedPointer<QStringFunctor> constMbFuncPtr2(cpp::newFunctor0(&foo, &Foo::constMemberFunction2, 10, &intVal));
    QCOMPARE(constMbFuncPtr2->execute(), QString("const2_10_%1").arg(intVal));
  }


  // AbstractFunctor1<>
  {
    // Functions
    typedef cpp::AbstractFunctor1<int, double> IntFunctor1;

    QScopedPointer<IntFunctor1> func1(cpp::newFunctor1(&function1));
    QCOMPARE(func1->execute(1.2), 1);

    // Member functions
    typedef cpp::AbstractFunctor1<QString, int> QStringFunctor1;
    Foo foo;

    QScopedPointer<QStringFunctor1> mbFunc1(cpp::newFunctor1(foo, &Foo::memberFunction1));
    QCOMPARE(mbFunc1->execute(5), QString("1_5"));
    QScopedPointer<QStringFunctor1> mbFuncPtr1(cpp::newFunctor1(&foo, &Foo::memberFunction1));
    QCOMPARE(mbFuncPtr1->execute(5), QString("1_5"));

    QScopedPointer<QStringFunctor1> constMbFunc1(cpp::newFunctor1(foo, &Foo::constMemberFunction1));
    QCOMPARE(constMbFunc1->execute(10), QString("const1_10"));
    QScopedPointer<QStringFunctor1> constMbFuncPtr1(cpp::newFunctor1(&foo, &Foo::constMemberFunction1));
    QCOMPARE(constMbFuncPtr1->execute(10), QString("const1_10"));
  }


  // AbstractFunctor2<>
  {
    // Functions
    typedef cpp::AbstractFunctor2<int, double, const int*> IntFunctor2;

    const int intVal = 7;
    QScopedPointer<IntFunctor2> func2(cpp::newFunctor2(&function2));
    QCOMPARE(func2->execute(1.2, &intVal), 1 + intVal);
    QCOMPARE(func2->execute(1.2, NULL), 1);

    // Member functions
    typedef cpp::AbstractFunctor2<QString, int, const int*> QStringFunctor2;
    Foo foo;

    QScopedPointer<QStringFunctor2> mbFunc2(cpp::newFunctor2(foo, &Foo::memberFunction2));
    QCOMPARE(mbFunc2->execute(5, &intVal), QString("2_5_%1").arg(intVal));
    QScopedPointer<QStringFunctor2> mbFuncPtr2(cpp::newFunctor2(&foo, &Foo::memberFunction2));
    QCOMPARE(mbFuncPtr2->execute(5, &intVal), QString("2_5_%1").arg(intVal));

    QScopedPointer<QStringFunctor2> constMbFunc2(cpp::newFunctor2(foo, &Foo::constMemberFunction2));
    QCOMPARE(constMbFunc2->execute(10, &intVal), QString("const2_10_%1").arg(intVal));
    QScopedPointer<QStringFunctor2> constMbFuncPtr2(cpp::newFunctor2(&foo, &Foo::constMemberFunction2));
    QCOMPARE(constMbFuncPtr2->execute(10, &intVal), QString("const2_10_%1").arg(intVal));
  }
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

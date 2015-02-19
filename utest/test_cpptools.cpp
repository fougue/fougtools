#include "test_cpptools.h"

#include "../src/cpptools/c_array_utils.h"
#include "../src/cpptools/circular_iterator.h"
#include "../src/cpptools/memory_utils.h"
#include "../src/cpptools/scoped_value.h"
#include "../src/cpptools/basic_shared_pointer.h"
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

struct DeleteHook
{
    DeleteHook(int valOnDelete, int* spyInt)
        : m_spyInt(spyInt),
          m_valOnDelete(valOnDelete)
    { }

    ~DeleteHook()
    { *m_spyInt = m_valOnDelete; }

private:
    int* m_spyInt;
    const int m_valOnDelete;
};

void TestCppTools::BasicSharedPointer_test()
{
    int spyHint = 0;
    {
        DeleteHook* delHook = new DeleteHook(-1, &spyHint);
        cpp::BasicSharedPointer<DeleteHook> sharedPtr(delHook);
    }
    QCOMPARE(spyHint, -1);

    spyHint = 0;
    {
        DeleteHook* delHook = new DeleteHook(-1, &spyHint);
        cpp::BasicSharedPointer<DeleteHook> sharedPtr(delHook);
        QCOMPARE(sharedPtr.data(), delHook);

        cpp::BasicSharedPointer<DeleteHook> sharedPtr1;
        QVERIFY(sharedPtr1.isNull());
        sharedPtr1 = sharedPtr;
        QCOMPARE(sharedPtr1.data(), delHook);
    }
    QCOMPARE(spyHint, -1);
}

void TestCppTools::cArrayUtils_test()
{
    int array1[1];
    int array5[5];
    QCOMPARE(cpp::cArraySize(array1), static_cast<size_t>(1));
    QCOMPARE(cpp::cArraySize(array5), static_cast<size_t>(5));

    QCOMPARE(cpp::cArrayEnd(array1), array1 + 1);
    QCOMPARE(cpp::cArrayEnd(array5), array5 + 5);
}

void TestCppTools::ScopedValue_test()
{
    bool b = true;
    {
        cpp::ScopedBool sb(b, true); Q_UNUSED(sb);
        QCOMPARE(b, true);
    }
    QCOMPARE(b, true);
    b = true;
    {
        cpp::ScopedBool sb(b, false); Q_UNUSED(sb);
        QCOMPARE(b, false);
    }
    QCOMPARE(b, true);

    b = false;
    {
        cpp::ScopedBool sb(b, true); Q_UNUSED(sb);
        QCOMPARE(b, true);
    }
    QCOMPARE(b, false);
    b = false;
    {
        cpp::ScopedBool sb(b, false); Q_UNUSED(sb);
        QCOMPARE(b, false);
    }
    QCOMPARE(b, false);
}

void TestCppTools::circularIterator_test()
{
    QCOMPARE(cpp::circularNext(0, 5, 1), 2);
    QCOMPARE(cpp::circularNext(0, 5, 0), 1);
    QCOMPARE(cpp::circularNext(0, 5, 4), 0);
    QCOMPARE(cpp::circularNext(0, 1, 0), 0);

    QCOMPARE(cpp::circularPrior(0, 5, 1), 0);
    QCOMPARE(cpp::circularPrior(0, 5, 0), 4);
    QCOMPARE(cpp::circularPrior(0, 5, 4), 3);
    QCOMPARE(cpp::circularPrior(0, 1, 0), 0);

    QCOMPARE(cpp::circularAdvance(0, 5, 1, -1), cpp::circularPrior(0, 5, 1));
    QCOMPARE(cpp::circularAdvance(0, 5, 0, -1), cpp::circularPrior(0, 5, 0));
    QCOMPARE(cpp::circularAdvance(0, 5, 4, -1), cpp::circularPrior(0, 5, 4));
    QCOMPARE(cpp::circularAdvance(0, 1, 0, -1), cpp::circularPrior(0, 1, 0));

    QCOMPARE(cpp::circularAdvance(0, 5, 1, 1), cpp::circularNext(0, 5, 1));
    QCOMPARE(cpp::circularAdvance(0, 5, 0, 1), cpp::circularNext(0, 5, 0));
    QCOMPARE(cpp::circularAdvance(0, 5, 4, 1), cpp::circularNext(0, 5, 4));
    QCOMPARE(cpp::circularAdvance(0, 1, 0, 1), cpp::circularNext(0, 1, 0));

    QCOMPARE(cpp::circularAdvance(0, 5, 0, 3), 3);
    QCOMPARE(cpp::circularAdvance(0, 5, 0, -3), 2);
    QCOMPARE(cpp::circularAdvance(0, 5, 0, 6), 1);
}

namespace memoryUtils_test {

struct DummyObserver
{
    bool isDummyDeleted;
}; // struct DummyObserver

struct Dummy
{
    Dummy(DummyObserver* obs) :
        m_a(0),
        m_b(0),
        m_observer(obs)
    {
        obs->isDummyDeleted = false;
    }

    ~Dummy()
    {
        m_observer->isDummyDeleted = true;
    }

    int m_a;
    double m_b;
    DummyObserver* m_observer;
};

} // namespace memoryUtils_test

void TestCppTools::memoryUtils_test()
{
    memoryUtils_test::DummyObserver observer;
    memoryUtils_test::Dummy* dummy = new memoryUtils_test::Dummy(&observer);
    const bool oldIsDeletedTag = observer.isDummyDeleted;
    cpp::checkedReset(dummy);
    QVERIFY(!oldIsDeletedTag);
    QVERIFY(dummy == NULL);
    QVERIFY(observer.isDummyDeleted);
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

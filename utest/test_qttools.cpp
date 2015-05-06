#include "test_qttools.h"

#include "../src/qttools/core/qlocale_utils.h"
#include "../src/qttools/core/qobject_wrap.h"
#include "../src/qttools/core/qstring_hfunc.h"
#include "../src/qttools/gui/qstandard_item_explorer.h"
#include "../src/qttools/script/calculator.h"

#ifdef FOUGTOOLS_HAVE_QTTOOLS_TASK
# include "../src/qttools/task/runner_current_thread.h"
# include "../src/qttools/task/runner_qthreadpool.h"
# include "../src/qttools/task/runner_stdasync.h"
# include "../src/qttools/task/manager.h"
#endif // FOUGTOOLS_HAVE_QTTOOLS_TASK

#include "../src/mathtools/consts.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

#include <cmath>
#include <unordered_map>

void TestQtTools::core_QLocaleUtils_test()
{
    QCOMPARE(static_cast<int>(QLocale::France), 74);
    QCOMPARE(qtcore::QLocaleUtils::toCountry(74), QLocale::France);
    //  foreach (auto country, qttools::QLocaleTools::allCountries()) {
    //    qDebug() << QLocale::countryToString(country);
    //  }
}

void TestQtTools::core_QStringHFunc_test()
{
    std::unordered_map<QString, int> map;
    map.emplace(QString::fromLatin1("test1"), 1);
    map.emplace(QString::fromLatin1("test2"), 2);
    QCOMPARE(map.at(QString::fromLatin1("test1")), 1);
    QCOMPARE(map.at(QString::fromLatin1("test2")), 2);
}

void TestQtTools::core_QObjectWrap_test()
{
    const int a = 50;
    auto wrap1 = qtcore::wrapAsQObject(a);
    QCOMPARE(wrap1->value(), a);
    delete wrap1;

    const QLatin1String str("core_QObjectWrap_test()");
    const QString qstr = str;
    auto wrap2 = qtcore::wrapAsQObject(std::move(qstr));
    QCOMPARE(wrap2->value(), QString(str));
    delete wrap2;
}

void TestQtTools::gui_QStandardItemExplorer_test()
{
    QStandardItemModel itemModel;

    auto rootItem = new QStandardItem(QLatin1String("root"));
    itemModel.appendRow(rootItem);

    auto item1 = new QStandardItem(QLatin1String("item_1"));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_1")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_2")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_3")));
    item1->appendRow(new QStandardItem(QLatin1String("item_1_4")));

    auto item2 = new QStandardItem(QLatin1String("item_2"));

    rootItem->appendRow(item1);
    rootItem->appendRow(item2);

    qtgui::QStandardItemExplorer explorer(&itemModel);
    QCOMPARE(explorer.current(), itemModel.invisibleRootItem());
    explorer.goNext();
    QCOMPARE(explorer.current(), rootItem);
    explorer.goNext();
    QCOMPARE(explorer.current(), item1);
    explorer.goNext();
    QCOMPARE(explorer.current(), item2);
    explorer.goNext();
    for (int i = 0; i < item1->rowCount(); ++i) {
        QCOMPARE(explorer.current(), item1->child(i));
        explorer.goNext();
    }
    QCOMPARE(explorer.atEnd(), true);
}

void TestQtTools::script_Calculator_test()
{
    qtscript::Calculator calc;
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

#ifdef FOUGTOOLS_HAVE_QTTOOLS_TASK

namespace Internal {

static const bool debugOutput = true;

template<typename SELECTOR, typename ... ARGS>
static qttask::BaseRunner* newTaskRunner(
        qttask::Manager* mgr, const char* selectorName, ARGS ... args)
{
    auto runner = mgr->newTask<SELECTOR>(args ...);
    runner->setTaskTitle(QString("Tâche [%1] %2").arg(selectorName).arg(runner->taskId()));
    return runner;
}

} // namespace Internal

void TestQtTools::task_Manager_test()
{
    auto taskMgr = qttask::Manager::globalInstance();
    QObject::connect(taskMgr, &qttask::Manager::started,
                     [](quint64 taskId, const QString& title) {
        if (Internal::debugOutput)
            qDebug() << "Started:" << taskId << title;
    } );

    QObject::connect(taskMgr, &qttask::Manager::progressStep,
                     [](quint64 taskId, const QString& title) {
        if (Internal::debugOutput)
            qDebug() << "Step:" << taskId << title;
    } );

    QObject::connect(taskMgr, &qttask::Manager::message,
                     [](quint64 taskId, const QString& msg) {
        if (Internal::debugOutput)
            qDebug() << "Message:" << taskId << msg;
    } );

    std::vector<qttask::BaseRunner*> taskVec;
    for (int i = 0; i < 5; ++i) {
        taskVec.push_back(Internal::newTaskRunner<QThreadPool>(taskMgr, "QThreadPool"));
        taskVec.push_back(Internal::newTaskRunner<QThread>(taskMgr, "QThread", QThread::HighestPriority));
        taskVec.push_back(Internal::newTaskRunner<qttask::StdAsync>(taskMgr, "std::async()"));
        taskVec.push_back(Internal::newTaskRunner<qttask::CurrentThread>(taskMgr, "CurrentThread"));
    }

    std::size_t taskCount = taskVec.size();
    std::unordered_map<quint64, bool> taskWorkDone;
    for (const auto task : taskVec)
        taskWorkDone.emplace(task->taskId(), false);

    QObject::connect(taskMgr, &qttask::Manager::ended,
                     [&](quint64 taskId) {
        --taskCount;

        auto it = taskWorkDone.find(taskId);
        if (it != taskWorkDone.cend())
            (*it).second = true;

        if (Internal::debugOutput)
            qDebug() << "Ended:" << taskId << taskMgr->taskTitle(taskId);

        QVERIFY(taskMgr->taskProgress(taskId) != nullptr);
    } );

    for (auto task : taskVec)
        task->run( [=] {
            task->progress().outputMessage(QString("-- Function %1 --")
                                           .arg(task->taskId()));
        } );

    QTime chrono;
    chrono.start();
    while (taskCount > 0 && chrono.elapsed() < 5000)
        QCoreApplication::processEvents();
    QCOMPARE(taskCount, static_cast<std::size_t>(0));
    QCOMPARE(taskWorkDone.size(), taskVec.size());
    for (const auto& mapPair : taskWorkDone) {
        QVERIFY(mapPair.second);
        QCOMPARE(taskMgr->taskProgress(mapPair.first), static_cast<qttask::Progress*>(nullptr));
    }
}
#endif // FOUGTOOLS_HAVE_QTTOOLS_TASK

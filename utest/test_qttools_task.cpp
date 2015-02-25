#include "test_qttools_task.h"

#include "../src/qttools/Task/RunnerCurrentThread.h"
#include "../src/qttools/Task/RunnerQThreadPool.h"
#include "../src/qttools/Task/RunnerStdAsync.h"
#include "../src/qttools/Task/Manager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>
#include <QtCore/QTime>
#include <QtCore/QTimer>

#include <unordered_map>

namespace Internal {

static const bool debugOutput = true;

template<typename SELECTOR, typename ... ARGS>
static Task::BaseRunner* newTaskRunner(
        Task::Manager* mgr, const char* selectorName, ARGS ... args)
{
    auto runner = mgr->newTask<SELECTOR>(args ...);
    runner->setTaskTitle(QString("Tâche [%1] %2").arg(selectorName).arg(runner->taskId()));
    return runner;
}

} // namespace Internal

void TestQtToolsTask::Manager_test()
{
    auto taskMgr = Task::Manager::globalInstance();
    QObject::connect(taskMgr, &Task::Manager::started,
                     [](quint64 taskId, const QString& title) {
        if (Internal::debugOutput)
            qDebug() << "Started:" << taskId << title;
    } );

    QObject::connect(taskMgr, &Task::Manager::progressStep,
                     [](quint64 taskId, const QString& title) {
        if (Internal::debugOutput)
            qDebug() << "Step:" << taskId << title;
    } );

    QObject::connect(taskMgr, &Task::Manager::message,
                     [](quint64 taskId, const QString& msg) {
        if (Internal::debugOutput)
            qDebug() << "Message:" << taskId << msg;
    } );

    std::vector<Task::BaseRunner*> taskVec;
    for (int i = 0; i < 5; ++i) {
        taskVec.push_back(Internal::newTaskRunner<QThreadPool>(taskMgr, "QThreadPool"));
        taskVec.push_back(Internal::newTaskRunner<QThread>(taskMgr, "QThread", QThread::HighestPriority));
        taskVec.push_back(Internal::newTaskRunner<Task::StdAsync>(taskMgr, "std::async()"));
        taskVec.push_back(Internal::newTaskRunner<Task::CurrentThread>(taskMgr, "CurrentThread"));
    }

    std::size_t taskCount = taskVec.size();
    std::unordered_map<quint64, bool> taskWorkDone;
    for (const auto task : taskVec)
        taskWorkDone.emplace(task->taskId(), false);

    QObject::connect(taskMgr, &Task::Manager::ended,
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
        QCOMPARE(taskMgr->taskProgress(mapPair.first), static_cast<Task::Progress*>(nullptr));
    }
}

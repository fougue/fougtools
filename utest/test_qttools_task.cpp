#include "test_qttools_task.h"

#include "../src/qttools/Task/CurrentThreadRunner.h"
#include "../src/qttools/Task/QThreadPoolRunner.h"
#include "../src/qttools/Task/StdAsyncRunner.h"
#include "../src/qttools/Task/Manager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>
#include <QtCore/QTime>
#include <QtCore/QTimer>

#include <unordered_map>

namespace Internal {
static const bool debugOutput = true;
} // namespace Internal

void TestQtToolsTask::Manager_test()
{
    Task::Manager taskMgr;
    QObject::connect(&taskMgr, &Task::Manager::started,
                     [](quint64 taskId, const QString& title) {
        if (Internal::debugOutput)
            qDebug() << "Started:" << taskId << title;
    } );

    QObject::connect(&taskMgr, &Task::Manager::progressStep,
                     [](quint64 taskId, const QString& title) {
        if (Internal::debugOutput)
            qDebug() << "Step:" << taskId << title;
    } );

    QObject::connect(&taskMgr, &Task::Manager::message,
                     [](quint64 taskId, const QString& msg) {
        if (Internal::debugOutput)
            qDebug() << "Message:" << taskId << msg;
    } );

    std::vector<Task::BaseRunner*> taskVec;
    for (int i = 0; i < 10; ++i) {
        const auto isPair = i % 2 == 0;
//        taskVec.push_back(
//                    isPair ? taskMgr.newTask<Task::QThreadPoolRunner>() :
//                             taskMgr.newTask<Task::QThreadRunner>(QThread::HighestPriority));
//        taskVec.back()->setTaskTitle(
//                    QString(isPair ? "Tâche [QThreadPool] %1" : "Tâche [QThread] %1").arg(i));
        taskVec.push_back(taskMgr.newTask<Task::StdAsyncRunner>());
//        taskVec.push_back(taskMgr.newTask<Task::CurrentThreadRunner>());
        taskVec.back()->setTaskTitle(QString("Tâche %1").arg(taskVec.back()->taskId()));
    }

    std::size_t taskCount = taskVec.size();
    std::unordered_map<quint64, bool> taskWorkDone;
    for (const auto task : taskVec)
        taskWorkDone.emplace(task->taskId(), false);

    QObject::connect(&taskMgr, &Task::Manager::ended,
                     [&](quint64 taskId) {
        --taskCount;

        auto it = taskWorkDone.find(taskId);
        if (it != taskWorkDone.cend())
            (*it).second = true;

        if (Internal::debugOutput)
            qDebug() << "Ended:" << taskId << " taskCount=" << taskCount;
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
    }
}

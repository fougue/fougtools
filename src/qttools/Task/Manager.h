#pragma once

#include "QThreadRunner.h"

#include <QtCore/QObject>

#include <unordered_map>

namespace Task {

class BaseRunner;
class Progress;

/*! \brief Central class providing management of tasks and notifications
 */
class Manager : public QObject
{
    Q_OBJECT

public:
    Manager(QObject* parent = nullptr);
    ~Manager();

    /*! \brief Create a ready-to-launch Runnable object
     *
     *  The created Runnable will be automatically deleted at the end of execution.
     *  TODO: make this function reentrant
     */
    template<typename RUNNER = QThreadRunner, typename ... ARGS>
    BaseRunner* newTask(ARGS ... args)
    {
        auto runner = new RUNNER(this, args ...);
        runner->m_taskId = ++m_taskIdSeq;
        return runner;
    }

    const Progress* taskProgress(quint64 taskId) const;

    void requestAbort(quint64 taskId);

signals:
    void started(quint64 taskId, const QString& title);
    void progressStep(quint64 taskId, const QString& title);
    void progress(quint64 taskId, int percent);
    void message(quint64 taskId, const QString& msg);
    void ended(quint64 taskId);

private:
    friend class RunnerSignals;

    void onAboutToRun(BaseRunner* runner);

    quint64 m_taskIdSeq;
    std::unordered_map<quint64, Progress*> m_taskIdToProgress;
};

} // namespace Task

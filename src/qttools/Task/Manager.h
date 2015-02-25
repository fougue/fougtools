#pragma once

#include "RunnerQThread.h"

#include <QtCore/QObject>

#include <atomic>
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

    /*! \brief Create a ready-to-launch Runner object
     *
     *  The created Runner will be automatically deleted at the end of execution.
     */
    template<typename SELECTOR = QThread, typename ... ARGS>
    Runner<SELECTOR>* newTask(ARGS ... args)
    {
        auto runner = new Runner<SELECTOR>(this, args ...);
        runner->m_taskId = m_taskIdSeq.fetch_add(1);
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
    friend class BaseRunnerSignals;

    void onAboutToRun(BaseRunner* runner);

    std::atomic<quint64> m_taskIdSeq;
    std::unordered_map<quint64, Progress*> m_taskIdToProgress;
};

} // namespace Task

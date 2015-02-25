#pragma once

#include "Progress.h"
#include "RunnerSignals.h"

#include <functional>

namespace Task {

class Manager;

/*! \brief Base class for all runner objects
 *
 *  BaseRunner provides control over a Runnable object : start/abort
 */
class BaseRunner
{
public:
    virtual ~BaseRunner();

    quint64 taskId() const;

    const QString& taskTitle() const;
    void setTaskTitle(const QString& title);

    Progress& progress();
    const Progress& progress() const;

    void run(std::function<void()>&& func);

protected:
    BaseRunner(const Manager* mgr);

    inline RunnerSignals* taskSignals()
    { return &m_signals; }

    void execRunnableFunc();

    virtual bool isAbortRequested();
    virtual void requestAbort();
    virtual void launch();

private:
    friend class Runnable;
    friend class RunnerSignals;
    friend class Manager;
    friend class Progress;

    const Manager* m_mgr;
    quint64 m_taskId;
    QString m_taskTitle;
    std::function<void()> m_func;

    RunnerSignals m_signals;
    Progress m_progress;
};

} // namespace Task

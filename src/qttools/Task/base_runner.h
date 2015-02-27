#pragma once

#include "progress.h"
#include "base_runner_signals.h"

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

    BaseRunnerSignals* qtSignals();

    void execRunnableFunc();

    virtual bool isAbortRequested();
    virtual void requestAbort();
    virtual void launch();
    virtual void destroy();

private:
    friend class BaseRunnerSignals;
    friend class Manager;
    friend class Progress;

    const Manager* m_mgr;
    quint64 m_taskId;
    QString m_taskTitle;
    std::function<void()> m_func;

    BaseRunnerSignals m_signals;
    Progress m_progress;
};

template<typename SELECTOR>
class Runner : public BaseRunner
{ };

} // namespace Task

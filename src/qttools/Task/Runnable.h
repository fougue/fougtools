#pragma once

#include "Progress.h"

#include <functional>

namespace Task {

class BaseRunner;
class Manager;

/*! \brief Provides an interface for running some piece of code (task)
 *
 *  Internally, execution is achieved through a BaseRunner object
 */
class Runnable
{
public:
    ~Runnable();

    quint64 taskId() const;

    const QString& taskTitle() const;
    void setTaskTitle(const QString& title);

    Progress* progress();
    const Progress* progress() const;

    void run(std::function<void()>&& func);

private:
    Runnable(Manager* mgr, quint64 taskId);

    friend class Manager;
    friend class Progress;
    friend class BaseRunner;

    Manager* m_mgr;
    quint64 m_taskId;
    QString m_taskTitle;
    BaseRunner* m_taskRunner;
    std::function<void()> m_func;
    Progress m_progress;
};

} // namespace Task

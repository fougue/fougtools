#include "Runnable.h"

#include "BaseRunner.h"
#include "Manager.h"

namespace Task {

Runnable::~Runnable()
{
    delete m_taskRunner;
}

quint64 Runnable::taskId() const
{
    return m_taskId;
}

const QString &Runnable::taskTitle() const
{
    return m_taskTitle;
}

void Runnable::setTaskTitle(const QString &title)
{
    m_taskTitle = title;
}

Progress *Runnable::progress()
{
    return &m_progress;
}

const Progress *Runnable::progress() const
{
    return &m_progress;
}

void Runnable::run(std::function<void()>&& func)
{
    m_func = func;
    if (func && m_taskRunner != nullptr) {
        m_mgr->m_taskIdToProgress.emplace(m_taskId, &m_progress);
        m_taskRunner->launch();
    }
}

Runnable::Runnable(Manager *mgr, quint64 taskId)
    : m_mgr(mgr),
      m_taskId(taskId),
      m_taskRunner(nullptr),
      m_progress(this)
{
}

} // namespace Task

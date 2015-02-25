#include "Manager.h"

#include "BaseRunner.h"

namespace Task {

Manager::Manager(QObject *parent)
    : QObject(parent),
      m_taskIdSeq(0)
{
    QObject::connect(this, &Manager::ended,
                     [=](quint64 taskId) { m_taskIdToProgress.erase(taskId); } );
}

Manager::~Manager()
{ }

const Progress *Manager::taskProgress(quint64 taskId) const
{
    auto it = m_taskIdToProgress.find(taskId);
    return it != m_taskIdToProgress.end() ? (*it).second : nullptr;
}

void Manager::requestAbort(quint64 taskId)
{
    auto it = m_taskIdToProgress.find(taskId);
    if (it != m_taskIdToProgress.end())
        (*it).second->m_runner->requestAbort();
}

void Manager::onAboutToRun(BaseRunner *runner)
{
    m_taskIdToProgress.emplace(runner->m_taskId, &runner->m_progress);
}

} // namespace Task

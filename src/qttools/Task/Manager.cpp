#include "Manager.h"

#include "Runnable.h"
#include "BaseRunner.h"

namespace Task {

Manager::Manager(QObject *parent)
    : QObject(parent),
      m_taskIdSeq(0)
{
    QObject::connect(this, &Manager::ended,
                     [=](const quint64 taskId) { m_taskIdToProgress.erase(taskId); } );
}

Manager::~Manager()
{
}

const Progress *Manager::taskProgress(quint64 taskId) const
{
    auto it = m_taskIdToProgress.find(taskId);
    return it != m_taskIdToProgress.end() ? (*it).second : nullptr;
}

void Manager::requestAbort(quint64 taskId)
{
    auto it = m_taskIdToProgress.find(taskId);
    if (it != m_taskIdToProgress.end())
        (*it).second->m_runnable->m_taskRunner->requestAbort();
}

} // namespace Task

#include "Manager.h"

#include "BaseRunner.h"

#include <QtCore/QGlobalStatic>

namespace Task {

Manager::Manager(QObject *parent)
    : QObject(parent),
      m_taskIdSeq(0)
{
}

Manager::~Manager()
{ }

QString Manager::taskTitle(quint64 taskId) const
{
    auto runner = this->getRunner(taskId);
    return runner != nullptr ? runner->taskTitle() : QString();
}

const Progress *Manager::taskProgress(quint64 taskId) const
{
    auto runner = this->getRunner(taskId);
    return runner != nullptr ? &runner->progress() : nullptr;
}

void Manager::requestAbort(quint64 taskId)
{
    auto runner = this->getRunner(taskId);
    if (runner != nullptr)
        runner->requestAbort();
}

Q_GLOBAL_STATIC(Manager, mgrGlobalInstance)

Manager *Manager::globalInstance()
{
    return mgrGlobalInstance();
}

void Manager::onAboutToRun(BaseRunner *runner)
{
    m_taskIdToRunner.emplace(runner->m_taskId, runner);
}

void Manager::onDestroyRequest(BaseRunner *runner)
{
    m_taskIdToRunner.erase(runner->taskId());
    runner->destroy();
}

BaseRunner *Manager::getRunner(quint64 taskId)
{
    return const_cast<BaseRunner*>(static_cast<const Manager*>(this)->getRunner(taskId));
}

const BaseRunner *Manager::getRunner(quint64 taskId) const
{
    auto it = m_taskIdToRunner.find(taskId);
    return it != m_taskIdToRunner.end() ? (*it).second : nullptr;
}

} // namespace Task

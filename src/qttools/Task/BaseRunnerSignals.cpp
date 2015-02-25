#include "BaseRunnerSignals.h"

#include "BaseRunner.h"
#include "Manager.h"

namespace Task {

BaseRunnerSignals::BaseRunnerSignals(BaseRunner* runner, QObject *parent)
    : QObject(parent),
      m_runner(runner)
{
    QObject::connect(this, &BaseRunnerSignals::aboutToRun, runner->m_mgr, &Manager::onAboutToRun);
    QObject::connect(this, &BaseRunnerSignals::started, runner->m_mgr, &Manager::started);
    QObject::connect(this, &BaseRunnerSignals::progressStep, runner->m_mgr, &Manager::progressStep);
    QObject::connect(this, &BaseRunnerSignals::progress, runner->m_mgr, &Manager::progress);
    QObject::connect(this, &BaseRunnerSignals::message, runner->m_mgr, &Manager::message);
    QObject::connect(this, &BaseRunnerSignals::ended, runner->m_mgr, &Manager::ended);
}

void BaseRunnerSignals::emitAboutToRun()
{
    emit aboutToRun(m_runner);
}

void BaseRunnerSignals::emitStarted(const QString &title)
{
    emit started(m_runner->m_taskId, title);
}

void BaseRunnerSignals::emitProgressStep(const QString &title)
{
    emit progressStep(m_runner->m_taskId, title);
}

void BaseRunnerSignals::emitProgress(int pct)
{
    emit progress(m_runner->m_taskId, pct);
}

void BaseRunnerSignals::emitMessage(const QString &msg)
{
    emit message(m_runner->m_taskId, msg);
}

void BaseRunnerSignals::emitEnded()
{
    emit ended(m_runner->m_taskId);
}

} // namespace Task

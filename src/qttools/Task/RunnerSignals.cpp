#include "RunnerSignals.h"

#include "BaseRunner.h"
#include "Manager.h"

namespace Task {

RunnerSignals::RunnerSignals(BaseRunner* runner, QObject *parent)
    : QObject(parent),
      m_runner(runner)
{
    QObject::connect(this, &RunnerSignals::aboutToRun, runner->m_mgr, &Manager::onAboutToRun);
    QObject::connect(this, &RunnerSignals::started, runner->m_mgr, &Manager::started);
    QObject::connect(this, &RunnerSignals::progressStep, runner->m_mgr, &Manager::progressStep);
    QObject::connect(this, &RunnerSignals::progress, runner->m_mgr, &Manager::progress);
    QObject::connect(this, &RunnerSignals::message, runner->m_mgr, &Manager::message);
    QObject::connect(this, &RunnerSignals::ended, runner->m_mgr, &Manager::ended);
}

void RunnerSignals::emitAboutToRun()
{
    emit aboutToRun(m_runner);
}

void RunnerSignals::emitStarted(const QString &title)
{
    emit started(m_runner->m_taskId, title);
}

void RunnerSignals::emitProgressStep(const QString &title)
{
    emit progressStep(m_runner->m_taskId, title);
}

void RunnerSignals::emitProgress(int pct)
{
    emit progress(m_runner->m_taskId, pct);
}

void RunnerSignals::emitMessage(const QString &msg)
{
    emit message(m_runner->m_taskId, msg);
}

void RunnerSignals::emitEnded()
{
    emit ended(m_runner->m_taskId);
}

} // namespace Task

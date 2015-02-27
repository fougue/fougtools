/****************************************************************************
**
**  FougTools
**  Copyright FougSys (27 Feb. 2015)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "base_runner_signals.h"

#include "base_runner.h"
#include "manager.h"

namespace qttask {

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
    QObject::connect(this, &BaseRunnerSignals::destroyRequest, runner->m_mgr, &Manager::onDestroyRequest);
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

void BaseRunnerSignals::emitDestroyRequest()
{
    emit destroyRequest(m_runner);
}

} // namespace qttask

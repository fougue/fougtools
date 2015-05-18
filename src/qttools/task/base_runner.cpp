/****************************************************************************
**
**  FougTools
**  Copyright Fougue (27 Feb. 2015)
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

#include "base_runner.h"

#include "manager.h"

namespace qttask {

BaseRunner::BaseRunner(const Manager *mgr)
    : m_mgr(mgr),
      m_taskId(0),
      m_signals(this),
      m_progress(this)
{ }

BaseRunner::~BaseRunner()
{ }

quint64 BaseRunner::taskId() const
{
    return m_taskId;
}

const QString &BaseRunner::taskTitle() const
{
    return m_taskTitle;
}

void BaseRunner::setTaskTitle(const QString &title)
{
    m_taskTitle = title;
}

Progress &BaseRunner::progress()
{
    return m_progress;
}

const Progress &BaseRunner::progress() const
{
    return m_progress;
}

void BaseRunner::run(std::function<void()>&& func)
{
    m_func = func;
    if (m_func) {
        m_signals.emitAboutToRun();
        launch();
    }
}

BaseRunnerSignals *BaseRunner::qtSignals()
{
    return &m_signals;
}

void BaseRunner::execRunnableFunc()
{
    m_signals.emitStarted(m_taskTitle);
    m_func();
    m_signals.emitEnded();
    m_signals.emitDestroyRequest();
}

bool BaseRunner::isAbortRequested()
{
    return false;
}

void BaseRunner::requestAbort()
{ }

void BaseRunner::launch()
{ }

void BaseRunner::destroy()
{
    delete this;
}

} // namespace qttask

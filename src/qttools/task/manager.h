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

#pragma once

#include "runner_qthread.h"

#include <QtCore/QObject>

#include <atomic>
#include <unordered_map>

namespace qttask {

class BaseRunner;
class Progress;

/*! \brief Central class providing management of tasks and notifications
 */
class Manager : public QObject
{
    Q_OBJECT

public:
    Manager(QObject* parent = nullptr);
    ~Manager();

    /*! \brief Create a ready-to-launch Runner object
     *
     *  Typical use:
     *  \code
     *      auto task = qttask::Manager::globalInstance()->newTask();
     *      task->run( [=] { someFunction(task->progress()); } );
     *  \endcode
     *
     *  The created Runner object will be automatically deleted at the end
     *  of BaseRunner::run().
     *  If for any reason BaseRunner::run() is not called, the Runner object
     *  has to be deleted by the caller.
     */
    template<typename SELECTOR = QThread, typename ... ARGS>
    Runner<SELECTOR>* newTask(ARGS ... args)
    {
        auto runner = new Runner<SELECTOR>(this, args ...);
        runner->m_taskId = m_taskIdSeq.fetch_add(1);
        return runner;
    }

    QString taskTitle(quint64 taskId) const;
    const Progress* taskProgress(quint64 taskId) const;

    void requestAbort(quint64 taskId);

    static Manager* globalInstance();

signals:
    void started(quint64 taskId, const QString& title);
    void progressStep(quint64 taskId, const QString& title);
    void progress(quint64 taskId, int percent);
    void message(quint64 taskId, const QString& msg);
    void ended(quint64 taskId);

private:
    friend class BaseRunnerSignals;

    void onAboutToRun(BaseRunner* runner);
    void onDestroyRequest(BaseRunner* runner);
    BaseRunner* getRunner(quint64 taskId);
    const BaseRunner* getRunner(quint64 taskId) const;

    std::atomic<quint64> m_taskIdSeq;
    std::unordered_map<quint64, BaseRunner*> m_taskIdToRunner;
};

} // namespace qttask

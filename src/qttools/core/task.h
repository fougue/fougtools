/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
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

#ifndef QTTOOLS_TASK_H
#define QTTOOLS_TASK_H

#include "core.h"
#include <QtCore/QObject>
class QThread;

namespace qttools {

class QTTOOLS_CORE_EXPORT Task : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool isWaitingStop READ isWaitingStop)
  Q_PROPERTY(bool isBoundToThread READ isBoundToThread)
  Q_PROPERTY(bool autoDeleteBoundThread
             READ autoDeleteBoundThread WRITE setAutoDeleteBoundThread)
  Q_PROPERTY(bool loopCount READ loopCount WRITE setLoopCount)
  Q_PROPERTY(bool loopInterval READ loopInterval WRITE setLoopInterval)

public:
  Task(QObject* parent = NULL);
  ~Task();

  bool isRunning() const;
  bool isWaitingStop() const;

  bool isBoundToThread() const;
  Q_SLOT void bindToThread(QThread* thread);

  bool autoDeleteBoundThread() const;
  Q_SLOT void setAutoDeleteBoundThread(bool v);

  int loopCount() const;
  Q_SLOT void setLoopCount(int v);

  int loopInterval() const;
  Q_SLOT void setLoopInterval(int msecs);

signals:
  void started();
  void finished();
  void aboutToStop();
  void stopped();

public slots:
  void exec();
  void asynchronousStop();
  void stop(int maxTime = -1);

protected:
  virtual void action() = 0;
  void acknowledgeStop();

private:
  class Private;
  Private* const d;
};

template<typename FUNCTOR>
class FunctorTask : public Task
{
public:
  FunctorTask(FUNCTOR functor, QObject* parent = NULL);

protected:
  void action();

private:
  FUNCTOR m_functor;
};

template<typename FUNCTOR>
Task* newFunctorTask(FUNCTOR functor, QObject* parent = NULL);

// --
// -- Implementation
// --

template<typename FUNCTOR>
FunctorTask<FUNCTOR>::FunctorTask(FUNCTOR functor, QObject* parent)
  : Task(parent),
    m_functor(functor)
{
}

template<typename FUNCTOR>
void FunctorTask<FUNCTOR>::action()
{
  m_functor();
  emit finished();
}

template<typename FUNCTOR>
Task* newFunctorTask(FUNCTOR functor, QObject* parent)
{
  return new FunctorTask<FUNCTOR>(functor, parent);
}

} // namespace qttools

#endif // QTTOOLS_TASK_H

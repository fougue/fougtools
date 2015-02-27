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

#include "base_runner.h"

#include <QtCore/QRunnable>
#include <QtCore/QThreadPool>

namespace qttask {

/*! \brief Task runner using the global instance of QThreadPool
 *
 *  Internally using QThreadPool::globalInstance()->start(...)
 */
template<>
class Runner<QThreadPool> : public QRunnable, public BaseRunner
{
public:
    /*! \param priority Same meaning as the second parameter of
     *                  QThreadPool::start(QRunnable*, int priority)
     */
    Runner<QThreadPool>(const Manager* mgr, int priority = 0)
        : BaseRunner(mgr),
          m_isAbortRequested(false),
          m_priority(priority)
    {
        this->setAutoDelete(false);
    }

    void run() override // -- QRunnable
    { this->execRunnableFunc(); }

    bool isAbortRequested() override
    { return m_isAbortRequested; }

    void requestAbort() override
    { m_isAbortRequested = true; }

    void launch() override
    { QThreadPool::globalInstance()->start(this, m_priority); }

private:
    bool m_isAbortRequested;
    int m_priority;
};

} // namespace qttask

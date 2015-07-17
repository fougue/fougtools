/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
****************************************************************************/

#include "sleep.h"

#include <QtCore/QEventLoop>
#include <QtCore/QThread>
#include <QtCore/QTimer>

namespace qtcore {

namespace internal {

class SleepTool : public QThread
{
public:
    static void milliSleep(unsigned msec)
    {
        QThread::msleep(msec);
    }
};

} // namespace internal

/*!
 * \brief Cause the current thread to sleep for \p msecs milliseconds
 *
 *  Internally based on QThread::msleep()
 *
 * \sa waitForMSec()
 *
 * \headerfile sleep.h <qttools/core/sleep.h>
 */
void mSecSleep(unsigned msec)
{
    internal::SleepTool::milliSleep(msec);
}

/*!
 * \brief Waits until \p msec milliseconds have elapsed
 *
 * Internally a QEventLoop is used, so the Qt event system is not blocked while
 * waiting.
 *
 * \sa mSecSleep()
 *
 * \headerfile sleep.h <qttools/core/sleep.h>
 */
void waitForMSec(unsigned msec)
{
    if (msec > 0) {
        QEventLoop eventLoop;
        QTimer::singleShot(msec, &eventLoop, SLOT(quit()));
        eventLoop.exec();
    }
}

} // namespace qtcore

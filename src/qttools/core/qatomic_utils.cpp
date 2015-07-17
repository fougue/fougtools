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

#include "qatomic_utils.h"

#include <QtCore/QAtomicInt>
#include <QtCore/QAtomicPointer>
#include <QtCore/QtDebug>

namespace qtcore {

/*! \class QAtomicUtils
 *  \brief Provides a collection of tools around QAtomicInt and QAtomicPointer
 *
 *  QAtomicUtils mainly provides common operations for QAtomicInt and
 *  QAtomicPointer. It is useful when portability for Qt4 / Qt5 is required
 *  because the API of these two classes have changed.
 *
 *  \headerfile qatomic_utils.h <qttools/core/qatomic_utils.h>
 *  \ingroup qttools_core
 *
 */

int QAtomicUtils::loadRelaxed(const QAtomicInt &atomInt)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    return atomInt.load();
#else
    return atomInt;
#endif
}

void QAtomicUtils::storeRelaxed(QAtomicInt* atomInt, int newVal)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    atomInt->store(newVal);
#else
    atomInt->fetchAndStoreRelaxed(newVal);
#endif
}

void QAtomicUtils::storeRelease(QAtomicInt* atomInt, int newVal)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    atomInt->storeRelease(newVal);
#else
    atomInt->fetchAndStoreRelease(newVal);
#endif
}

} // namespace qtcore

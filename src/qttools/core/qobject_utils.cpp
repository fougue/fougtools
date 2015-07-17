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

#include "qobject_utils.h"

#include <QtCore/QObject>

namespace qtcore {

/*! \class QObjectUtils
 *  \brief Provides a collection of tools around QObject
 *  \headerfile qobject_utils.h <qttools/core/qobject_utils.h>
 *  \ingroup qttools_core
 *
 */

void QObjectUtils::forwardSignal(
        const QObject* sender, const QObject* resender, const char* signal)
{
    QObject::connect(sender, signal, resender, signal);
}

} // namespace qtcore

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

#pragma once

#include "core.h"

#include <QtCore/QSignalMapper>

namespace qtcore {

class QTTOOLS_CORE_EXPORT QSignalMapperUtils
{
public:
    typedef void (QSignalMapper::*SignalMapped_int)(int);
    typedef void (QSignalMapper::*SignalMapped_QString)(const QString&);
    typedef void (QSignalMapper::*SignalMapped_QWidgetPtr)(QWidget*);
    typedef void (QSignalMapper::*SignalMapped_QObjectPtr)(QObject*);

    typedef void (QSignalMapper::*SlotMap)();
    typedef void (QSignalMapper::*SlotMap_QObjectPtr)(QObject*);

    static SignalMapped_int signalMapped_int();
    static SignalMapped_QString signalMapped_QString();
    static SignalMapped_QWidgetPtr signalMapped_QWidgetPtr();
    static SignalMapped_QObjectPtr signalMapped_QObjectPtr();

    static SlotMap slotMap();
    static SlotMap_QObjectPtr slotMap_QObjectPtr();
};

} // namespace qtcore

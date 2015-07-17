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

#include "gui.h"

#include <QtWidgets/QComboBox>

namespace qtgui {

class QTTOOLS_GUI_EXPORT QComboBoxUtils
{
public:
    typedef void (QComboBox::*SignalActivated_int)(int);
    typedef void (QComboBox::*SignalActivated_QString)(const QString&);
    typedef void (QComboBox::*SignalCurrentIndexChanged_int)(int);
    typedef void (QComboBox::*SignalCurrentIndexChanged_QString)(const QString&);
    typedef void (QComboBox::*SignalHighlighted_int)(int);
    typedef void (QComboBox::*SignalHighlighted_QString)(const QString&);

    static SignalActivated_int signalActivated_int();
    static SignalActivated_QString signalActivated_QString();
    static SignalCurrentIndexChanged_int signalCurrentIndexChanged_int();
    static SignalCurrentIndexChanged_QString signalCurrentIndexChanged_QString();
    static SignalHighlighted_int signalHighlighted_int();
    static SignalHighlighted_QString signalHighlighted_QString();
};

} // namespace qtgui

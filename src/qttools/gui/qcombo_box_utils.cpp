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

#include "qcombo_box_utils.h"

namespace qtgui {

/*!
 * \class QComboBoxUtils
 * \brief Provides a collection of tools around QComboBox
 * \headerfile qcombo_box_utils.h <qttools/gui/qcombo_box_utils.h>
 * \ingroup qttools_gui
 */

QComboBoxUtils::SignalActivated_int QComboBoxUtils::signalActivated_int()
{
    return (QComboBoxUtils::SignalActivated_int)&QComboBox::activated;
}

QComboBoxUtils::SignalActivated_QString QComboBoxUtils::signalActivated_QString()
{
    return (QComboBoxUtils::SignalActivated_QString)&QComboBox::activated;
}

QComboBoxUtils::SignalCurrentIndexChanged_int QComboBoxUtils::signalCurrentIndexChanged_int()
{
    return (QComboBoxUtils::SignalCurrentIndexChanged_int)&QComboBox::currentIndexChanged;
}

QComboBoxUtils::SignalCurrentIndexChanged_QString QComboBoxUtils::signalCurrentIndexChanged_QString()
{
    return (QComboBoxUtils::SignalCurrentIndexChanged_QString)&QComboBox::currentIndexChanged;
}

QComboBoxUtils::SignalHighlighted_int QComboBoxUtils::signalHighlighted_int()
{
    return (QComboBoxUtils::SignalHighlighted_int)&QComboBox::highlighted;
}

QComboBoxUtils::SignalHighlighted_QString QComboBoxUtils::signalHighlighted_QString()
{
    return (QComboBoxUtils::SignalHighlighted_QString)&QComboBox::highlighted;
}

} // namespace qtgui

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
#include "abstract_length_editor.h"

namespace qtgui {

class QTTOOLS_GUI_EXPORT MeasurementSystemPreferences
{
public:
    MeasurementSystemPreferences();
    MeasurementSystemPreferences(
            AbstractLengthEditor::MetricUnit metUnit,
            AbstractLengthEditor::ImperialUnit impUnit);

    AbstractLengthEditor::MetricUnit metricUnit() const;
    void setMetricUnit(AbstractLengthEditor::MetricUnit unit);

    AbstractLengthEditor::ImperialUnit imperialUnit() const;
    void setImperialUnit(AbstractLengthEditor::ImperialUnit unit);

private:
    AbstractLengthEditor::MetricUnit m_metricUnit;
    AbstractLengthEditor::ImperialUnit m_imperialUnit;
};

} // namespace qtgui

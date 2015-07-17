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

#include "measurement_system_preferences.h"

namespace qtgui {

/*!
 * \class MeasurementSystemPreferences
 * \brief
 *
 * \headerfile measurement_system_preferences.h <qttools/gui/measurement_system_preferences.h>
 * \ingroup qttools_gui
 *
 */

MeasurementSystemPreferences::MeasurementSystemPreferences()
    : m_metricUnit(AbstractLengthEditor::MillimeterUnit),
      m_imperialUnit(AbstractLengthEditor::InchUnit)
{
}

MeasurementSystemPreferences::MeasurementSystemPreferences(
        AbstractLengthEditor::MetricUnit metUnit,
        AbstractLengthEditor::ImperialUnit impUnit)
    : m_metricUnit(metUnit),
      m_imperialUnit(impUnit)
{
}

AbstractLengthEditor::MetricUnit MeasurementSystemPreferences::metricUnit() const
{
    return m_metricUnit;
}

AbstractLengthEditor::ImperialUnit MeasurementSystemPreferences::imperialUnit() const
{
    return m_imperialUnit;
}

void MeasurementSystemPreferences::setMetricUnit(AbstractLengthEditor::MetricUnit unit)
{
    m_metricUnit = unit;
}

void MeasurementSystemPreferences::setImperialUnit(AbstractLengthEditor::ImperialUnit unit)
{
    m_imperialUnit = unit;
}

} // namespace qtgui

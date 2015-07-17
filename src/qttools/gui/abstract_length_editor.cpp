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

#include "abstract_length_editor.h"

#include "quantity_editor_manager.h"

namespace qtgui {

/*!
 * \class AbstractLengthEditor
 * \brief Abstract base class for all length (\c [L]) editors that are aware of
 *        the current measurement system (metric or imperial)
 *
 * \headerfile abstract_length_editor.h <qttools/gui/abstract_length_editor.h>
 * \ingroup qttools_gui
 *
 * length() and setLength() use values in millimeter (mm).
 */

QVector<AbstractLengthEditor::MetricUnit> AbstractLengthEditor::allMetricUnits()
{
    return QVector<MetricUnit>() << MeterUnit << CentimeterUnit << MillimeterUnit;
}

QVector<AbstractLengthEditor::ImperialUnit> AbstractLengthEditor::allImperialUnits()
{
    return QVector<ImperialUnit>() << InchUnit << FootUnit << YardUnit;
}

AbstractLengthEditor::AbstractLengthEditor()
    : m_prefMetricUnit(MillimeterUnit),
      m_prefImperialUnit(InchUnit)
{
}

double AbstractLengthEditor::qtyValue() const
{
    return this->length();
}

void AbstractLengthEditor::setQtyValue(double v)
{
    this->setLength(v);
}

/*! \fn double AbstractLengthEditor::length() const
 *  \brief Length in millimeter (mm)
 */

/*! \fn void AbstractLengthEditor::setLength(double)
 *  \brief Set the length in millimeter (mm) to be edited
 */

/*! Length unit used when the metric measurement system is currently active
 */
AbstractLengthEditor::MetricUnit AbstractLengthEditor::preferredMetricUnit() const
{
    return m_prefMetricUnit;
}

/*! Set the length unit to be used when the metric measurement system is
 *  currently active
 */
void AbstractLengthEditor::setPreferredMetricUnit(MetricUnit unit)
{
    const double lengthMm = this->length();
    m_prefMetricUnit = unit;
    this->setLength(lengthMm);
    this->updateEditor(this->measurementSystem());
}

/*! Length unit used when the imperial measurement system is currently active
 */
AbstractLengthEditor::ImperialUnit AbstractLengthEditor::preferredImperialUnit() const
{
    return m_prefImperialUnit;
}

/*! Set the length unit to be used when the imperial measurement system is
 *  currently active
 */
void AbstractLengthEditor::setPreferredImperialUnit(ImperialUnit unit)
{
    m_prefImperialUnit = unit;
    this->updateEditor(this->measurementSystem());
}

// -- Utilities

QString AbstractLengthEditor::unitText(MetricUnit unit)
{
    switch (unit) {
    case MeterUnit : return QLatin1String("m");
    case CentimeterUnit : return QLatin1String("cm");
    case MillimeterUnit : return QLatin1String("mm");
    default : return QString();
    }
}

QString AbstractLengthEditor::unitText(ImperialUnit unit)
{
    switch (unit) {
    case InchUnit : return QLatin1String("in");
    case FootUnit : return QLatin1String("ft");
    case YardUnit : return QLatin1String("yd");
    default : return QString();
    }
}

double AbstractLengthEditor::asMetricLength(double len, MetricUnit unit)
{
    switch (unit) {
    case qtgui::AbstractLengthEditor::MeterUnit :
        return len / 1000.;
    case qtgui::AbstractLengthEditor::CentimeterUnit :
        return len / 10.;
    case qtgui::AbstractLengthEditor::MillimeterUnit :
        return len;
    }
    return len;
}

double AbstractLengthEditor::asImperialLength(double len, ImperialUnit unit)
{
    switch (unit) {
    case qtgui::AbstractLengthEditor::InchUnit :
        return len / 25.4;
    case qtgui::AbstractLengthEditor::FootUnit :
        return (len / 25.4) / 12.;
    case qtgui::AbstractLengthEditor::YardUnit :
        return (len / 25.4) / 36.;
    }
    return len;
}

} // namespace qtgui

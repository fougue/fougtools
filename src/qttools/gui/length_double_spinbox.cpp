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

#include "length_double_spinbox.h"

#include "../../cpptools/scoped_value.h"
#include "quantity_editor_manager.h"

namespace qtgui {

namespace internal {

static double toMmValue(double v, qtgui::LengthDoubleSpinBox::MetricUnit unit)
{
    switch (unit) {
    case qtgui::LengthDoubleSpinBox::MeterUnit:
        return v * 1000.;
    case qtgui::LengthDoubleSpinBox::CentimeterUnit:
        return v * 10.;
    case qtgui::LengthDoubleSpinBox::MillimeterUnit:
        return v;
    default:
        return v;
    }
}

static double toMmValue(double v, qtgui::LengthDoubleSpinBox::ImperialUnit unit)
{
    switch (unit) {
    case qtgui::LengthDoubleSpinBox::InchUnit:
        return v * 25.4;
    case qtgui::LengthDoubleSpinBox::FootUnit:
        return (v * 25.4) * 12.;
    case qtgui::LengthDoubleSpinBox::YardUnit:
        return (v * 25.4) * 36.;
    default:
        return v;
    }
}

} // namespace internal

class LengthDoubleSpinBox::Private
{
public:
    Private();

    void onValueChanged(double v);

    double m_orgLengthMm;
    bool m_valueHasChanged;
    bool m_isInternalUpdateContext;
};

LengthDoubleSpinBox::Private::Private()
    : m_orgLengthMm(0.),
      m_valueHasChanged(false),
      m_isInternalUpdateContext(false)
{
}

void LengthDoubleSpinBox::Private::onValueChanged(double v)
{
    Q_UNUSED(v);
    if (!m_isInternalUpdateContext)
        m_valueHasChanged = true;
}

/*!
 * \class LengthDoubleSpinBox
 * \brief Provides a QDoubleSpinBox adapted to the interface of AbstractLengthEditor
 *
 * \headerfile length_double_spinbox.h <qttools/gui/length_double_spinbox.h>
 * \ingroup qttools_gui
 */

LengthDoubleSpinBox::LengthDoubleSpinBox(QWidget* parent)
    : QDoubleSpinBox(parent),
      d(new Private)
{
    this->updateEditor(this->measurementSystem());
    QObject::connect(
                this,
                static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                [=](double v) { d->onValueChanged(v); } );
}

LengthDoubleSpinBox::~LengthDoubleSpinBox()
{
    delete d;
}

double LengthDoubleSpinBox::length() const
{
    if (!d->m_valueHasChanged)
        return d->m_orgLengthMm;

    const double v = QDoubleSpinBox::value();
    switch (this->measurementSystem()) {
    case QLocale::MetricSystem:
        return internal::toMmValue(v, this->preferredMetricUnit());
#if QT_VERSION >= 0x050000
    case QLocale::ImperialUKSystem:
#endif // QT_VERSION
    case QLocale::ImperialSystem:
        return internal::toMmValue(v, this->preferredImperialUnit());
    }
    return 0.;
}

void LengthDoubleSpinBox::setLength(double v)
{
    d->m_orgLengthMm = v;
    d->m_valueHasChanged = false;

    cpp::ScopedBool sb(d->m_isInternalUpdateContext, true);
    Q_UNUSED(sb);

    switch (this->measurementSystem()) {
    case QLocale::MetricSystem:
        this->setValue(AbstractLengthEditor::asMetricLength(
                           v, this->preferredMetricUnit()));
        break;
#if QT_VERSION >= 0x050000
    case QLocale::ImperialUKSystem:
#endif // QT_VERSION
    case QLocale::ImperialSystem:
        this->setValue(AbstractLengthEditor::asImperialLength(
                           v, this->preferredImperialUnit()));
        break;
    }
}

void LengthDoubleSpinBox::updateEditor(QLocale::MeasurementSystem newSys)
{
    cpp::ScopedBool sb(d->m_isInternalUpdateContext, true);
    Q_UNUSED(sb);

    const double oldLengthMm = this->length();
    double newLengthUnit = 0.;
    QString unitStr;
    switch (newSys) {
    case QLocale::MetricSystem: {
        unitStr = AbstractLengthEditor::unitText(this->preferredMetricUnit());
        newLengthUnit = AbstractLengthEditor::asMetricLength(
                    oldLengthMm, this->preferredMetricUnit());
        break;
    }
#if QT_VERSION >= 0x050000
    case QLocale::ImperialUKSystem:
#endif // QT_VERSION
    case QLocale::ImperialSystem: {
        unitStr = AbstractLengthEditor::unitText(this->preferredImperialUnit());
        newLengthUnit = AbstractLengthEditor::asImperialLength(
                    oldLengthMm, this->preferredImperialUnit());
        break;
    }
    }

    QDoubleSpinBox::setSuffix(unitStr);
    QDoubleSpinBox::setValue(newLengthUnit);
}

} // namespace qtgui

#include "moc_length_double_spinbox.cpp"

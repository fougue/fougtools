/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "qttools/gui/length_double_spinbox.h"

#include "cpptools/scoped_value.h"
#include "qttools/gui/length_editor_manager.h"

namespace {

QLocale::MeasurementSystem currMeasurementSys()
{
  return qttools::LengthEditorManager::globalInstance()->measurementSytem();
}

double toMmValue(double v, qttools::LengthDoubleSpinBox::MetricUnit unit)
{
  switch (unit) {
  case qttools::LengthDoubleSpinBox::MeterUnit:
    return v * 1000.;
  case qttools::LengthDoubleSpinBox::CentimeterUnit:
    return v * 10.;
  case qttools::LengthDoubleSpinBox::MillimeterUnit:
    return v;
  default:
    return v;
  }
}

double toMmValue(double v, qttools::LengthDoubleSpinBox::ImperialUnit unit)
{
  switch (unit) {
  case qttools::LengthDoubleSpinBox::InchUnit:
    return v * 25.4;
  case qttools::LengthDoubleSpinBox::FootUnit:
    return (v * 25.4) * 12.;
  case qttools::LengthDoubleSpinBox::YardUnit:
    return (v * 25.4) * 36.;
  default:
    return v;
  }
}

} // Anonymous namespace

namespace qttools {

class LengthDoubleSpinBoxPrivate
{
public:
  LengthDoubleSpinBoxPrivate();

  void onValueChanged(double v);

  double m_orgLengthMm;
  bool m_valueHasChanged;
  bool m_isInternalUpdateContext;
};

LengthDoubleSpinBoxPrivate::LengthDoubleSpinBoxPrivate()
  : m_orgLengthMm(0.),
    m_valueHasChanged(false),
    m_isInternalUpdateContext(false)
{
}

void LengthDoubleSpinBoxPrivate::onValueChanged(double v)
{
  Q_UNUSED(v);
  if (!m_isInternalUpdateContext)
    m_valueHasChanged = true;
}

/*! \class LengthDoubleSpinBox
 *  \brief Provides a QDoubleSpinBox adapted to the interface of AbstractLengthEditor
 *
 */

LengthDoubleSpinBox::LengthDoubleSpinBox(QWidget* parent)
  : QDoubleSpinBox(parent),
    d_ptr(new LengthDoubleSpinBoxPrivate)
{
  this->updateEditor(::currMeasurementSys());
  connect(this, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
}

LengthDoubleSpinBox::~LengthDoubleSpinBox()
{
  delete d_ptr;
}

double LengthDoubleSpinBox::length() const
{
  Q_D(const LengthDoubleSpinBox);

  if (!d->m_valueHasChanged)
    return d->m_orgLengthMm;

  const double v = this->value();
  switch (::currMeasurementSys()) {
  case QLocale::MetricSystem:
    return ::toMmValue(v, this->preferredMetricUnit());
  case QLocale::ImperialSystem:
    return ::toMmValue(v, this->preferredImperialUnit());
  }
  return 0.;
}

void LengthDoubleSpinBox::setLength(double v)
{
  Q_D(LengthDoubleSpinBox);

  d->m_orgLengthMm = v;
  d->m_valueHasChanged = false;

  cpp::ScopedBool sb(d->m_isInternalUpdateContext, true); Q_UNUSED(sb);
  switch (::currMeasurementSys()) {
  case QLocale::MetricSystem:
    this->setValue(AbstractLengthEditor::asMetricLength(v, this->preferredMetricUnit()));
    break;
  case QLocale::ImperialSystem:
    this->setValue(AbstractLengthEditor::asImperialLength(v, this->preferredImperialUnit()));
    break;
  }
}

void LengthDoubleSpinBox::updateEditor(QLocale::MeasurementSystem newSys)
{
  Q_D(LengthDoubleSpinBox);

  cpp::ScopedBool sb(d->m_isInternalUpdateContext, true); Q_UNUSED(sb);

  const double oldLengthMm = this->length();
  double newLengthUnit = 0.;
  QString unitStr;
  switch (newSys) {
  case QLocale::MetricSystem: {
    unitStr = AbstractLengthEditor::unitText(this->preferredMetricUnit());
    newLengthUnit = AbstractLengthEditor::asMetricLength(oldLengthMm, this->preferredMetricUnit());
    break;
  }
  case QLocale::ImperialSystem: {
    unitStr = AbstractLengthEditor::unitText(this->preferredImperialUnit());
    newLengthUnit = AbstractLengthEditor::asImperialLength(oldLengthMm, this->preferredImperialUnit());
    break;
  }
  }

  this->setSuffix(unitStr);
  this->setValue(newLengthUnit);
}

} // namespace qttools

#include "moc_length_double_spinbox.cpp"

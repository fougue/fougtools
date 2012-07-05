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

#include "abstract_length_editor.h"

#include "length_editor_manager.h"

static QLocale::MeasurementSystem currMeasurementSys()
{
  return qttools::LengthEditorManager::globalInstance()->measurementSytem();
}

namespace qttools {

/*! \class AbstractLengthEditor
 *  \brief Abstract base class for all length (\c [L]) editors that are
 *         aware of the current measurement system (metric or imperial)
 *
 *  length() and setLength() use values in millimeter (mm).
 */

// -- Lifecycle

AbstractLengthEditor::AbstractLengthEditor()
  : m_prefMetricUnit(MillimeterUnit),
    m_prefImperialUnit(InchUnit)
{
  LengthEditorManager::globalInstance()->attach(this);
}

AbstractLengthEditor::~AbstractLengthEditor()
{
  LengthEditorManager::globalInstance()->detach(this);
}

// -- Query

/*! \fn double AbstractLengthEditor::length() const
 *  \brief Length in millimeter (mm)
 */

/*! \brief Length unit used when the metric measurement system is currently
 *         active
 */
AbstractLengthEditor::MetricUnit AbstractLengthEditor::preferredMetricUnit() const
{
  return m_prefMetricUnit;
}

/*! \brief Set the length unit to be used when the metric measurement system
 *         is currently active
 */
void AbstractLengthEditor::setPreferredMetricUnit(MetricUnit unit)
{
  m_prefMetricUnit = unit;
  this->updateEditor(::currMeasurementSys());
}

/*! \brief Length unit used when the imperial measurement system is currently
 *         active
 */
AbstractLengthEditor::ImperialUnit AbstractLengthEditor::preferredImperialUnit() const
{
  return m_prefImperialUnit;
}

/*! \brief Set the length unit to be used when the imperial measurement system
 *         is currently active
 */
void AbstractLengthEditor::setPreferredImperialUnit(ImperialUnit unit)
{
  m_prefImperialUnit = unit;
  this->updateEditor(::currMeasurementSys());
}

// -- Element change

/*! \fn void AbstractLengthEditor::setLength(double)
 *  \brief Set the length (in millimeter (mm)) to be edited
 */

/*! \brief Called by LengthEditorManager when the current measurement system
 *         was switched to another one
 *
 *  Does nothing by default
 */
void AbstractLengthEditor::updateEditor(QLocale::MeasurementSystem /*newSys*/)
{
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
  case qttools::AbstractLengthEditor::MeterUnit :
    return len / 1000.;
  case qttools::AbstractLengthEditor::CentimeterUnit :
    return len / 10.;
  case qttools::AbstractLengthEditor::MillimeterUnit :
    return len;
  }
  return len;
}

double AbstractLengthEditor::asImperialLength(double len, ImperialUnit unit)
{
  switch (unit) {
  case qttools::AbstractLengthEditor::InchUnit :
    return len / 25.4;
  case qttools::AbstractLengthEditor::FootUnit :
    return (len / 25.4) / 12.;
  case qttools::AbstractLengthEditor::YardUnit :
    return (len / 25.4) / 36.;
  }
  return len;
}

} // namespace qttools

/****************************************************************************
**
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
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

#pragma once

#include "gui.h"
#include "abstract_quantity_editor.h"
#include <QtCore/QVector>

namespace qtgui {

class QTTOOLS_GUI_EXPORT AbstractLengthEditor : public AbstractQuantityEditor
{
public:
    enum MetricUnit
    {
        MeterUnit,
        CentimeterUnit,
        MillimeterUnit
    };
    static QVector<MetricUnit> allMetricUnits();

    enum ImperialUnit
    {
        InchUnit,
        FootUnit,
        YardUnit
    };
    static QVector<ImperialUnit> allImperialUnits();

    AbstractLengthEditor();

    double qtyValue() const Q_DECL_OVERRIDE;
    void setQtyValue(double v) Q_DECL_OVERRIDE;

    virtual double length() const = 0;
    virtual void setLength(double v) = 0;

    MetricUnit preferredMetricUnit() const;
    virtual void setPreferredMetricUnit(MetricUnit unit);

    ImperialUnit preferredImperialUnit() const;
    virtual void setPreferredImperialUnit(ImperialUnit unit);

    // -- Utilities
    static QString unitText(MetricUnit unit);
    static QString unitText(ImperialUnit unit);
    static double asMetricLength(double len, MetricUnit unit);
    static double asImperialLength(double len, ImperialUnit unit);

private:
    MetricUnit m_prefMetricUnit;
    ImperialUnit m_prefImperialUnit;
};

} // namespace qtgui

#include <QtCore/QMetaType>
Q_DECLARE_METATYPE(qtgui::AbstractLengthEditor::MetricUnit)
Q_DECLARE_METATYPE(qtgui::AbstractLengthEditor::ImperialUnit)


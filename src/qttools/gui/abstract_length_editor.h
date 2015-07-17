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


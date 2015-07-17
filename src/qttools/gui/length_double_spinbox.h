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
// QtWidgets
#include <QDoubleSpinBox>

namespace qtgui {

class QTTOOLS_GUI_EXPORT LengthDoubleSpinBox :
        public QDoubleSpinBox,
        public AbstractLengthEditor
{
    Q_OBJECT
    Q_PROPERTY(double length READ length WRITE setLength)

public:
    LengthDoubleSpinBox(QWidget* parent = NULL);
    ~LengthDoubleSpinBox();

    double length() const Q_DECL_OVERRIDE;
    Q_SLOT void setLength(double v) Q_DECL_OVERRIDE;

public slots:
    void updateEditor(QLocale::MeasurementSystem newSys) Q_DECL_OVERRIDE;

private:
    class Private;
    Private* const d;
};

} // namespace qtgui

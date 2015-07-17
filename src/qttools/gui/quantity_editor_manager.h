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
#include <QtCore/QLocale>
#include <QtCore/QSet>

namespace qtgui {

class AbstractQuantityEditor;

namespace internal { class QuantityEditorManagerCreator; }

class QTTOOLS_GUI_EXPORT QuantityEditorManager : public QObject
{
    Q_OBJECT

private:
    QuantityEditorManager();
    ~QuantityEditorManager();

    void attach(AbstractQuantityEditor* editor);
    void detach(AbstractQuantityEditor* editor);

public:
    static QuantityEditorManager* globalInstance();

    QLocale::MeasurementSystem measurementSytem() const;
    void setMeasurementSystem(QLocale::MeasurementSystem sys);

signals:
    void currentMeasurementSytemChanged(QLocale::MeasurementSystem sys);

private:
    friend class internal::QuantityEditorManagerCreator;
    friend class AbstractQuantityEditor;
    QSet<AbstractQuantityEditor*> m_qtyEditors;
    QLocale::MeasurementSystem m_measureSys;
};

} // namespace qtgui

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
// QtWidgets
#include <QWidget>
class QTextEdit;

namespace qtgui {

class QTTOOLS_GUI_EXPORT LineNumbersBar : public QWidget
{
    Q_OBJECT

public:
    LineNumbersBar(QWidget* parent = NULL);
    ~LineNumbersBar();

    void setCurrentLine(int lineno);
    void setStopLine(int lineno);
    void setBugLine(int lineno);
    void setTextEdit(QTextEdit* edit);

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    void updateWidget();

    class Private;
    Private* const d;
};

} //namespace qtgui

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
#include <QtCore/QObject>
// QtWidgets
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
class QResizeEvent;
QT_END_NAMESPACE

namespace qtgui {

class QTTOOLS_GUI_EXPORT CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = NULL);
    ~CodeEditor();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    class LineNumberArea;
    class Private;
    Private* const d;
};

} // namespace qtgui


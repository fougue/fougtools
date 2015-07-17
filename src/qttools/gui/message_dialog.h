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
#include <QDialog>
#include <QDialogButtonBox>
class QLabel;

namespace qtgui {

class QTTOOLS_GUI_EXPORT MessageDialog : public QDialog
{
public:
    enum Icon
    {
        NoIcon,
        Information,
        Warning,
        Critical,
        Question
    };

    MessageDialog(
            Icon icon,
            const QString& title,
            const QString& text,
            QDialogButtonBox::StandardButtons buttons,
            QWidget* parent = NULL);

    QWidget* detailsWidget() const;
    void setDetailsWidget(QWidget* widget);

private:
    QLabel* m_textLabel;
    QWidget* m_detailsWidget;
};

} // namespace qtgui

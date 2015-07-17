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

#include "message_dialog.h"

#include "../core/qsignal_mapper_utils.h"

#include <QtCore/QSignalMapper>
// QtWidgets
#include <QApplication>
#include <QAbstractButton>
#include <QGridLayout>
#include <QLabel>
#include <QStyle>

namespace qtgui {

/*!
 * \class MessageDialog
 * \brief Alternative to QMessageBox providing a customizable "details" widget
 *
 * \headerfile message_dialog.h <qttools/gui/message_dialog.h>
 * \ingroup qttools_gui
 *
 */

MessageDialog::MessageDialog(Icon icon,
                             const QString& title,
                             const QString& text,
                             QDialogButtonBox::StandardButtons buttons,
                             QWidget* parent)
    : QDialog(parent),
      m_textLabel(new QLabel(text, this)),
      m_detailsWidget(new QWidget(this))
{
    this->setWindowTitle(title);
    QLabel* pixLabel = new QLabel(this);
    const QSize pixSize(32, 32);
    const QStyle* style = QApplication::style();
    switch (icon) {
    case Question :
        pixLabel->setPixmap(style->standardIcon(QStyle::SP_MessageBoxQuestion).pixmap(pixSize));
        break;
    case Information :
        pixLabel->setPixmap(style->standardIcon(QStyle::SP_MessageBoxInformation).pixmap(pixSize));
        break;
    case Warning :
        pixLabel->setPixmap(style->standardIcon(QStyle::SP_MessageBoxWarning).pixmap(pixSize));
        break;
    case Critical :
        pixLabel->setPixmap(style->standardIcon(QStyle::SP_MessageBoxCritical).pixmap(pixSize));
        break;
    case NoIcon : break;
    }
    QDialogButtonBox* btnBox = new QDialogButtonBox(buttons, Qt::Horizontal, this);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(pixLabel, 0, 0);
    layout->addWidget(m_textLabel, 0, 1);
    layout->addWidget(m_detailsWidget, 1, 1);
    layout->addWidget(btnBox, 2, 0, 1, 2, Qt::AlignRight);
    this->setLayout(layout);

    QSignalMapper* sigMapper = new QSignalMapper(this);
    foreach (QAbstractButton* btn, btnBox->buttons()) {
        sigMapper->setMapping(btn, btnBox->standardButton(btn));
        QObject::connect(btn, &QAbstractButton::clicked,
                         sigMapper, qtcore::QSignalMapperUtils::slotMap());
    }
    QObject::connect(sigMapper, qtcore::QSignalMapperUtils::signalMapped_int(), this, &QDialog::done);
}

QWidget *MessageDialog::detailsWidget() const
{
    return m_detailsWidget;
}

void MessageDialog::setDetailsWidget(QWidget* widget)
{
    if (widget == NULL)
        return;
    widget->setParent(m_detailsWidget);
    QBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(widget);
    m_detailsWidget->setLayout(layout);
}

} // namespace qtgui

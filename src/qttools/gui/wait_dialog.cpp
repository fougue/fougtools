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

#include "wait_dialog.h"

#include <QtCore/QTimer>
#include <QtCore/QThread>
// QtWidgets
#include <QApplication>
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QProgressBar>

namespace qtgui {

class WaitDialog::Private
{
public:
    Private(WaitDialog* parent)
        : m_waitLabel(NULL),
          m_progressBar(NULL),
          m_btnBox(NULL),
          m_updateTimer(new QTimer(parent)),
          m_minDuration(1000)
    {
    }

    QLabel* m_waitLabel;
    QProgressBar* m_progressBar;
    QDialogButtonBox* m_btnBox;
    QTimer* m_updateTimer;
    int m_minDuration;
};

/*!
 * \class WaitDialog
 * \brief Provides a dialog for long background operations
 *
 * \headerfile wait_dialog.h <qttools/gui/wait_dialog.h>
 * \ingroup qttools_gui
 *
 */

WaitDialog::WaitDialog(QWidget* parent)
    : QDialog(parent),
      d(new Private(this))
{
    // Create the UI
    this->setObjectName("qttools__WaitDialog");
    this->setWindowTitle(tr("Waiting"));
    this->resize(170, 60);

    d->m_waitLabel = new QLabel(this);
    d->m_btnBox = new QDialogButtonBox(this);
    d->m_btnBox->setStandardButtons(QDialogButtonBox::Abort);
    d->m_progressBar = new QProgressBar(this);
    d->m_progressBar->setValue(0);
    d->m_progressBar->setTextVisible(false);

    QBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(d->m_waitLabel);
    layout->addWidget(d->m_progressBar);
    layout->addWidget(d->m_btnBox);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Configure
    this->setWindowModality(Qt::ApplicationModal);
    QObject::connect(d->m_updateTimer, &QTimer::timeout, this, &WaitDialog::updateProgress);
    d->m_updateTimer->setInterval(500);
}

WaitDialog::~WaitDialog()
{
    if (this->isWaiting())
        this->stopWait();
    delete d;
}

bool WaitDialog::isWaiting() const
{
    return d->m_updateTimer->isActive();
}

void WaitDialog::setWaitLabel(const QString& text)
{
    d->m_waitLabel->setText(text);
}

void WaitDialog::setMinimumDuration(int msecs)
{
    d->m_minDuration = msecs;
}

void WaitDialog::startWait()
{
    if (this->isWaiting())
        return;
    d->m_progressBar->setValue(0);
    d->m_updateTimer->start();
}

void WaitDialog::stopWait()
{
    d->m_updateTimer->stop();
    this->close();
}

void WaitDialog::updateProgress()
{
    const int incr = 5;
    const int currValue = d->m_progressBar->value();
    const int newValue =
            currValue + incr <= d->m_progressBar->maximum() ?
                currValue + incr :
                d->m_progressBar->minimum();
    d->m_progressBar->setValue(newValue);
    const int timeSinceStart = (newValue / incr) * d->m_updateTimer->interval();
    if (timeSinceStart >= d->m_minDuration && !this->isVisible())
        this->show();
    QApplication::processEvents();
}

} // namespace qtgui

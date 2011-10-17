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

#include "qttools/gui/wait_dialog.h"

#include "qttools/core/task.h"
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtGui/QApplication>
#include <QtGui/QBoxLayout>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>

namespace qttools {

class WaitDialogPrivate
{
public:
  WaitDialogPrivate(WaitDialog* parent)
    : waitLabel(0),
      progressBar(0),
      btnBox(0),
      updateTimer(new QTimer(parent)),
      minDuration(1000)
  {
  }

  QLabel* waitLabel;
  QProgressBar* progressBar;
  QDialogButtonBox* btnBox;
  QTimer* updateTimer;
  int minDuration;
};


WaitDialog::WaitDialog(QWidget* parent)
  : QDialog(parent),
    _d(new WaitDialogPrivate(this))
{
  // Create the UI
  this->setObjectName("qttools__WaitDialog");
  this->setWindowTitle(tr("Waiting"));
  this->resize(170, 60);

  _d->waitLabel = new QLabel(this);
  _d->btnBox = new QDialogButtonBox(this);
  _d->btnBox->setStandardButtons(QDialogButtonBox::Abort);
  _d->progressBar = new QProgressBar(this);
  _d->progressBar->setValue(0);
  _d->progressBar->setTextVisible(false);

  QBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(_d->waitLabel);
  layout->addWidget(_d->progressBar);
  layout->addWidget(_d->btnBox);
  layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
  // Configure
  this->setWindowModality(Qt::ApplicationModal);
  connect(_d->updateTimer, SIGNAL(timeout()), this, SLOT(updateProgress()));
  _d->updateTimer->setInterval(500);
}

WaitDialog::~WaitDialog()
{
  if (this->isWaiting())
    this->stopWait();
  delete _d;
}

bool WaitDialog::isWaiting() const
{
  return _d->updateTimer->isActive();
}

void WaitDialog::setWaitLabel(const QString& text)
{
  _d->waitLabel->setText(text);
}

void WaitDialog::setMinimumDuration(int msecs)
{
  _d->minDuration = msecs;
}

void WaitDialog::startWait()
{
  if (this->isWaiting())
    return;
  _d->progressBar->setValue(0);
  _d->updateTimer->start();
}

void WaitDialog::stopWait()
{
  _d->updateTimer->stop();
  this->close();
}

void WaitDialog::waitFor(qttools::Task* task, WaitForOption opt)
{
  QThread* taskThread = new QThread;
  task->bindToThread(taskThread);
  QEventLoop eventLoop;
  connect(taskThread, SIGNAL(started()), this, SLOT(startWait()));
  connect(taskThread, SIGNAL(finished()), this, SLOT(stopWait()));
  connect(taskThread, SIGNAL(finished()), &eventLoop, SLOT(quit()));
  connect(_d->btnBox, SIGNAL(rejected()), task, SLOT(stop()));
  taskThread->start();
  eventLoop.exec();
  if (opt == WaitDialog::DeleteTaskOption)
    delete task;
}

void WaitDialog::updateProgress()
{
  const int incr = 5;
  const int currValue = _d->progressBar->value();
  const int newValue =
      currValue + incr <= _d->progressBar->maximum() ?
        currValue + incr : _d->progressBar->minimum();
  _d->progressBar->setValue(newValue);
  const int timeSinceStart = (newValue / incr) * _d->updateTimer->interval();
  if (timeSinceStart >= _d->minDuration && !this->isVisible())
    this->show();
  QApplication::processEvents();
}

} // namespace qttools

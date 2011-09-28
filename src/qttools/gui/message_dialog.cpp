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

#include "qttools/gui/message_dialog.h"

#include <QtCore/QSignalMapper>
#include <QtGui/QAbstractButton>
#include <QtGui/QApplication>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QStyle>

namespace qttools {

MessageDialog::MessageDialog(Icon icon,
                             const QString& title,
                             const QString& text,
                             QDialogButtonBox::StandardButtons buttons,
                             QWidget* parent) :
  QDialog(parent),
  _textLabel(new QLabel(text, this)),
  _detailsWidget(new QWidget(this))
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
  layout->addWidget(_textLabel, 0, 1);
  layout->addWidget(_detailsWidget, 1, 1);
  layout->addWidget(btnBox, 2, 0, 1, 2, Qt::AlignRight);
  this->setLayout(layout);

  QSignalMapper* sigMapper = new QSignalMapper(this);
  foreach (QAbstractButton* btn, btnBox->buttons()) {
    sigMapper->setMapping(btn, btnBox->standardButton(btn));
    connect(btn, SIGNAL(clicked()), sigMapper, SLOT(map()));
  }
  connect(sigMapper, SIGNAL(mapped(int)), this, SLOT(done(int)));
}

void MessageDialog::setDetailsWidget(QWidget* widget)
{
  if (widget == 0)
    return;
  widget->setParent(_detailsWidget);
  QBoxLayout* layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->addWidget(widget);
  _detailsWidget->setLayout(layout);
}

} // namespace qttools

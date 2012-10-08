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

#include "view_item_button_mechanism.h"

#include <QtCore/QtDebug>
#include <QtGui/QAbstractItemView>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QToolTip>

namespace qttools {

/*! \class ViewItemButtonMechanismPrivate
 *  \brief Internal (pimpl of ViewItemButtonMechanism)
 */

class ViewItemButtonMechanismPrivate
{
public:
  struct ButtonInfo
  {
    QIcon icon;
    QString toolTip;
    bool isOverButton;
    int matchRole;
    QVariant matchData;
    int displayColumn;
    ViewItemButtonMechanism::ItemSide itemSide;
  };

  ViewItemButtonMechanismPrivate(ViewItemButtonMechanism* backPtr);

  ButtonInfo buttonInfo(int btnId) const;
  ButtonInfo* mutableButtonInfo(int btnId);
  void setAllIsOverButtonState(bool on);
  QModelIndex modelIndexForButtonDisplay(const QModelIndex& index) const;
  void itemViewUpdateAt(const QModelIndex& index);

  QAbstractItemView* m_view;
  QHash<int, ButtonInfo> m_btnInfos;
  QModelIndex m_prevModelIndexUnderMouse;

private:
  ViewItemButtonMechanism* m_backPtr;
};

ViewItemButtonMechanismPrivate::ViewItemButtonMechanismPrivate(ViewItemButtonMechanism *backPtr)
  : m_view(nullptr),
    m_backPtr(backPtr)
{
}

ViewItemButtonMechanismPrivate::ButtonInfo ViewItemButtonMechanismPrivate::buttonInfo(int btnId) const
{
  return m_btnInfos.value(btnId);
}

ViewItemButtonMechanismPrivate::ButtonInfo *ViewItemButtonMechanismPrivate::mutableButtonInfo(int btnId)
{
  if (m_btnInfos.contains(btnId))
    return &(m_btnInfos[btnId]);
  return nullptr;
}

void ViewItemButtonMechanismPrivate::setAllIsOverButtonState(bool on)
{
  foreach (int id, m_btnInfos.keys())
    this->mutableButtonInfo(id)->isOverButton = on;
}

QModelIndex ViewItemButtonMechanismPrivate::modelIndexForButtonDisplay(const QModelIndex &index) const
{
  const int btnIndex = m_backPtr->buttonAtModelIndex(index);
  if (m_btnInfos.contains(btnIndex) && this->buttonInfo(btnIndex).displayColumn != -1)
    return index.sibling(index.row(), this->buttonInfo(btnIndex).displayColumn);
  return index;
}

void ViewItemButtonMechanismPrivate::itemViewUpdateAt(const QModelIndex &index)
{
  const QModelIndex displayIndex = this->modelIndexForButtonDisplay(index);
  if (index.isValid())
    m_view->update(index);
  if (displayIndex != index && displayIndex.isValid())
    m_view->update(displayIndex);
}

/*! \class ViewItemButtonMechanism
 *  \brief Provides buttons integrated to items displayed by QAbstractItemView
 */

ViewItemButtonMechanism::ViewItemButtonMechanism(QAbstractItemView* view, QObject *parent)
  : QObject(parent),
    d(new ViewItemButtonMechanismPrivate(this))
{
  d->m_view = view;
  if (view != nullptr) {
    view->viewport()->setMouseTracking(true);
    view->viewport()->installEventFilter(this);
  }
}

ViewItemButtonMechanism::~ViewItemButtonMechanism()
{
  delete d;
}

QAbstractItemView* ViewItemButtonMechanism::itemView() const
{
  return d->m_view;
}

void ViewItemButtonMechanism::reset()
{
  d->m_prevModelIndexUnderMouse = QModelIndex();
}

bool ViewItemButtonMechanism::eventFilter(QObject *object, QEvent *event)
{
  if (object == this->itemView()->viewport()) {
    const QMouseEvent* mouseEvent = dynamic_cast<const QMouseEvent*>(event);
    const QModelIndex modelIndexUnderMouse =
        mouseEvent != nullptr ? this->itemView()->indexAt(mouseEvent->pos()) :
                                QModelIndex();
    switch (event->type()) {
    case QEvent::MouseMove: {
      if (d->m_prevModelIndexUnderMouse != modelIndexUnderMouse)
        d->itemViewUpdateAt(d->m_prevModelIndexUnderMouse);
      d->itemViewUpdateAt(modelIndexUnderMouse);
      d->m_prevModelIndexUnderMouse = modelIndexUnderMouse;
      return true;
    }
    case QEvent::MouseButtonRelease: {
      if (mouseEvent->button() != Qt::LeftButton)
        return false;

      foreach (int btnIndex, d->m_btnInfos.keys()) {
        if (d->m_btnInfos.value(btnIndex).isOverButton) {
          emit buttonClicked(btnIndex, modelIndexUnderMouse);
          return true;
        }
      }
      return false;
    }
    case QEvent::ToolTip: {
      QString toolTip;
      foreach (int btnIndex, d->m_btnInfos.keys()) {
        if (d->m_btnInfos.value(btnIndex).isOverButton) {
          toolTip = d->m_btnInfos.value(btnIndex).toolTip;
          break;
        }
      }

      if (!toolTip.isEmpty()) {
        QToolTip::showText(QCursor::pos(), toolTip, this->itemView());
        return true;
      }

      return false;
    }
    default:
      break;
    }
  }

  return false;
}

void ViewItemButtonMechanism::paint(QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index)
{
  bool mouseIsOver = false;
  if (painter != nullptr) {
    QWidget* w = dynamic_cast<QWidget*>(painter->device());
    if (w != nullptr) {
      QPoint mousePos = QCursor::pos();
      QPoint wMousePos = w->mapFromGlobal(mousePos);
      mouseIsOver = option.rect.contains(wMousePos);
    }
  }

//  QStyledItemDelegate::paint(painter, option, index);

  if (this->itemView()->isEnabled()) {
    const int pixWidth = option.rect.height();
    const int pixHeight = option.rect.height();

    QStyleOptionViewItemV4 optionForBtn(option);
    optionForBtn.rect = this->itemView()->visualRect(d->modelIndexForButtonDisplay(index));

    if (mouseIsOver) {
      const int btnIndex = this->buttonAtModelIndex(index);
      if (d->m_btnInfos.contains(btnIndex)) {
        const ViewItemButtonMechanismPrivate::ButtonInfo btnInfo = d->m_btnInfos.value(btnIndex);
        QRect pixRect;
        if (btnInfo.itemSide == ItemLeftSide) {
          pixRect = QRect(optionForBtn.rect.left() + 2, optionForBtn.rect.top(),
                          pixWidth, pixHeight);
        }
        else {
          pixRect = QRect(optionForBtn.rect.right() - pixWidth - 2, optionForBtn.rect.top(),
                          pixWidth, pixHeight);
        }

        const bool isInsideButtonRegion =
            pixRect.contains(this->itemView()->viewport()->mapFromGlobal(QCursor::pos()));
        const QIcon icon = btnInfo.icon;
        const QPixmap pix = icon.pixmap(pixWidth, pixHeight, isInsideButtonRegion ? QIcon::Active :
                                                                                    QIcon::Normal);
        painter->drawPixmap(pixRect, pix);

        d->setAllIsOverButtonState(false);
        d->mutableButtonInfo(btnIndex)->isOverButton = isInsideButtonRegion;
      }
    }
    else {
      painter->fillRect(optionForBtn.rect, optionForBtn.backgroundBrush);
    }
  }
  else  {
    d->setAllIsOverButtonState(false);
  }
}

void ViewItemButtonMechanism::addButton(int btnId, const QIcon &icon, const QString &toolTip)
{
  ViewItemButtonMechanismPrivate::ButtonInfo info;
  info.icon = icon;
  info.toolTip = toolTip;
  info.isOverButton = false;
  info.matchRole = Qt::UserRole + 1;
  info.displayColumn = -1;
  info.itemSide = ItemRightSide;
  d->m_btnInfos.insert(btnId, info);
}

void ViewItemButtonMechanism::setButtonDetection(int btnId, int matchRole, const QVariant &matchData)
{
  if (d->m_btnInfos.contains(btnId)) {
    d->mutableButtonInfo(btnId)->matchRole = matchRole;
    d->mutableButtonInfo(btnId)->matchData = matchData;
  }
}

void ViewItemButtonMechanism::setButtonDisplayColumn(int btnId, int col)
{
  if (d->m_btnInfos.contains(btnId))
    d->mutableButtonInfo(btnId)->displayColumn = col;
}

void ViewItemButtonMechanism::setButtonItemSide(int btnId, ItemSide side)
{
  if (d->m_btnInfos.contains(btnId))
    d->mutableButtonInfo(btnId)->itemSide = side;
}

int ViewItemButtonMechanism::buttonAtModelIndex(const QModelIndex &index) const
{
  foreach (int id, d->m_btnInfos.keys()) {
    const ViewItemButtonMechanismPrivate::ButtonInfo btnInfo = d->m_btnInfos.value(id);
    const QVariant modelItemData = index.data(btnInfo.matchRole);
    if ((!btnInfo.matchData.isNull() && btnInfo.matchData.isValid())
        && (!modelItemData.isNull() && modelItemData.isValid())
        && (btnInfo.matchData == modelItemData))
    {
      return id;
    }
  }
  return -1;
}

} // namespace qttools

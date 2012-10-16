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
    int index;
    QIcon icon;
    QString toolTip;
    int matchRole;
    QVariant matchData;
    int displayColumn;
    ViewItemButtonMechanism::ItemSide itemSide;
    ViewItemButtonMechanism::DisplayMode itemDisplayMode;
  };

  ViewItemButtonMechanismPrivate(ViewItemButtonMechanism* backPtr);

  const ButtonInfo* buttonInfo(int btnId) const;
  ButtonInfo* mutableButtonInfo(int btnId);
  void setAllIsOverButtonState(bool on);
  QModelIndex modelIndexForButtonDisplay(const QModelIndex& index) const;
  void itemViewUpdateAt(const QModelIndex& index);
  void paintButton(ButtonInfo *btnInfo,
                   QPainter* painter,
                   const QStyleOptionViewItem& option);
  void resetButtonUnderMouseState();

  QAbstractItemView* m_view;
  QHash<int, ButtonInfo> m_btnInfos;
  QModelIndex m_prevModelIndexUnderMouse;
  const ButtonInfo* m_buttonUnderMouse;

private:
  ViewItemButtonMechanism* m_backPtr;
};

ViewItemButtonMechanismPrivate::ViewItemButtonMechanismPrivate(ViewItemButtonMechanism *backPtr)
  : m_view(0),
    m_buttonUnderMouse(0),
    m_backPtr(backPtr)
{
}

const ViewItemButtonMechanismPrivate::ButtonInfo *ViewItemButtonMechanismPrivate::buttonInfo(int btnId) const
{
  const QHash<int, ButtonInfo>::ConstIterator iBtnInfo = m_btnInfos.find(btnId);
  if (iBtnInfo != m_btnInfos.constEnd())
    return &(iBtnInfo.value());
  return 0;
}

ViewItemButtonMechanismPrivate::ButtonInfo *ViewItemButtonMechanismPrivate::mutableButtonInfo(int btnId)
{
  QHash<int, ButtonInfo>::Iterator iBtnInfo = m_btnInfos.find(btnId);
  if (iBtnInfo != m_btnInfos.end())
    return &(iBtnInfo.value());
  return 0;
}

QModelIndex ViewItemButtonMechanismPrivate::modelIndexForButtonDisplay(const QModelIndex &index) const
{
  const int btnIndex = m_backPtr->buttonAtModelIndex(index);
  const ViewItemButtonMechanismPrivate::ButtonInfo* btnInfo = this->buttonInfo(btnIndex);
  if (btnInfo != 0 && btnInfo->displayColumn != -1)
    return index.sibling(index.row(), btnInfo->displayColumn);
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

void ViewItemButtonMechanismPrivate::paintButton(ButtonInfo *btnInfo,
                                                 QPainter *painter,
                                                 const QStyleOptionViewItem &option)
{
  if (btnInfo == 0 || painter == 0)
    return;

  const int pixWidth = option.rect.height();
  const int pixHeight = option.rect.height();

  QRect pixRect;
  if (btnInfo->itemSide == ViewItemButtonMechanism::ItemLeftSide)
    pixRect = QRect(option.rect.left() + 2, option.rect.top(), pixWidth, pixHeight);
  else
    pixRect = QRect(option.rect.right() - pixWidth - 2, option.rect.top(), pixWidth, pixHeight);

  const bool isInsideButtonRegion =
      pixRect.contains(m_view->viewport()->mapFromGlobal(QCursor::pos()));
  const QIcon icon = btnInfo->icon;
  const QPixmap pix = icon.pixmap(pixWidth, pixHeight, isInsideButtonRegion ? QIcon::Active :
                                                                              QIcon::Normal);
  painter->drawPixmap(pixRect, pix);

  if (isInsideButtonRegion)
    m_buttonUnderMouse = btnInfo;
}

void ViewItemButtonMechanismPrivate::resetButtonUnderMouseState()
{
  m_buttonUnderMouse = 0;
}

/*! \class ViewItemButtonMechanism
 *  \brief Provides buttons integrated to items displayed by QAbstractItemView
 */

ViewItemButtonMechanism::ViewItemButtonMechanism(QAbstractItemView* view, QObject *parent)
  : QObject(parent),
    d(new ViewItemButtonMechanismPrivate(this))
{
  d->m_view = view;
  if (view != 0) {
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
  d->resetButtonUnderMouseState();
}

bool ViewItemButtonMechanism::eventFilter(QObject *object, QEvent *event)
{
  if (object == this->itemView()->viewport()) {
    const QMouseEvent* mouseEvent = dynamic_cast<const QMouseEvent*>(event);
    const QModelIndex modelIndexUnderMouse =
        mouseEvent != 0 ? this->itemView()->indexAt(mouseEvent->pos()) :
                          QModelIndex();
    switch (event->type()) {
    case QEvent::MouseMove: {
      d->resetButtonUnderMouseState();
      if (d->m_prevModelIndexUnderMouse != modelIndexUnderMouse)
        d->itemViewUpdateAt(d->m_prevModelIndexUnderMouse);
      d->itemViewUpdateAt(modelIndexUnderMouse);
      d->m_prevModelIndexUnderMouse = modelIndexUnderMouse;
      return true;
    }
    case QEvent::MouseButtonRelease: {
      if (mouseEvent->button() != Qt::LeftButton)
        return false;

      if (d->m_buttonUnderMouse != 0)
      {
        emit buttonClicked(d->m_buttonUnderMouse->index, modelIndexUnderMouse);
        return true;
      }
      return false;
    }
    case QEvent::ToolTip: {
      const QString toolTip = d->m_buttonUnderMouse != 0 ? d->m_buttonUnderMouse->toolTip :
                                                           QString();
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
  if (painter != 0) {
    QWidget* w = dynamic_cast<QWidget*>(painter->device());
    if (w != 0) {
      QPoint mousePos = QCursor::pos();
      QPoint wMousePos = w->mapFromGlobal(mousePos);
      mouseIsOver = option.rect.contains(wMousePos);
    }
  }

  //  QStyledItemDelegate::paint(painter, option, index);

  if (this->itemView()->isEnabled()) {
    QStyleOptionViewItemV4 optionForBtn(option);
    optionForBtn.rect = this->itemView()->visualRect(d->modelIndexForButtonDisplay(index));
    const int btnIndex = this->buttonAtModelIndex(index);
    ViewItemButtonMechanismPrivate::ButtonInfo* btnInfo = d->mutableButtonInfo(btnIndex);
    const int dispMode = btnInfo != 0 ? btnInfo->itemDisplayMode : -1;
    switch (dispMode) {
    case DisplayPermanent: {
      d->paintButton(btnInfo, painter, optionForBtn);
      break;
    }
    case DisplayOnDetection: {
      if (mouseIsOver)
        d->paintButton(btnInfo, painter, optionForBtn);
      else
        painter->fillRect(optionForBtn.rect, optionForBtn.backgroundBrush);
      break;
    }
    default:
      break;
    }
  }
  else {
    d->resetButtonUnderMouseState();
    //    d->setAllIsOverButtonState(false);
  }
}

void ViewItemButtonMechanism::addButton(int btnId, const QIcon &icon, const QString &toolTip)
{
  if (d->m_btnInfos.contains(btnId)) {
    qWarning() << QString("%1 : there is already a button of index '%2'").arg(btnId);
    return;
  }

  ViewItemButtonMechanismPrivate::ButtonInfo info;
  info.index = btnId;
  info.icon = icon;
  info.toolTip = toolTip;
  info.matchRole = Qt::UserRole + 1;
  info.displayColumn = -1;
  info.itemSide = ItemRightSide;
  info.itemDisplayMode = DisplayOnDetection;
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

void ViewItemButtonMechanism::setButtonDisplayMode(int btnId, DisplayMode mode)
{
  if (d->m_btnInfos.contains(btnId))
    d->mutableButtonInfo(btnId)->itemDisplayMode = mode;
}

int ViewItemButtonMechanism::buttonAtModelIndex(const QModelIndex &index) const
{
  foreach (int id, d->m_btnInfos.keys()) {
    const ViewItemButtonMechanismPrivate::ButtonInfo* btnInfo = d->buttonInfo(id);
    const QVariant modelItemData = index.data(btnInfo->matchRole);
    if ((!btnInfo->matchData.isNull() && btnInfo->matchData.isValid())
        && (!modelItemData.isNull() && modelItemData.isValid())
        && (btnInfo->matchData == modelItemData))
    {
      return id;
    }
  }
  return -1;
}

} // namespace qttools

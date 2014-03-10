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

#include "item_view_buttons.h"

#include "proxy_styled_item_delegate.h"

#include <QtCore/QtDebug>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
// QtWidgets
#include <QAbstractItemView>
#include <QToolTip>
#include <QStyledItemDelegate>

#include "../../cpptools/memory_utils.h"

namespace qttools {

/*! \class ItemViewButtonsPrivate
 *  \brief Internal (pimpl of ItemViewButtons)
 */

class ItemViewButtons::Private
{
public:
  class ProxyItemDelegate : public ProxyStyledItemDelegate
  {
  public:
    ProxyItemDelegate(const ItemViewButtons* itemBtns,
                      QStyledItemDelegate* srcDelegate,
                      QObject* parent = NULL);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

  private:
    const ItemViewButtons* m_itemBtns;
  };

  struct ButtonInfo
  {
    int index;
    QIcon icon;
    QSize iconSize;
    QString toolTip;
    int matchRole;
    QVariant matchData;
    int displayColumn;
    ItemViewButtons::ItemSide itemSide;
    ItemViewButtons::DisplayModes itemDisplayModes;
  };

  Private(ItemViewButtons* backPtr);

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
  ItemViewButtons* m_backPtr;
};

ItemViewButtons::Private::ProxyItemDelegate::ProxyItemDelegate(const ItemViewButtons *itemBtns,
                                                               QStyledItemDelegate *srcDelegate,
                                                               QObject* parent)
  : ProxyStyledItemDelegate(srcDelegate, parent),
    m_itemBtns(itemBtns)
{
}

void ItemViewButtons::Private::ProxyItemDelegate::paint(QPainter *painter,
                                                        const QStyleOptionViewItem &option,
                                                        const QModelIndex &index) const
{
  ProxyStyledItemDelegate::paint(painter, option, index);
  if (m_itemBtns != NULL)
    m_itemBtns->paint(painter, option, index);
}

ItemViewButtons::Private::Private(ItemViewButtons *backPtr)
  : m_view(NULL),
    m_buttonUnderMouse(NULL),
    m_backPtr(backPtr)
{
}

const ItemViewButtons::Private::ButtonInfo*
ItemViewButtons::Private::buttonInfo(int btnId) const
{
  const QHash<int, ButtonInfo>::ConstIterator iBtnInfo = m_btnInfos.find(btnId);
  if (iBtnInfo != m_btnInfos.constEnd())
    return &(iBtnInfo.value());
  return NULL;
}

ItemViewButtons::Private::ButtonInfo*
ItemViewButtons::Private::mutableButtonInfo(int btnId)
{
  QHash<int, ButtonInfo>::Iterator iBtnInfo = m_btnInfos.find(btnId);
  if (iBtnInfo != m_btnInfos.end())
    return &(iBtnInfo.value());
  return NULL;
}

QModelIndex ItemViewButtons::Private::modelIndexForButtonDisplay(const QModelIndex &index) const
{
  const int btnIndex = m_backPtr->buttonAtModelIndex(index);
  const ItemViewButtons::Private::ButtonInfo* btnInfo = this->buttonInfo(btnIndex);
  if (btnInfo != NULL && btnInfo->displayColumn != -1)
    return index.sibling(index.row(), btnInfo->displayColumn);
  return index;
}

void ItemViewButtons::Private::itemViewUpdateAt(const QModelIndex &index)
{
  const QModelIndex displayIndex = this->modelIndexForButtonDisplay(index);
  if (index.isValid())
    m_view->update(index);
  if (displayIndex != index && displayIndex.isValid())
    m_view->update(displayIndex);
}

void ItemViewButtons::Private::paintButton(ButtonInfo *btnInfo,
                                           QPainter *painter,
                                           const QStyleOptionViewItem &option)
{
  if (btnInfo == NULL || painter == NULL)
    return;

  const bool isValidBtnIconSize = btnInfo->iconSize.isValid();
  const int pixWidth = isValidBtnIconSize ? btnInfo->iconSize.width() : option.rect.height();
  const int pixHeight = isValidBtnIconSize ? btnInfo->iconSize.height() : option.rect.height();

  QRect pixRect;
  const int yPixPos = option.rect.top() + (option.rect.height() - pixHeight) / 2;
  if (btnInfo->itemSide == ItemViewButtons::ItemLeftSide)
    pixRect = QRect(option.rect.left() + 2, yPixPos, pixWidth, pixHeight);
  else
    pixRect = QRect(option.rect.right() - pixWidth - 2, yPixPos, pixWidth, pixHeight);

  const bool isInsideButtonRegion =
      pixRect.contains(m_view->viewport()->mapFromGlobal(QCursor::pos()));
  const QIcon icon = btnInfo->icon;
  const QPixmap pix = icon.pixmap(pixWidth, pixHeight, isInsideButtonRegion ? QIcon::Active :
                                                                              QIcon::Normal);
  painter->drawPixmap(pixRect, pix);

  if (isInsideButtonRegion)
    m_buttonUnderMouse = btnInfo;
}

void ItemViewButtons::Private::resetButtonUnderMouseState()
{
  m_buttonUnderMouse = NULL;
}

/*!
 * \class ItemViewButtons
 * \brief Provides buttons integrated to items displayed by QAbstractItemView
 *
 * Example:
 * \code
 *   // Let's suppose we have some demo tabular data with a "Customer" column
 *   // We want to allow the user to delete customers through a button integrated to the view item
 *   // that shows up when the mouse is over a "customer" model item
 *
 *   static const int customerItemTag = 100;
 *
 *   QStandardItemModel* model = ...;
 *   QStandardItem* customerItem = new QStandardItem;
 *   customerItem->setData(customerItemTag, Qt::UserRole + 1);
 *   // Add more items ...
 *
 *   QTableView* tableView = ...;
 *   tableView->setModel(model);
 *
 *   qttools::ItemViewButtons* tableBtns = new qttools::ItemViewButtons(tableView);
 *
 *   QIcon deleteCustomerIcon(":/images/delete.png");
 *   deleteCustomerIcon.addPixmap(QPixmap(":/images/delete__active.png"), QIcon::Active);
 *   tableBtns->addButton(1, deleteCustomerIcon, tr("Delete customer"));
 *   tableBtns->setButtonDetection(1, Qt::UserRole + 1, customerItemTag);
 *   tableBtns->setButtonDisplayColumn(1, 0); // If "Customer" is in column 0
 *   tableBtns->setButtonDisplayModes(1, ItemViewButtons::DisplayOnDetection);
 *   tableBtns->setButtonToolTip(1, tr("Delete this customer"));
 *
 *   tableBtns->installDefaultItemDelegate();
 *
 * \endcode
 *
 * \headerfile item_view_buttons.h <qttools/gui/item_view_buttons.h>
 * \ingroup qttools_gui
 */

ItemViewButtons::ItemViewButtons(QAbstractItemView* view, QObject *parent)
  : QObject(parent),
    d(new Private(this))
{
  d->m_view = view;
  if (view != NULL) {
    view->viewport()->setMouseTracking(true);
    view->viewport()->installEventFilter(this);
  }
}

ItemViewButtons::~ItemViewButtons()
{
  delete d;
}

QAbstractItemView* ItemViewButtons::itemView() const
{
  return d->m_view;
}

void ItemViewButtons::reset()
{
  d->m_prevModelIndexUnderMouse = QModelIndex();
  d->resetButtonUnderMouseState();
}

bool ItemViewButtons::eventFilter(QObject *object, QEvent *event)
{
  if (object == this->itemView()->viewport()) {
    const QMouseEvent* mouseEvent = dynamic_cast<const QMouseEvent*>(event);
    const QModelIndex modelIndexUnderMouse =
        mouseEvent != NULL ? this->itemView()->indexAt(mouseEvent->pos()) :
                             QModelIndex();
    switch (event->type()) {
    case QEvent::Leave:
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

      if (d->m_buttonUnderMouse != NULL) {
        emit buttonClicked(d->m_buttonUnderMouse->index, modelIndexUnderMouse);
        return true;
      }
      return false;
    }
    case QEvent::ToolTip: {
      const QString toolTip = d->m_buttonUnderMouse != NULL ? d->m_buttonUnderMouse->toolTip :
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

void ItemViewButtons::paint(QPainter *painter,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{
  bool mouseIsOver = false;
  if (painter != NULL) {
    QWidget* w = dynamic_cast<QWidget*>(painter->device());
    if (w != NULL) {
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
    Private::ButtonInfo* btnInfo = d->mutableButtonInfo(btnIndex);
    if (btnInfo == NULL)
      return;

    // Check if button can be displayed
    if (btnInfo->itemDisplayModes.testFlag(DisplayWhenItemSelected)
        && !option.state.testFlag(QStyle::State_Selected))
    {
      //      painter->fillRect(optionForBtn.rect, optionForBtn.backgroundBrush);
      return;
    }

    if (btnInfo->itemDisplayModes.testFlag(DisplayPermanent)) {
      d->paintButton(btnInfo, painter, optionForBtn);
    }
    else if (btnInfo->itemDisplayModes.testFlag(DisplayOnDetection)) {
      if (mouseIsOver)
        d->paintButton(btnInfo, painter, optionForBtn);
      else
        painter->fillRect(optionForBtn.rect, optionForBtn.backgroundBrush);
    }
  }
  else {
    d->resetButtonUnderMouseState();
    //    d->setAllIsOverButtonState(false);
  }
}

/*!
 * \brief Add a button to be furthered configured with setButtonXxx() functions
 * \param btnId Index of the button (used later to reference the button)
 * \param icon Icon of the button (ItemViewButtons supports QIcon:::Active which can be used
 *             to display an highlighted pixmap when the mouse is hovering the button)
 * \param toolTip Tool-tip to be displayed when the mouse stays over the button
 *
 *  Does nothing if button index \p btnId is already used by some other button.
 */
void ItemViewButtons::addButton(int btnId, const QIcon &icon, const QString &toolTip)
{
  if (d->m_btnInfos.contains(btnId)) {
    qWarning() << QString("%1 : there is already a button of index '%2'").arg(Q_FUNC_INFO).arg(btnId);
    return;
  }

  Private::ButtonInfo info;
  info.index = btnId;
  info.icon = icon;
  info.toolTip = toolTip;
  info.matchRole = Qt::UserRole + 1;
  info.displayColumn = -1;
  info.itemSide = ItemRightSide;
  info.itemDisplayModes = DisplayOnDetection;
  d->m_btnInfos.insert(btnId, info);
}

/*!
 * \brief Copy all properties of a button into another
 * \param srcBtnId Index of the source button
 * \param dstBtnId Index of the destination button
 */
void ItemViewButtons::copyButtonProperties(int srcBtnId, int dstBtnId)
{
  if (srcBtnId == dstBtnId)
    return;

  const Private::ButtonInfo* srcBtnInfo = d->buttonInfo(srcBtnId);
  Private::ButtonInfo* dstBtnInfo = d->mutableButtonInfo(dstBtnId);

  if (srcBtnInfo != NULL) {
    if (dstBtnInfo != NULL) {
      *dstBtnInfo = *srcBtnInfo;
      dstBtnInfo->index = dstBtnId; // Restore destination button index
    }
    else {
      qWarning() << QString("%1 : no destination button of index '%1'").arg(Q_FUNC_INFO).arg(dstBtnId);
    }
  }
  else {
    qWarning() << QString("%1 : no source button of index '%1'").arg(Q_FUNC_INFO).arg(srcBtnId);
  }
}

/*!
 * \brief The role used when matching item data for button detection
 * \param btnId Index of the button
 * \returns -1 If button does not exist
 * \sa buttonDetectionMatchData()
 */
int ItemViewButtons::buttonDetectionMatchRole(int btnId) const
{
  const Private::ButtonInfo* btnInfo = d->buttonInfo(btnId);
  return btnInfo != NULL ? btnInfo->matchRole : -1;
}

/*!
 * \brief The data to be matched for button detection
 * \param btnId Index of the button
 * \returns QVariant() If button does not exist
 */
QVariant ItemViewButtons::buttonDetectionMatchData(int btnId) const
{
  const Private::ButtonInfo* btnInfo = d->buttonInfo(btnId);
  return btnInfo != NULL ? btnInfo->matchData : QVariant();
}

void ItemViewButtons::setButtonDetection(int btnId, int matchRole, const QVariant &matchData)
{
  Private::ButtonInfo* btnInfo = d->mutableButtonInfo(btnId);
  if (btnInfo != NULL) {
    btnInfo->matchRole = matchRole;
    btnInfo->matchData = matchData;
  }
}

/*!
 * \brief Index of the view column where the button is displayed (when detected)
 * \param btnId Index of the button
 * \returns -1 If button does not exist
 */
int ItemViewButtons::buttonDisplayColumn(int btnId) const
{
  const Private::ButtonInfo* btnInfo = d->buttonInfo(btnId);
  return btnInfo != NULL ? btnInfo->displayColumn : -1;
}

void ItemViewButtons::setButtonDisplayColumn(int btnId, int col)
{
  cpp::checkedAssign(&Private::ButtonInfo::displayColumn, d->mutableButtonInfo(btnId), col);
}

/*!
 * \brief Side in the item's cell where the button is displayed
 * \param btnId Index of the button
 * \returns -1 If button does not exist
 */
int ItemViewButtons::buttonItemSide(int btnId) const
{
  const Private::ButtonInfo* btnInfo = d->buttonInfo(btnId);
  return btnInfo != NULL ? btnInfo->itemSide : -1;
}

void ItemViewButtons::setButtonItemSide(int btnId, ItemSide side)
{
  cpp::checkedAssign(&Private::ButtonInfo::itemSide, d->mutableButtonInfo(btnId), side);
}

/*!
 * \brief Display modes of the button
 * \param btnId Index of the button
 * \returns DisplayModes() If button does not exist
 */
ItemViewButtons::DisplayModes ItemViewButtons::buttonDisplayModes(int btnId) const
{
  const Private::ButtonInfo* btnInfo = d->buttonInfo(btnId);
  return btnInfo != NULL ? btnInfo->itemDisplayModes : DisplayModes();
}

void ItemViewButtons::setButtonDisplayModes(int btnId, DisplayModes modes)
{
  cpp::checkedAssign(&Private::ButtonInfo::itemDisplayModes, d->mutableButtonInfo(btnId), modes);
}

/*!
 * \brief Icon of the button
 * \param btnId Index of the button
 * \returns QIcon() If button does not exist
 */
QIcon ItemViewButtons::buttonIcon(int btnId) const
{
  const Private::ButtonInfo* btnInfo = d->buttonInfo(btnId);
  return btnInfo != NULL ? btnInfo->icon : QIcon();
}

void ItemViewButtons::setButtonIcon(int btnId, const QIcon &icon)
{
  cpp::checkedAssign(&Private::ButtonInfo::icon, d->mutableButtonInfo(btnId), icon);
}

/*!
 * \brief Icon size of the button
 * \param btnId Index of the button
 * \returns QSize() If button does not exist
 */
QSize ItemViewButtons::buttonIconSize(int btnId) const
{
  const Private::ButtonInfo* btnInfo = d->buttonInfo(btnId);
  return btnInfo != NULL ? btnInfo->iconSize : QSize();
}

void ItemViewButtons::setButtonIconSize(int btnId, const QSize &size)
{
  cpp::checkedAssign(&Private::ButtonInfo::iconSize, d->mutableButtonInfo(btnId), size);
}

/*!
 * \brief Tool-tip of the button
 * \param btnId Index of the button
 * \returns QString() If button does not exist
 */
QString ItemViewButtons::buttonToolTip(int btnId) const
{
  const Private::ButtonInfo* btnInfo = d->buttonInfo(btnId);
  return btnInfo != NULL ? btnInfo->toolTip : QString();
}

void ItemViewButtons::setButtonToolTip(int btnId, const QString &toolTip)
{
  cpp::checkedAssign(&Private::ButtonInfo::toolTip, d->mutableButtonInfo(btnId), toolTip);
}

/*! \brief Install a delegate for the attached view item, allowing the button mechanism to work
 */
void ItemViewButtons::installDefaultItemDelegate()
{
  if (d->m_view != NULL)
    d->m_view->setItemDelegate(this->createProxyItemDelegate(NULL));
}

/*!
 * \brief Create a proxy delegate around \p sourceDelegate to be further installed with
 *        QAbstractItemView::setItemDelegate()
 *
 *  This is useful when you have a delegate for an item view but for some reason don't want to
 *  modify it to integrate with ItemViewButtons
 */
QStyledItemDelegate*
ItemViewButtons::createProxyItemDelegate(QStyledItemDelegate *sourceDelegate,
                                         QObject *parent) const
{
  return new Private::ProxyItemDelegate(this, sourceDelegate, parent);
}

int ItemViewButtons::buttonAtModelIndex(const QModelIndex &index) const
{
  foreach (int id, d->m_btnInfos.keys()) {
    const Private::ButtonInfo* btnInfo = d->buttonInfo(id);
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

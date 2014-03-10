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

#ifndef QTTOOLS_ITEM_VIEW_BUTTONS_H
#define QTTOOLS_ITEM_VIEW_BUTTONS_H

#include "gui.h"

#include <QtCore/QHash>
#include <QtCore/QModelIndex>
#include <QtCore/QObject>
#include <QtCore/QFlags>
#include <QtGui/QIcon>
class QAbstractItemView;
class QIcon;
class QPainter;
class QStyledItemDelegate;
class QStyleOptionViewItem;

namespace qttools {

class QTTOOLS_GUI_EXPORT ItemViewButtons : public QObject
{
  Q_OBJECT

public:
  // Types
  enum ItemSide
  {
    ItemLeftSide,
    ItemRightSide
  };

  enum DisplayMode
  {
    DisplayOnDetection = 0x01,
    DisplayPermanent = 0x02,
    DisplayWhenItemSelected = 0x04
  };
  typedef QFlags<DisplayMode> DisplayModes;

  // Ctor & dtor
  ItemViewButtons(QAbstractItemView* view, QObject* parent = NULL);
  ~ItemViewButtons();

  // View control
  QAbstractItemView* itemView() const;

  bool eventFilter(QObject *object, QEvent *event);
  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

  // Button management
  void addButton(int btnId, const QIcon& icon = QIcon(), const QString& toolTip = QString());
  void copyButtonProperties(int srcBtnId, int dstBtnId);

  int buttonDetectionMatchRole(int btnId) const;
  QVariant buttonDetectionMatchData(int btnId) const;
  void setButtonDetection(int btnId, int matchRole, const QVariant& matchData);

  int buttonDisplayColumn(int btnId) const;
  void setButtonDisplayColumn(int btnId, int col = -1);

  int buttonItemSide(int btnId) const;
  void setButtonItemSide(int btnId, ItemSide side);

  DisplayModes buttonDisplayModes(int btnId) const;
  void setButtonDisplayModes(int btnId, DisplayModes modes);

  QIcon buttonIcon(int btnId) const;
  void setButtonIcon(int btnId, const QIcon& icon);

  QSize buttonIconSize(int btnId) const;
  void setButtonIconSize(int btnId, const QSize& size);

  QString buttonToolTip(int btnId) const;
  void setButtonToolTip(int btnId, const QString& toolTip);

  // Delegates
  void installDefaultItemDelegate();
  QStyledItemDelegate* createProxyItemDelegate(QStyledItemDelegate *sourceDelegate,
                                               QObject* parent = NULL) const;

signals:
  void buttonClicked(int btnId, const QModelIndex& index);

public slots:
  void reset();

protected:
  virtual int buttonAtModelIndex(const QModelIndex& index) const;

private:
  class Private;
  friend class Private;
  Private* const d;
};

} // namespace qttools

Q_DECLARE_OPERATORS_FOR_FLAGS(qttools::ItemViewButtons::DisplayModes)

#endif // QTTOOLS_ITEM_VIEW_BUTTONS_H

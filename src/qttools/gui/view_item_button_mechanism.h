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

#ifndef QTTOOLS_VIEW_ITEM_BUTTON_MECHANISM_H
#define QTTOOLS_VIEW_ITEM_BUTTON_MECHANISM_H

#include "gui.h"

#include <QtCore/QHash>
#include <QtCore/QModelIndex>
#include <QtCore/QObject>
#include <QtGui/QIcon>
class QAbstractItemView;
class QIcon;
class QPainter;
class QStyleOptionViewItem;

namespace qttools {

class QTTOOLS_GUI_EXPORT ViewItemButtonMechanism : public QObject
{
  Q_OBJECT

public:
  enum ItemSide
  {
    ItemLeftSide,
    ItemRightSide
  };

  enum DisplayMode
  {
    DisplayOnDetection,
    DisplayPermanent
  };

  ViewItemButtonMechanism(QAbstractItemView* view, QObject* parent = 0);
  ~ViewItemButtonMechanism();

  QAbstractItemView* itemView() const;

  bool eventFilter(QObject *object, QEvent *event);
  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index);

  void addButton(int btnId, const QIcon& icon, const QString& toolTip = QString());
  void setButtonDetection(int btnId, int matchRole, const QVariant& matchData);
  void setButtonDisplayColumn(int btnId, int col = -1);
  void setButtonItemSide(int btnId, ItemSide side);
  void setButtonDisplayMode(int btnId, DisplayMode mode);

signals:
  void buttonClicked(int btnId, const QModelIndex& index);

public slots:
  void reset();

protected:
  virtual int buttonAtModelIndex(const QModelIndex& index) const;

private:
  friend class ViewItemButtonMechanismPrivate;
  class ViewItemButtonMechanismPrivate* const d;
};

} // namespace qttools

#endif // QTTOOLS_VIEW_ITEM_BUTTON_MECHANISM_H

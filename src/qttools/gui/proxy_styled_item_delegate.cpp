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

#include "proxy_styled_item_delegate.h"

namespace qttools {

/*!
 * \class ProxyStyledItemDelegate
 * \brief Convenience class that simplifies dynamically overriding QStyledItemDelegate
 *
 * QStyledItemDelegate protected functions cannot be overriden through proxy technique, this is
 * a limitation that applies to :
 *   \li QStyledItemDelegate::initStyleOption()
 *   \li QStyledItemDelegate::eventFilter()
 *   \li QStyledItemDelegate::editorEvent()
 *
 * \headerfile proxy_styled_item_delegate.h <qttools/gui/proxy_styled_item_delegate.h>
 * \ingroup qttools_gui
 *
 */

ProxyStyledItemDelegate::ProxyStyledItemDelegate(QObject *parent)
  : QStyledItemDelegate(parent),
    m_sourceDelegate(NULL)
{

}

ProxyStyledItemDelegate::ProxyStyledItemDelegate(QStyledItemDelegate *srcDelegate,
                                                 QObject* parent)
  : QStyledItemDelegate(parent),
    m_sourceDelegate(srcDelegate)
{
}

QStyledItemDelegate *ProxyStyledItemDelegate::sourceDelegate() const
{
  return m_sourceDelegate;
}

void ProxyStyledItemDelegate::setSourceDelegate(QStyledItemDelegate *srcDelegate)
{
  m_sourceDelegate = srcDelegate;
}

void ProxyStyledItemDelegate::paint(QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
  if (m_sourceDelegate != NULL)
    m_sourceDelegate->paint(painter, option, index);
  else
    QStyledItemDelegate::paint(painter, option, index);
}

QSize ProxyStyledItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
  if (m_sourceDelegate != NULL)
    return m_sourceDelegate->sizeHint(option, index);
  return QStyledItemDelegate::sizeHint(option, index);
}

QString ProxyStyledItemDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
  if (m_sourceDelegate != NULL)
    return m_sourceDelegate->displayText(value, locale);
  return QStyledItemDelegate::displayText(value, locale);
}

QWidget *ProxyStyledItemDelegate::createEditor(QWidget *parent,
                                               const QStyleOptionViewItem &option,
                                               const QModelIndex &index) const
{
  if (m_sourceDelegate != NULL)
    return m_sourceDelegate->createEditor(parent, option, index);
  return QStyledItemDelegate::createEditor(parent, option, index);
}

void ProxyStyledItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if (m_sourceDelegate != NULL)
    m_sourceDelegate->setEditorData(editor, index);
  else
    QStyledItemDelegate::setEditorData(editor, index);
}

void ProxyStyledItemDelegate::setModelData(QWidget *editor,
                                           QAbstractItemModel *model,
                                           const QModelIndex &index) const
{
  if (m_sourceDelegate != NULL)
    m_sourceDelegate->setModelData(editor, model, index);
  else
    QStyledItemDelegate::setModelData(editor, model, index);
}

void ProxyStyledItemDelegate::updateEditorGeometry(QWidget *editor,
                                                   const QStyleOptionViewItem &option,
                                                   const QModelIndex &index) const
{
  if (m_sourceDelegate != NULL)
    m_sourceDelegate->updateEditorGeometry(editor, option, index);
  else
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

} // namespace qttools

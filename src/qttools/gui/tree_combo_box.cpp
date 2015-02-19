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

#include "tree_combo_box.h"

#include <QtCore/QtDebug>
// QtWidgets
#include <QHeaderView>
#include <QTreeView>

namespace qttools {

/*!
 * \class TreeComboBox
 * \brief Provides a QComboBox able to display a tree model item
 *
 * \headerfile tree_combo_box.h <qttools/gui/tree_combo_box.h>
 * \ingroup qttools_gui
 *
 */

/*! \example qttools/tree_combo_box/main.cpp
 *  Example of how to use class qttools::TreeComboBox
 */

TreeComboBox::TreeComboBox(QWidget *parent)
    : QComboBox(parent)
{
    QTreeView* treeView = new QTreeView(this);
    treeView->setEditTriggers(QTreeView::NoEditTriggers);
    treeView->setSelectionBehavior(QTreeView::SelectRows);
    treeView->header()->setVisible(false);
    this->setView(treeView);
}

void TreeComboBox::showPopup()
{
    this->setRootModelIndex(QModelIndex());
    this->treeView()->expandAll();
    this->treeView()->setItemsExpandable(false);
    QComboBox::showPopup();
}

//! The QTreeView used to display the attached tree model
QTreeView *TreeComboBox::treeView() const
{
    return qobject_cast<QTreeView*>(this->view());
}

/*! \brief Similar to QComboBox::findData() but searches recursively in the tree model (instead of
 *         just root items)
 */
QModelIndex TreeComboBox::treeFindData(const QVariant &data, int role, Qt::MatchFlags flags) const
{
    if (this->model() == NULL)
        return QModelIndex();
    const QModelIndex startId = this->model()->index(0, this->modelColumn(), QModelIndex());
    const QModelIndexList matchIds = this->model()->match(startId, role, data, 1, flags);
    return !matchIds.isEmpty() ? matchIds.first() : QModelIndex();
}

/*! \brief Holds the QModelIndex of the current item in the TreeComboBox
 */
QModelIndex TreeComboBox::currentModelIndex() const
{
    if (this->model() == NULL)
        return QModelIndex();
    const QModelIndex treeViewCurrentIndex = this->treeView()->currentIndex();
    if (!treeViewCurrentIndex.isValid())
        return this->model()->index(this->currentIndex(), this->modelColumn(), this->rootModelIndex());
    return treeViewCurrentIndex;
}

void TreeComboBox::setCurrentModelIndex(const QModelIndex &modelIndex)
{
    this->setRootModelIndex(modelIndex.parent());
    this->setCurrentIndex(modelIndex.row());
}

} // namespace qttools

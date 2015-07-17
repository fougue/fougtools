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

#include "tree_combo_box.h"

#include <QtCore/QtDebug>
// QtWidgets
#include <QHeaderView>
#include <QTreeView>

namespace qtgui {

/*!
 * \class TreeComboBox
 * \brief Provides a QComboBox able to display a tree model item
 *
 * \headerfile tree_combo_box.h <qttools/gui/tree_combo_box.h>
 * \ingroup qttools_gui
 *
 */

/*! \example qttools/tree_combo_box/main.cpp
 *  Example of how to use class qtgui::TreeComboBox
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

/*! Similar to QComboBox::findData() but searches recursively in the tree
 *  model (instead of just root items)
 */
QModelIndex TreeComboBox::treeFindData(
        const QVariant &data, int role, Qt::MatchFlags flags) const
{
    if (this->model() == NULL)
        return QModelIndex();
    const QModelIndex startId =
            this->model()->index(0, this->modelColumn(), QModelIndex());
    const QModelIndexList matchIds =
            this->model()->match(startId, role, data, 1, flags);
    return !matchIds.isEmpty() ? matchIds.first() : QModelIndex();
}

/*! \brief Holds the QModelIndex of the current item in the TreeComboBox
 */
QModelIndex TreeComboBox::currentModelIndex() const
{
    if (this->model() == NULL)
        return QModelIndex();
    const QModelIndex treeViewCurrentIndex = this->treeView()->currentIndex();
    if (!treeViewCurrentIndex.isValid()) {
        return this->model()->index(
                    this->currentIndex(),
                    this->modelColumn(),
                    this->rootModelIndex());
    }
    return treeViewCurrentIndex;
}

void TreeComboBox::setCurrentModelIndex(const QModelIndex &modelIndex)
{
    this->setRootModelIndex(modelIndex.parent());
    this->setCurrentIndex(modelIndex.row());
}

} // namespace qtgui

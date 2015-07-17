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

#include "qstandard_item_explorer.h"

#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

namespace qtgui {

/*!
 * \class QStandardItemExplorer
 * \brief Provides a BFS (breadth-first search) exploration of a
 *        QStandardItemModel object
 *
 * Example of use :
 * \code
 *   QStandardItemModel* model = ...;
 *   for (QStandardItemExplorer explorer(model);
 *        !explorer.atEnd();
 *        explorer.goNext())
 *   {
 *     QStandardItem* item = explorer.current();
 *     // Do something with item ...
 *   }
 * \endcode
 *
 * \headerfile qstandard_item_explorer.h <qttools/gui/qstandard_item_explorer.h>
 * \ingroup qttools_gui
 *
 */

QStandardItemExplorer::QStandardItemExplorer()
{
}

QStandardItemExplorer::QStandardItemExplorer(QStandardItem *rootItem)
{
    this->begin(rootItem);
}

QStandardItemExplorer::QStandardItemExplorer(QStandardItemModel *model)
{
    this->begin(model->invisibleRootItem());
}

bool QStandardItemTreeBfsModel::isDeeper(
        const QStandardItem *current, const QStandardItem *previous)
{
    return current->index().parent() != previous->index().parent();
}

} // namespace qtgui

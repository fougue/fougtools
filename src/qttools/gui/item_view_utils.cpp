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

#include "item_view_utils.h"

// Those classe are in Qt4/QtGui and Qt5/QtCore
#include <QSortFilterProxyModel>
#include <QItemSelectionModel>

// QtWidgets
#include <QAbstractItemView>

namespace qtgui {

/*! \class ItemViewUtils
 *  \brief Provides a collection of tools around QAbstractItemView
 *
 *  \headerfile item_view_utils.h <qttools/gui/item_view_utils.h>
 *  \ingroup qttools_gui
 */

/*! \brief Indexes, in the given column, of the rows selected in a view
 *  \param view View in which to find selected rows
 *  \param col Column index. If \p col == \c -1 then \p col is ignored
 */
QVector<int> ItemViewUtils::selectedRows(const QAbstractItemView* view, int col)
{
    const QItemSelectionModel* itemSelModel = view->selectionModel();
    if (itemSelModel == NULL || !itemSelModel->hasSelection())
        return QVector<int>();
    const QModelIndexList selIndexes = itemSelModel->selectedIndexes();
    QVector<int> result;
    result.reserve(selIndexes.size());
    QSet<int> alreadyAddedRows;
    foreach (const QModelIndex& modId, selIndexes) {
        if (!alreadyAddedRows.contains(modId.row()) && (col == -1 || modId.column() == col)) {
            result.append(modId.row());
            alreadyAddedRows.insert(modId.row());
        }
    }
    return result;
}

void ItemViewUtils::selectRows(QAbstractItemView* view, const QVector<int>& rows)
{
    const QAbstractItemModel* model = view->model();
    QItemSelectionModel* selModel = view->selectionModel();
    if (model == NULL || selModel == NULL)
        return;
    const QItemSelectionModel::SelectionFlags selFlags =
            QItemSelectionModel::ToggleCurrent | QItemSelectionModel::Rows;
    //        QItemSelectionModel::Select | QItemSelectionModel::Rows;
    foreach (int iRow, rows)
        selModel->select(model->index(iRow, 0), selFlags);
}

/*! \brief Same as QSortFilterProxyModel::mapFromSource() but more concise
 */
int ItemViewUtils::mapRowFromSourceModel(const QSortFilterProxyModel* proxyModel, int srcRow)
{
    return proxyModel->mapFromSource(proxyModel->sourceModel()->index(srcRow, 0)).row();
}

/*! \brief Same as QSortFilterProxyModel::mapToSource() but more concise
 */
int ItemViewUtils::mapRowToSourceModel(const QSortFilterProxyModel* proxyModel, int proxyRow)
{
    return proxyModel->mapToSource(proxyModel->index(proxyRow, 0)).row();
}

} // namespace qtgui

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

#pragma once

class QAbstractItemModel;

#include "core.h"
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QVector>

namespace qtcore {

class QTTOOLS_CORE_EXPORT ItemModelUtils
{
public:
    static bool isValidRow(
            const QAbstractItemModel* model,
            int row,
            const QModelIndex& parent = QModelIndex());

    static bool isValidColumn(
            const QAbstractItemModel* model,
            int col,
            const QModelIndex& parent = QModelIndex());

    template<typename INT_CONTAINER>
    static bool validRows(
            const QAbstractItemModel* model,
            const INT_CONTAINER& rows,
            const QModelIndex& parent = QModelIndex());

    static int findDataInRow(
            const QAbstractItemModel* model, int col, const QVariant& value);

    static QVariant tableData(
            const QAbstractItemModel* model,
            int row,
            int col,
            int role = Qt::DisplayRole);

    template<typename INT_CONTAINER>
    static void removeRows(
            QAbstractItemModel* model, const INT_CONTAINER& rows);
};

} // namespace qtcore

// --
// -- Implementation
// --

#include <algorithm>
#include <functional>
#include <QtCore/QAbstractItemModel>

namespace qtcore {

template<typename INT_CONTAINER>
bool ItemModelUtils::validRows(
        const QAbstractItemModel* model,
        const INT_CONTAINER& rows,
        const QModelIndex& parent)
{
    for (auto iRow = rows.begin(); iRow != rows.end(); ++iRow) {
        if (!ItemModelUtils::isValidRow(model, *iRow, parent))
            return false;
    }
    return !rows.isEmpty();
}

template<typename INT_CONTAINER>
void ItemModelUtils::removeRows(
        QAbstractItemModel* model, const INT_CONTAINER& rows)
{
    if (model == NULL)
        return;
    // Delete rows by descending order
    QVector<int> descRows;
    for (auto it = rows.begin(); it != rows.end(); ++it) {
        if (ItemModelUtils::isValidRow(model, *it))
            descRows.append(*it);
    }
    std::sort(descRows.begin(), descRows.end(), std::greater<int>());
    foreach (int row, descRows)
        model->removeRow(row);
}

} // namespace qtcore

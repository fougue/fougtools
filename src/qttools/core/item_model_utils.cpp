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

#include "item_model_utils.h"

namespace qtcore {

/*! \class ItemModelUtils
 *  \brief Provides a collection of tools around QAbstractItemModel
 *  \headerfile item_model_utils.h <qttools/core/item_model_utils.h>
 *  \ingroup qttools_core
 *
 */

bool ItemModelUtils::isValidRow(const QAbstractItemModel* model, int row, const QModelIndex& parent)
{
    if (model != NULL)
        return 0 <= row && row < model->rowCount(parent);
    return false;
}

bool ItemModelUtils::isValidColumn(const QAbstractItemModel* model, int col, const QModelIndex& parent)
{
    if (model != NULL)
        return 0 <= col && col < model->columnCount(parent);
    return false;
}

/*! \brief Try to find a value in a given column of a model
 *  \return Index of the row where the first match of \p value could be found
 *  \retval -1 if \p value could not be found
 */
int ItemModelUtils::findDataInRow(const QAbstractItemModel* model, int col, const QVariant& value)
{
    if (model != NULL) {
        for (int row = 0; row < model->rowCount(); ++row) {
            if (model->data(model->index(row, col)) == value)
                return row;
        }
    }
    return -1;
}

/*! \brief Same as QAbstractItemModel::data() but more concise
 */
QVariant ItemModelUtils::tableData(const QAbstractItemModel* model, int row, int col, int role)
{
    if (model != NULL)
        return model->data(model->index(row, col), role);
    return QVariant();
}

} // namespace qtcore

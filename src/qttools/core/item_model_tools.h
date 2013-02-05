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

#ifndef QTTOOLS_ITEM_MODEL_TOOLS_H
#define QTTOOLS_ITEM_MODEL_TOOLS_H

#include "core.h"
#include <QtCore/QModelIndex>
#include <QtCore/QVector>
class QAbstractItemModel;
class QVariant;

namespace qttools {

QTTOOLS_CORE_EXPORT
bool isValidRow(const QAbstractItemModel* model,
                int row, const QModelIndex& parent = QModelIndex());

QTTOOLS_CORE_EXPORT
bool isValidColumn(const QAbstractItemModel* model,
                   int col, const QModelIndex& parent = QModelIndex());

template<typename INT_CONTAINER>
bool validRows(const QAbstractItemModel* model,
               const INT_CONTAINER& rows,
               const QModelIndex& parent = QModelIndex());

QTTOOLS_CORE_EXPORT
int findDataInRow(const QAbstractItemModel* model, int col, const QVariant& value);

QTTOOLS_CORE_EXPORT
QVariant tableModelData(const QAbstractItemModel* model,
                        int row, int col, int role = Qt::DisplayRole);

template<typename INT_CONTAINER>
void removeRows(QAbstractItemModel* model, const INT_CONTAINER& rows);

} // namespace qttools

// --
// -- Implementation
// --

#include <algorithm>
#include <QtCore/QAbstractItemModel>

namespace qttools {

template<typename INT_CONTAINER>
bool validRows(const QAbstractItemModel* model,
               const INT_CONTAINER& rows, const QModelIndex& parent)
{
  for (typename INT_CONTAINER::const_iterator iRow = rows.begin(); iRow != rows.end(); ++iRow) {
    if (!qttools::isValidRow(model, *iRow, parent))
      return false;
  }
  return !rows.isEmpty();
}

template<typename INT_CONTAINER>
void removeRows(QAbstractItemModel* model, const INT_CONTAINER& rows)
{
  if (model == NULL)
      return;
  // Delete rows by descending order
  QVector<int> descRows;
  for (typename INT_CONTAINER::const_iterator it = rows.begin(); it != rows.end(); ++it) {
    if (qttools::isValidRow(model, *it))
      descRows.append(*it);
  }
  std::sort(descRows.begin(), descRows.end(), std::greater<int>());
  foreach (int row, descRows)
    model->removeRow(row);
}

} // namespace qttools

#endif // QTTOOLS_ITEM_MODEL_TOOLS_H

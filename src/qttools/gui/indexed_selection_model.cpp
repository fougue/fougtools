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

#include "indexed_selection_model.h"

namespace qtgui {

/*!
 * \class IndexedSelectionModel
 * \brief Helper that keeps track of selected items in any kind of view (not specific to Qt)
 *
 * View items are each referenced by an index that the caller must provide.
 *
 * \headerfile indexed_selection_model.h <qttools/gui/indexed_selection_model.h>
 * \ingroup qttools_gui
 *
 */

IndexedSelectionModel::IndexedSelectionModel(QObject* parent)
    : QObject(parent),
      m_hadSelection(false)
{
    QObject::connect(this, &IndexedSelectionModel::selectionCleared,
                     this, &IndexedSelectionModel::selectionChanged);
    QObject::connect(this, &IndexedSelectionModel::itemToggled,
                     this, &IndexedSelectionModel::selectionChanged);
}

//! Indexes of the items being selected in the view
const QSet<int>& IndexedSelectionModel::selectedItems() const
{
    return m_selectedItems;
}

//! Is the selection not empty ?
bool IndexedSelectionModel::hasSelection() const
{
    return !this->selectedItems().isEmpty();
}

/*! Is index \p id valid ?
 *
 *  By default only indexes >= 0 are valid.
 */
bool IndexedSelectionModel::isValidIndex(int id) const
{
    return id >= 0;
}

/*! \brief Untoggle all selected items, this will emit selectionCleared() at the end
 *
 *  Signal selectionCleared() is emitted only if hasSelection() returned \c true.
 */
void IndexedSelectionModel::clear()
{
    this->beginClear();
    this->clearItems();
    this->endClear();
}

//! Toggle the item's selection state of index \p id
void IndexedSelectionModel::toggleItem(int id)
{
    if (!this->isValidIndex(id))
        return;
    const bool isItemSelected = this->selectedItems().contains(id);
    if (isItemSelected)
        m_selectedItems.remove(id);
    else
        m_selectedItems.insert(id);
    emit itemToggled(id, !isItemSelected);
}

void IndexedSelectionModel::beginClear()
{
    m_hadSelection = this->hasSelection();
}

void IndexedSelectionModel::clearItems()
{
    // Untoggle selected items
    foreach (int id, this->selectedItems()) {
        m_selectedItems.remove(id);
        emit itemToggled(id, false);
    }
    Q_ASSERT(this->selectedItems().count() == 0);
}

void IndexedSelectionModel::endClear()
{
    if (m_hadSelection)
        emit selectionCleared();
}

} // namespace qtgui

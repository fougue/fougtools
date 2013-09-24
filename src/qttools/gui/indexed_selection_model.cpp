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

#include "indexed_selection_model.h"

#include <cassert>

namespace qttools {

/*! \class IndexedSelectionModel
 *  \brief
 *
 * \headerfile indexed_selection_model.h <qttools/gui/indexed_selection_model.h>
 * \ingroup qttools_gui
 *
 */

IndexedSelectionModel::IndexedSelectionModel(QObject* parent)
  : QObject(parent),
    m_hadSelection(false)
{
  connect(this, SIGNAL(selectionCleared()), this, SIGNAL(selectionChanged()));
  connect(this, SIGNAL(itemToggled(int,bool)), this, SIGNAL(selectionChanged()));
}

const QSet<int>& IndexedSelectionModel::selectedItems() const
{
  return m_selectedItems;
}

bool IndexedSelectionModel::hasSelection() const
{
  return !this->selectedItems().isEmpty();
}

bool IndexedSelectionModel::isValidIndex(int id) const
{
  return id >= 0;
}

void IndexedSelectionModel::clear()
{
  this->beginClear();
  this->clearItems();
  this->endClear();
}

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
  assert(this->selectedItems().count() == 0);
}

void IndexedSelectionModel::endClear()
{
  if (m_hadSelection)
    emit selectionCleared();
}

} // namespace qttools

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

#ifndef QTTOOLS_IDENTIFIER_MODEL_ROW_MAPPING_H
#define QTTOOLS_IDENTIFIER_MODEL_ROW_MAPPING_H

#include "core.h"
#include <QtCore/QHash>
#include <QtCore/QAbstractItemModel>

namespace qttools {

template<typename IDENTIFIER>
class IdentifierModelRowMapping
{
public:
  IdentifierModelRowMapping(const QAbstractItemModel* model, int identCol = 0);

  int modelRow(IDENTIFIER ident) const;

  bool isMapped(IDENTIFIER ident) const;
  void changeMap(IDENTIFIER ident, int modelRow);
  void removeMap(IDENTIFIER ident);
  void remap();

  void setIdentifierColumn(int col);

private:
  QHash<IDENTIFIER, int> m_mapping;
  const QAbstractItemModel* m_model;
  int m_identCol;
};

// --
// -- Implementation
// --

template<typename IDENTIFIER>
IdentifierModelRowMapping<IDENTIFIER>::IdentifierModelRowMapping(const QAbstractItemModel* model,
                                                                 int identCol)
  : m_model(model),
    m_identCol(identCol)
{
}

template<typename IDENTIFIER>
int IdentifierModelRowMapping<IDENTIFIER>::modelRow(IDENTIFIER ident) const
{
  return m_mapping.value(ident, -1);
}

template<typename IDENTIFIER>
bool IdentifierModelRowMapping<IDENTIFIER>::isMapped(IDENTIFIER ident) const
{
  return m_mapping.contains(ident);
}

template<typename IDENTIFIER>
void IdentifierModelRowMapping<IDENTIFIER>::setIdentifierColumn(int col)
{
  m_identCol = col;
}

template<typename IDENTIFIER>
void IdentifierModelRowMapping<IDENTIFIER>::changeMap(IDENTIFIER ident, int modelRow)
{
  m_mapping.insert(ident, modelRow);
}

template<typename IDENTIFIER>
void IdentifierModelRowMapping<IDENTIFIER>::removeMap(IDENTIFIER ident)
{
  m_mapping.remove(ident);
}

template<typename IDENTIFIER>
void IdentifierModelRowMapping<IDENTIFIER>::remap()
{
  const QAbstractItemModel* m = m_model;
  m_mapping.clear();
  for (int row = 0; row < m_model->rowCount(); ++row) {
    const QVariant identVar = m->data(m->index(row, m_identCol));
    const IDENTIFIER ident = identVar.value<IDENTIFIER>();
    m_mapping.insert(ident, row);
  }
}

} // namespace qttools

#endif // QTTOOLS_IDENTIFIER_MODEL_ROW_MAPPING_H

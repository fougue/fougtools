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

#include "qttools/core/core.h"
#include <QtCore/QHash>
#include <QtCore/QAbstractItemModel>

namespace qttools {

template<typename _IDENTIFIER_>
class IdentifierModelRowMapping
{
public:
  IdentifierModelRowMapping(const QAbstractItemModel* model, int identCol = 0);

  int modelRow(_IDENTIFIER_ ident) const;

  bool isMapped(_IDENTIFIER_ ident) const;
  void changeMap(_IDENTIFIER_ ident, int modelRow);
  void removeMap(_IDENTIFIER_ ident);
  void remap();

  void setIdentifierColumn(int col);

private:
  QHash<_IDENTIFIER_, int> _mapping;
  const QAbstractItemModel* _model;
  int _identCol;
};


// --
// -- Implementation
// --

template<typename _IDENTIFIER_>
IdentifierModelRowMapping<_IDENTIFIER_>::IdentifierModelRowMapping(
    const QAbstractItemModel* model, int identCol) :
  _mapping(),
  _model(model),
  _identCol(identCol)
{
}

template<typename _IDENTIFIER_>
int IdentifierModelRowMapping<_IDENTIFIER_>::modelRow(_IDENTIFIER_ ident) const
{
  if (this->_mapping.contains(ident))
    return this->_mapping[ident];
  return -1;
}

template<typename _IDENTIFIER_>
bool IdentifierModelRowMapping<_IDENTIFIER_>::isMapped(_IDENTIFIER_ ident) const
{
  return this->_mapping.contains(ident);
}

template<typename _IDENTIFIER_>
void IdentifierModelRowMapping<_IDENTIFIER_>::setIdentifierColumn(int col)
{
  this->_identCol = col;
}

template<typename _IDENTIFIER_>
void IdentifierModelRowMapping<_IDENTIFIER_>::changeMap(_IDENTIFIER_ ident,
                                                        int modelRow)
{
  this->_mapping[ident] = modelRow;
}

template<typename _IDENTIFIER_>
void IdentifierModelRowMapping<_IDENTIFIER_>::removeMap(_IDENTIFIER_ ident)
{
  this->_mapping.remove(ident);
}

template<typename _IDENTIFIER_>
void IdentifierModelRowMapping<_IDENTIFIER_>::remap()
{
  const QAbstractItemModel* m = this->_model;
  this->_mapping.clear();
  for (int row = 0; row < this->_model->rowCount(); ++row) {
    const QVariant identVar = m->data(m->index(row, this->_identCol));
    const _IDENTIFIER_ ident = identVar.value<_IDENTIFIER_>();
    this->_mapping[ident] = row;
  }
}

} // namespace qttools

#endif // QTTOOLS_IDENTIFIER_MODEL_ROW_MAPPING_H

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

#include "qttools/gui/qcombo_box_current_item_keeper.h"

#include <QtGui/QComboBox>

#include <QtCore/QtDebug>

namespace qttools {

/*! \class QComboBoxCurrentItemKeeper
 *  \brief Provides automatic preservation of a QComboBox's current item on
 *         reset of a QAbstractItemModel
 *
 */

QComboBoxCurrentItemKeeper::QComboBoxCurrentItemKeeper(QComboBox* comboBox)
  : QObject(comboBox),
    m_oldCurrentIndex(-1),
    m_oldIdentifierValue(),
    m_columnForModelRowIdentifier(0)
{
  if (comboBox == 0)
    return;
  const QAbstractItemModel* model = comboBox->model();
  connect(model, SIGNAL(modelAboutToBeReset()),
          this, SLOT(onModelAboutToBeReset()));
  connect(model, SIGNAL(modelReset()), this, SLOT(onModelReset()));
}

int QComboBoxCurrentItemKeeper::columnForModelRowIdentifier() const
{
  return m_columnForModelRowIdentifier;
}

void QComboBoxCurrentItemKeeper::setColumnForModelRowIdentifier(int col)
{
  m_columnForModelRowIdentifier = col;
}

void QComboBoxCurrentItemKeeper::onModelAboutToBeReset()
{
  m_oldCurrentIndex = this->comboBox()->currentIndex();
  m_oldIdentifierValue = this->currentIdentifierValue();

#ifdef m_TRACE_QComboBoxCurrentItemKeeper_
  qDebug() << "QComboBoxCurrentItemKeeper::onModelAboutToBeReset()";
  qDebug() << "   m_oldCurrentIndex :" << m_oldCurrentIndex
           << " m_oldIdentifierValue :" << m_oldIdentifierValue;
#endif // m_TRACE_QComboBoxCurrentItemKeeper_
}

void QComboBoxCurrentItemKeeper::onModelReset()
{
#ifdef m_TRACE_QComboBoxCurrentItemKeeper_
  qDebug() << "QComboBoxCurrentItemKeeper::onModelReset()";
#endif // m_TRACE_QComboBoxCurrentItemKeeper_

  int newCurrIndex = -1;
  if (m_oldIdentifierValue == this->identifierValue(m_oldCurrentIndex)) {
    // Special case when the old index matches the (new) current index
    newCurrIndex = m_oldCurrentIndex;
#ifdef m_TRACE_QComboBoxCurrentItemKeeper_
    qDebug() << "   if() newCurrIndex :" << newCurrIndex;
#endif // m_TRACE_QComboBoxCurrentItemKeeper_
  }
  else  {
    // Case when the old index does not match the (new) current index
    const QAbstractItemModel* model = this->comboBox()->model();
    for (int iRow = 0; iRow < model->rowCount() && newCurrIndex != -1; ++iRow)
      if (m_oldIdentifierValue == this->identifierValue(iRow))
        newCurrIndex = iRow;
#ifdef m_TRACE_QComboBoxCurrentItemKeeper_
    qDebug() << "   else() newCurrIndex :" << newCurrIndex;
#endif // m_TRACE_QComboBoxCurrentItemKeeper_
  }
  newCurrIndex = std::max(newCurrIndex, 0);
#ifdef m_TRACE_QComboBoxCurrentItemKeeper_
  qDebug() << "   setCurrentIndex :" << newCurrIndex;
#endif // m_TRACE_QComboBoxCurrentItemKeeper_
  this->comboBox()->setCurrentIndex(newCurrIndex);
}

QComboBox* QComboBoxCurrentItemKeeper::comboBox() const
{
  return qobject_cast<QComboBox*>(this->parent());
}

QVariant QComboBoxCurrentItemKeeper::currentIdentifierValue() const
{
  return this->identifierValue(this->comboBox()->currentIndex());
}

QVariant QComboBoxCurrentItemKeeper::identifierValue(int row) const
{
  const QAbstractItemModel* model = this->comboBox()->model();
  return model->data(model->index(row, this->columnForModelRowIdentifier()));
}

} // namespace qttools

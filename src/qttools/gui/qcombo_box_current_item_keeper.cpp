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

#include "qcombo_box_current_item_keeper.h"

#include <QtCore/QtDebug>
// QtWidgets
#include <QComboBox>

namespace qtgui {

/*!
 * \class QComboBoxCurrentItemKeeper
 * \brief Provides automatic preservation of a QComboBox's current item on reset
 *        of a QAbstractItemModel
 *
 * \headerfile qcombo_box_current_item_keeper.h <qttools/gui/qcombo_box_current_item_keeper.h>
 * \ingroup qttools_gui
 *
 */

QComboBoxCurrentItemKeeper::QComboBoxCurrentItemKeeper(QComboBox* comboBox)
    : QObject(comboBox),
      m_oldCurrentIndex(-1),
      m_oldIdentifierValue(),
      m_columnForModelRowIdentifier(0)
{
    if (comboBox == NULL)
        return;
    const QAbstractItemModel* model = comboBox->model();
    QObject::connect(
                model, &QAbstractItemModel::modelAboutToBeReset,
                this, &QComboBoxCurrentItemKeeper::onModelAboutToBeReset);
    QObject::connect(
                model, &QAbstractItemModel::modelReset,
                this, &QComboBoxCurrentItemKeeper::onModelReset);
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

#ifdef _TRACE_QComboBoxCurrentItemKeeper_
    qDebug() << "QComboBoxCurrentItemKeeper::onModelAboutToBeReset()";
    qDebug() << "   m_oldCurrentIndex :" << m_oldCurrentIndex
             << " m_oldIdentifierValue :" << m_oldIdentifierValue;
#endif // _TRACE_QComboBoxCurrentItemKeeper_
}

void QComboBoxCurrentItemKeeper::onModelReset()
{
#ifdef _TRACE_QComboBoxCurrentItemKeeper_
    qDebug() << "QComboBoxCurrentItemKeeper::onModelReset()";
#endif // _TRACE_QComboBoxCurrentItemKeeper_

    int newCurrIndex = -1;
    if (m_oldIdentifierValue == this->identifierValue(m_oldCurrentIndex)) {
        // Special case when the old index matches the (new) current index
        newCurrIndex = m_oldCurrentIndex;
#ifdef _TRACE_QComboBoxCurrentItemKeeper_
        qDebug() << "   if() newCurrIndex :" << newCurrIndex;
#endif // _TRACE_QComboBoxCurrentItemKeeper_
    }
    else  {
        // Case when the old index does not match the (new) current index
        const QAbstractItemModel* model = this->comboBox()->model();
        for (int iRow = 0; iRow < model->rowCount() && newCurrIndex == -1; ++iRow) {
            if (m_oldIdentifierValue == this->identifierValue(iRow))
                newCurrIndex = iRow;
        }
#ifdef _TRACE_QComboBoxCurrentItemKeeper_
        qDebug() << "   else() newCurrIndex :" << newCurrIndex;
#endif // _TRACE_QComboBoxCurrentItemKeeper_
    }
    newCurrIndex = std::max(newCurrIndex, 0);
#ifdef _TRACE_QComboBoxCurrentItemKeeper_
    qDebug() << "   setCurrentIndex :" << newCurrIndex;
#endif // _TRACE_QComboBoxCurrentItemKeeper_
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

} // namespace qtgui

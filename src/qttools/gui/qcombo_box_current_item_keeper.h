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

#include "gui.h"
#include <QtCore/QObject>
#include <QtCore/QVariant>
class QComboBox;

namespace qtgui {

class QTTOOLS_GUI_EXPORT QComboBoxCurrentItemKeeper : public QObject
{
    Q_OBJECT

public:
    QComboBoxCurrentItemKeeper(QComboBox* comboBox = NULL);

    int columnForModelRowIdentifier() const;
    void setColumnForModelRowIdentifier(int col);

signals:
    void currentIndexChanged(int row);

private slots:
    void onModelAboutToBeReset();
    void onModelReset();

private:
    QComboBox* comboBox() const;
    QVariant currentIdentifierValue() const;
    QVariant identifierValue(int row) const;

    int m_oldCurrentIndex;
    QVariant m_oldIdentifierValue;
    int m_columnForModelRowIdentifier;
};

} // namespace qtgui

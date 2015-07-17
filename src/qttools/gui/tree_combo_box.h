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

#include <QtCore/QModelIndex>
// QtWidgets
#include <QComboBox>
class QTreeView;

namespace qtgui {

class QTTOOLS_GUI_EXPORT TreeComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QModelIndex currentModelIndex READ currentModelIndex WRITE setCurrentModelIndex)

public:
    TreeComboBox(QWidget *parent = NULL);

    void showPopup() Q_DECL_OVERRIDE;

    QTreeView* treeView() const;

    QModelIndex treeFindData(
            const QVariant& data,
            int role = Qt::UserRole,
            Qt::MatchFlags flags = Qt::MatchRecursive) const;

    QModelIndex currentModelIndex() const;
    Q_SLOT void setCurrentModelIndex(const QModelIndex& modelIndex);
};

} // namespace qtgui

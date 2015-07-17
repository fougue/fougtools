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
#include <QtCore/QSet>

namespace qtgui {

class QTTOOLS_GUI_EXPORT IndexedSelectionModel : public QObject
{
    Q_OBJECT

public:
    IndexedSelectionModel(QObject* parent = NULL);

    const QSet<int>& selectedItems() const;

    virtual bool hasSelection() const;
    virtual bool isValidIndex(int id) const;

public slots:
    virtual void clear();
    void toggleItem(int id);

signals:
    void selectionCleared();
    void itemToggled(int id, bool on);
    void selectionChanged();

protected:
    void beginClear();
    void clearItems();
    void endClear();

private:
    QSet<int> m_selectedItems;
    bool m_hadSelection;
};

} // namespace qtgui

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

#include "core.h"
#include <QtCore/Qt>
#include <QtCore/QVector>

namespace qtcore {

class QTTOOLS_CORE_EXPORT GridNumbering
{
public:
    enum SweepMode
    {
        OneWay,
        ZigZag
    };

    GridNumbering();
    GridNumbering(
            Qt::Corner corner, Qt::Orientation orientation, SweepMode sweep);

    Qt::Corner startCorner() const;
    void setStartCorner(Qt::Corner corner);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    SweepMode sweepMode() const;
    void setSweepMode(SweepMode sweepMode);

    static QVector< QVector<int> > gridIndexes(
            const GridNumbering& gridNb,
            int rowCount,
            int colCount,
            int startIndex = 0);
private:
    Qt::Corner m_startCorner;
    Qt::Orientation m_orientation;
    SweepMode m_sweepMode;
};

} // namespace qtcore

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
#include "grid_numbering.h"

namespace qtcore {

class QTTOOLS_CORE_EXPORT GridStruct
{
public:
    GridStruct();
    GridStruct(int rows, int cols);

    bool isValid() const;

    int itemCount() const;
    void setItemCount(int rows, int cols);

    int rowCount() const;
    void setRowCount(int count);

    int columnCount() const;
    void setColumnCount(int count);

    const GridNumbering& itemNumbering() const;
    void setItemNumbering(const GridNumbering& gridNb);

private:
    int m_rowCount;
    int m_colCount;
    GridNumbering m_gridNb;
};

} // namespace qtcore

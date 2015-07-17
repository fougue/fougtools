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

#include "grid_struct.h"

namespace qtcore {

/*!
 * \class GridStruct
 * \brief Basic data for a grid structure : row and column count + cell numbering
 * \headerfile grid_struct.h <qttools/core/grid_struct.h>
 * \ingroup qttools_core
 *
 */

//! Constructs an invalid grid having no items, ie. itemCount() == 0
GridStruct::GridStruct()
    : m_rowCount(0),
      m_colCount(0)
{
}

GridStruct::GridStruct(int rows, int cols)
    : m_rowCount(rows),
      m_colCount(cols)
{
}

bool GridStruct::isValid() const
{
    return this->itemCount() > 0;
}

int GridStruct::itemCount() const
{
    return this->rowCount() * this->columnCount();
}

void GridStruct::setItemCount(int rows, int cols)
{
    this->setRowCount(rows);
    this->setColumnCount(cols);
}

int GridStruct::rowCount() const
{
    return m_rowCount;
}

void GridStruct::setRowCount(int count)
{
    m_rowCount = count;
}

int GridStruct::columnCount() const
{
    return m_colCount;
}

void GridStruct::setColumnCount(int count)
{
    m_colCount = count;
}

const GridNumbering& GridStruct::itemNumbering() const
{
    return m_gridNb;
}

void GridStruct::setItemNumbering(const GridNumbering& gridNb)
{
    m_gridNb = gridNb;
}

} // namespace qtcore

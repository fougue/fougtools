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

#include "grid_numbering.h"
#include <algorithm>

namespace qttools {

/*!
 * \class GridNumbering
 * \brief Represents standard numbering of grid cells
 *
 * \headerfile grid_numbering.h <qttools/core/grid_numbering.h>
 * \ingroup qttools_core
 *
 * GridNumbering stores key information about numbering of grid cells :
 *    \li start corner (grid corner where the numbering starts, i.e. the firt cell)
 *    \li orientation (horizontal or vertical numbering)
 *    \li sweep mode (one-way or zig-zag numbering)
 *
 */

GridNumbering::GridNumbering()
  : m_startCorner(Qt::TopLeftCorner),
    m_orientation(Qt::Horizontal),
    m_sweepMode(OneWay)
{
}

GridNumbering::GridNumbering(Qt::Corner corner, Qt::Orientation orientation, SweepMode sweep)
  : m_startCorner(corner),
    m_orientation(orientation),
    m_sweepMode(sweep)
{
}

Qt::Corner GridNumbering::startCorner() const
{
  return m_startCorner;
}

void GridNumbering::setStartCorner(Qt::Corner corner)
{
  m_startCorner = corner;
}

Qt::Orientation GridNumbering::orientation() const
{
  return m_orientation;
}

void GridNumbering::setOrientation(Qt::Orientation orientation)
{
  m_orientation = orientation;
}

GridNumbering::SweepMode GridNumbering::sweepMode() const
{
  return m_sweepMode;
}

void GridNumbering::setSweepMode(SweepMode sweepMode)
{
  m_sweepMode = sweepMode;
}

/*!
 * \brief Computes all the indexes of a grid's cells
 *
 * The result is an array of grid rows (each row being of the same size).\n
 * For example:
 *   \li GridNumbering(Qt::TopRightCorner, Qt::Vertical, GridNumbering::OneWay)
 *   \li rowCount = colCount = 4
 *   \li startIndex = 0
 *
 * will output:
 * \code
 *   row[0] == { 12   8  4  0 }
 *   row[1] == { 13   9  5  1 }
 *   row[2] == { 14  10  6  2 }
 *   row[3] == { 15  11  7  3 }
 * \endcode
 *
 * \note: Let N = \p rowCount and M = \p colCount , complexity is O(NxM)
 *
 * \param gridNb How grid cells have to be numbered
 * \param rowCount Count of rows in the grid
 * \param colCount Count of columns in the grid
 * \param startIndex The first index to start from (usually 0 or 1)
 */
QVector< QVector<int> > GridNumbering::gridIndexes(const GridNumbering& gridNb,
                                                   int rowCount, int colCount,
                                                   int startIndex)
{
  const bool isZigZag = gridNb.sweepMode() == ZigZag;
  const Qt::Corner nbCorner = gridNb.startCorner();
  const Qt::Orientation nbOrientation = gridNb.orientation();

  // Create normalized grid
  QVector< QVector<int> > grid;
  grid.resize(rowCount);
  for (int row = 0; row < rowCount; ++row)
    grid[row].resize(colCount);

  // Fill grid (handle the orientation and sweep mode)
  const int dim1Count = nbOrientation == Qt::Horizontal ? rowCount : colCount;
  const int dim2Count = nbOrientation == Qt::Horizontal ? colCount : rowCount;
  int index = startIndex;
  for (int dim1 = 0; dim1 < dim1Count; ++dim1) {
    const bool isEvenDim1 = ((dim1 + 1) % 2) == 0;
    const int dim2Start = isEvenDim1 && isZigZag ? dim2Count - 1 : 0;
    const int dim2End = isEvenDim1 && isZigZag ? -1 : dim2Count;
    const int dim2Incr = isEvenDim1 && isZigZag ? -1 : 1;
    for (int dim2 = dim2Start; dim2 != dim2End; dim2 += dim2Incr) {
      const int row = nbOrientation == Qt::Horizontal ? dim1 : dim2;
      const int col = nbOrientation == Qt::Horizontal ? dim2 : dim1;
      grid[row][col] = index++;
    } // end for(dim2)
  } // end for(dim1)

  // Handle left-right side
  if (nbCorner == Qt::TopRightCorner || nbCorner == Qt::BottomRightCorner) {
    for (int row = 0; row < rowCount; ++row)
      std::reverse(grid[row].begin(), grid[row].end());
  }

  // Handle top-bottom side
  if (nbCorner == Qt::BottomLeftCorner || nbCorner == Qt::BottomRightCorner)
    std::reverse(grid.begin(), grid.end());
  return grid;
}

} // namespace qttools

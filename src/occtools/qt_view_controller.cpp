/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language, the Qt and Open Cascade toolkits.
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

#include "qt_view_controller.h"

#include <QtGui/QKeyEvent>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
# include <QtWidgets/QRubberBand>
#else
# include <QtGui/QRubberBand>
//# include <QtGui/QPlastiqueStyle>
#endif

#include "qt_view.h"

namespace occ {

/*! \class QtViewController
 *
 *  \headerfile qt_view_controller.h <occtools/qt_view_controller.h>
 *  \ingroup occtools
 */

QtViewController::QtViewController(QtView* view)
  : QObject(view),
    m_view(view),
    m_rubberBand(NULL)
{
}

// -- Rubber band handling

void QtViewController::beginRubberBandDraw(const QPoint& startPos)
{
  this->createRubberBand();
  m_startRubberBandPos = startPos;
  m_rubberBand->setGeometry(QRect(startPos, QSize()));
  m_rubberBand->show();
}

void QtViewController::updateRubberBandDraw(const QPoint& currPos)
{
  this->createRubberBand();
  m_rubberBand->hide();
  QRect window(m_startRubberBandPos, currPos);
  m_rubberBand->setGeometry(window.normalized());
  m_rubberBand->show();
}

void QtViewController::endRubberBandDraw()
{
  this->createRubberBand();
  m_rubberBand->hide();
}

// --- Event handling

bool QtViewController::eventFilter(QObject* object, QEvent* event)
{
  return QObject::eventFilter(object, event);
}

void QtViewController::notifyContextSelectionChanged()
{
  emit contextSelectionChanged();
}

void QtViewController::notifyEscaped()
{
  emit escaped();
}

// --- Access

Handle_V3d_View QtViewController::internalOccView() const
{
  return m_view->internalView();
}

Handle_AIS_InteractiveContext QtViewController::context() const
{
  return m_view->context();
}

QtView* QtViewController::view() const
{
  return m_view;
}

const QRect QtViewController::rubberBandGeometry() const
{
  if (m_rubberBand == NULL)
    return QRect();
  return m_rubberBand->geometry();
}

// --- Implementation

void QtViewController::createRubberBand()
{
  if (m_rubberBand == NULL) {
    m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this->view());
    //_rubberBand->setWindowOpacity(0.7);
    // TODO Is this instruction really needed ?
    // m_rubberBand->setStyle(static_cast<QStyle*>(new QPlastiqueStyle()));
  }
}

} // namespace occ

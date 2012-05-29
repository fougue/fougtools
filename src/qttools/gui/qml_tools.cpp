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

#include "qttools/gui/qml_tools.h"

#include <QtDeclarative/QDeclarativeContext>
#include <QtGui/QApplication>
#include <QtGui/QCursor>

static Qt::CursorShape toQtCursorShape(int shape)
{
  switch (shape) {
  case Qt::ArrowCursor: return Qt::ArrowCursor;
  case Qt::UpArrowCursor: return Qt::UpArrowCursor;
  case Qt::CrossCursor: return Qt::CrossCursor;
  case Qt::WaitCursor: return Qt::WaitCursor;
  case Qt::IBeamCursor: return Qt::IBeamCursor;
  case Qt::SizeVerCursor: return Qt::SizeVerCursor;
  case Qt::SizeHorCursor: return Qt::SizeHorCursor;
  case Qt::SizeBDiagCursor: return Qt::SizeBDiagCursor;
  case Qt::SizeFDiagCursor: return Qt::SizeFDiagCursor;
  case Qt::SizeAllCursor: return Qt::SizeAllCursor;
  case Qt::BlankCursor: return Qt::BlankCursor;
  case Qt::SplitVCursor: return Qt::SplitVCursor;
  case Qt::SplitHCursor: return Qt::SplitHCursor;
  case Qt::PointingHandCursor: return Qt::PointingHandCursor;
  case Qt::ForbiddenCursor: return Qt::ForbiddenCursor;
  case Qt::WhatsThisCursor: return Qt::WhatsThisCursor;
  case Qt::BusyCursor: return Qt::BusyCursor;
  case Qt::OpenHandCursor: return Qt::OpenHandCursor;
  case Qt::ClosedHandCursor: return Qt::ClosedHandCursor;
  case Qt::DragCopyCursor: return Qt::DragCopyCursor;
  case Qt::DragMoveCursor: return Qt::DragMoveCursor;
  case Qt::DragLinkCursor: return Qt::DragLinkCursor;
  case Qt::BitmapCursor: return Qt::BitmapCursor;
  case Qt::CustomCursor: return Qt::CustomCursor;
  }
  return Qt::ArrowCursor;
}

namespace qttools {

QmlTools::QmlTools(QObject* parent)
  : QObject(parent)
{
}

void QmlTools::setOverrideCursor(int shape)
{
  QApplication::setOverrideCursor(QCursor(::toQtCursorShape(shape)));
}

void QmlTools::restoreOverrideCursor()
{
  QApplication::restoreOverrideCursor();
}

void QmlTools::declareObject(QDeclarativeContext* context, QmlTools* obj)
{
  if (obj != 0)
    context->setContextProperty(QLatin1String("qttools_QmlTools"), obj);
}

} // namespace qttools

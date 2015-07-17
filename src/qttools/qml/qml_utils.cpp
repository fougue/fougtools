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

#include "qml_utils.h"

#include <QtGui/QCursor>

#if QT_VERSION >= 0x050000
# include <QtGui/QGuiApplication>
# include <QtQml/QQmlContext>
#else
# include <QtDeclarative/QDeclarativeContext>
# include <QtGui/QApplication>
#endif // QT_VERSION

namespace qtqml {

namespace internal {

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

} // namespace internal

QmlUtils::QmlUtils(QObject* parent)
    : QObject(parent)
{
}

void QmlUtils::setOverrideCursor(int shape)
{
#if QT_VERSION >= 0x050000
    QGuiApplication::setOverrideCursor(QCursor(internal::toQtCursorShape(shape)));
#else
    QApplication::setOverrideCursor(QCursor(internal::toQtCursorShape(shape)));
#endif // QT_VERSION
}

void QmlUtils::restoreOverrideCursor()
{
#if QT_VERSION >= 0x050000
    QGuiApplication::restoreOverrideCursor();
#else
    QApplication::restoreOverrideCursor();
#endif // QT_VERSION
}

#if QT_VERSION >= 0x050000
void QmlUtils::declareObject(QQmlContext* context, QmlUtils* obj)
#else
void QmlUtils::declareObject(QDeclarativeContext* context, QmlUtils* obj)
#endif // QT_VERSION
{
    if (obj != NULL)
        context->setContextProperty(QLatin1String("qtqml_QmlUtils"), obj);
}

} // namespace qtqml

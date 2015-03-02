#include "qt_view_controller.h"

#include <QtCore/QDebug>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QApplication>
#include <QMenu>

#include <V3d_View.hxx>

#include <occtools/qt_view.h>

QtViewController::QtViewController(occ::QtView *qtView)
    : QObject(qtView),
      m_qtView(qtView)
{
    if (qtView != NULL) {
        qtView->installEventFilter(this);
        qtView->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(qtView, &QWidget::customContextMenuRequested,
                         this, &QtViewController::showActionMenu);
    }
}

bool QtViewController::eventFilter(QObject* watched, QEvent* event)
{
    const occ::QtView* qtView = qobject_cast<const occ::QtView*>(watched);
    if (qtView != m_qtView)
        return QObject::eventFilter(watched, event);
    Handle_V3d_View occView = qtView->internalView();

    //const Qt::KeyboardModifiers keybMods = QApplication::queryKeyboardModifiers();

    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        const QMouseEvent* mouseEvent = static_cast<const QMouseEvent*>(event);
        const QPoint currPos = qtView->mapFromGlobal(mouseEvent->globalPos());
        m_prevPos = currPos;
        if (mouseEvent->button() == Qt::LeftButton) {
            occView->StartRotation(currPos.x(), currPos.y());
            return true;
        }
        break;
    }
    case QEvent::MouseMove: {
        qDebug() << "Mouse move";
        const QMouseEvent* mouseEvent = static_cast<const QMouseEvent*>(event);
        const QPoint currPos = qtView->mapFromGlobal(mouseEvent->globalPos());
        const QPoint prevPos = m_prevPos;
        m_prevPos = currPos;

        if (QApplication::mouseButtons() == Qt::LeftButton) {
            occView->Rotation(currPos.x(), currPos.y());
            return true;
        }
        else if (QApplication::mouseButtons() == Qt::RightButton) {
            occView->Pan(currPos.x() - prevPos.x(), prevPos.y() - currPos.y());
            return true;
        }
        break;
    }
    case QEvent::Wheel: {
        const QWheelEvent* wheelEvent = static_cast<const QWheelEvent*>(event);
        Standard_Real currentScale = occView->Scale();
        if (wheelEvent->delta() > 0)
            currentScale *= 1.1; // +10%
        else
            currentScale /= 1.1; // -10%
        occView->SetScale(currentScale);
        return true;
    }
    default: return false;
    } // end switch

    return false;
}

void QtViewController::showActionMenu(const QPoint &pos)
{
    if (m_qtView != NULL) {
        QMenu menu;
        menu.addAction(tr("&Fit all"), m_qtView, SLOT(fitAll()));
        menu.exec(QCursor::pos());
    }
}

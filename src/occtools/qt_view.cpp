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

#include "qt_view.h"

#if defined(Q_OS_WIN32)
# include <windows.h>
#endif

#include <AIS_InteractiveContext.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <V3d_View.hxx>

#include <QtCore/QtDebug>

#include <QApplication>
#include <QtGui/QLinearGradient>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <GL/gl.h>
#include <GL/glu.h>

#if defined(Q_OS_WIN32)
# include <WNT_Window.hxx>
#elif defined(Q_OS_MAC) && !defined(MACOSX_USE_GLX)
# include <Cocoa_Window.hxx>
#else
# include <Aspect_DisplayConnection.hxx>
# include <Xw_Window.hxx> // OpenCascade
# include <X11/X.h>
#endif

#include <vector>
#include <unordered_map>

namespace occ {

//! QtView's pimpl
class QtView::Private
{
public:
    Private(const Handle_AIS_InteractiveContext& context3d, QtView *backPtr);

    void initialize();

    Handle_AIS_InteractiveContext m_context;
    Handle_V3d_View m_internalView;
    bool m_isInitialized;
    bool m_needsResize;

#ifndef OCCTOOLS_QTVIEW_NO_PAINTCALLBACK
    struct PaintCallbackData
    {
        int id;
        QtView::PaintCallback callback;
    };

    std::vector<PaintCallbackData> m_paintCallbacks;
#endif
    int m_paintCallbackLastId;
    Aspect_GraphicCallbackStruct* m_callbackData;

private:
    QtView* m_backPtr;
};

//! Callback executed each time a paint is requested (on paintEvent())
int occ_QtView_paintCallBack(
        Aspect_Drawable /*drawable*/,
        void* pointer,
        Aspect_GraphicCallbackStruct* data)
{
#ifndef OCCTOOLS_QTVIEW_NO_PAINTCALLBACK
    QtView::Private* d = reinterpret_cast<QtView::Private*>(pointer);
    d->m_callbackData = data;

    for (const auto& cbData : d->m_paintCallbacks)
        cbData.callback();

    d->m_callbackData = NULL;
#endif // !OCCTOOLS_QTVIEW_NO_PAINTCALLBACK

    return 0;
}

QtView::Private::Private(
        const Handle_AIS_InteractiveContext &context3d, QtView* backPtr)
    : m_context(context3d),
      m_isInitialized(false),
      m_needsResize(false),
      m_paintCallbackLastId(0),
      m_callbackData(NULL),
      m_backPtr(backPtr)
{
}

void QtView::Private::initialize()
{
    if (!m_isInitialized && m_backPtr->winId() != 0) {
        m_internalView = m_context->CurrentViewer()->CreateView();

#if defined(Q_OS_WIN32)
        Aspect_Handle winHandle = (Aspect_Handle)m_backPtr->winId();
        Handle_WNT_Window hWnd = new WNT_Window(winHandle);
#elif defined(Q_OS_MAC) && !defined(MACOSX_USE_GLX)
        NSView* viewHandle = (NSView*)m_backPtr->winId();
        Handle_Cocoa_Window hWnd = new Cocoa_Window(viewHandle);
#else
        Window winHandle = (Window)m_backPtr->winId();
        Handle_Aspect_DisplayConnection dispConnection =
                m_context->CurrentViewer()->Driver()->GetDisplayConnection();
        Handle_Xw_Window hWnd = new Xw_Window(dispConnection, winHandle);
#endif
        m_internalView->SetWindow(hWnd, NULL, &occ_QtView_paintCallBack, this);
        if (!hWnd->IsMapped())
            hWnd->Map();

        m_internalView->SetBgGradientColors(
                    Quantity_Color(0.5, 0.58, 1., Quantity_TOC_RGB),
                    Quantity_NOC_WHITE,
                    Aspect_GFM_VER);

        m_internalView->TriedronDisplay(
                    Aspect_TOTP_LEFT_LOWER,
                    Quantity_NOC_GRAY50,
                    0.1,
                    V3d_ZBUFFER);

        m_internalView->MustBeResized();
        m_isInitialized = true;
        m_needsResize = true;
    }
}

/*! \class QtView
 *  \brief Qt wrapper around the V3d_View class
 *
 *  QtView widgets are explicitly bound to a context ie an AIS_InteractiveContext. The context
 *  can be retrieved with context().
 *
 *  QtView does not handle input devices interaction like keyboard and mouse.
 *
 *  \headerfile qt_view.h <occtools/qt_view.h>
 *  \ingroup occtools
 */

//! Construct a QtView bound to the interactive context \p context3d, and having
//! \p parent as its Qt widget parent
QtView::QtView(const Handle_AIS_InteractiveContext& context3d, QWidget* parent)
    : QWidget(parent),
      d(new Private(context3d, this))
{
    this->setMouseTracking(true);

    // Avoid Qt background clears to improve resizing speed, along with a couple
    // of other attributes
    this->setAutoFillBackground(false);
    this->setAttribute(Qt::WA_NoSystemBackground);

    this->setAttribute(Qt::WA_PaintOnScreen);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setAttribute(Qt::WA_NativeWindow);
}

QtView::~QtView()
{
    delete d;
}

Handle_AIS_InteractiveContext QtView::context() const
{
    return d->m_context;
}

Handle_V3d_View QtView::internalView() const
{
    return d->m_internalView;
}

//! Hack for Qt 4.5.x
QPaintEngine* QtView::paintEngine() const
{
    return NULL;
}

//! Force a redraw of the view
void QtView::redraw()
{
    if (!d->m_internalView.IsNull()) {
        if (d->m_needsResize)
            d->m_internalView->MustBeResized();
        else
            d->m_internalView->Redraw();
    }
    d->m_needsResize = false;
}

#ifndef OCCTOOLS_QTVIEW_NO_PAINTCALLBACK
int QtView::addPaintCallback(const PaintCallback &callback)
{
    if (callback) {
        Private::PaintCallbackData cbData;
        cbData.id = ++(d->m_paintCallbackLastId);
        cbData.callback = callback;
        d->m_paintCallbacks.push_back(cbData);
        return cbData.id;
    }
    return -1;
}

void QtView::removePaintCallback(int callbackId)
{
    auto callbackIt =
            std::find_if(
                d->m_paintCallbacks.begin(),
                d->m_paintCallbacks.end(),
                [=] (const Private::PaintCallbackData& cbData) {
        return cbData.id == callbackId;
    } );
    if (callbackIt != d->m_paintCallbacks.end())
        d->m_paintCallbacks.erase(callbackIt);
}

Aspect_GraphicCallbackStruct *QtView::paintCallbackData() const
{
    return d->m_callbackData;
}

#endif // !OCCTOOLS_QTVIEW_NO_PAINTCALLBACK

void QtView::fitAll()
{
    if (!d->m_internalView.IsNull()) {
        d->m_internalView->ZFitAll();
        d->m_internalView->FitAll();
    }
}

//! Reimplemented from QWidget::paintEvent()
void QtView::paintEvent(QPaintEvent* /*event*/)
{
    d->initialize();
    if (!d->m_context->CurrentViewer().IsNull())
        this->redraw();
}

/*! \brief Reimplemented from QWidget::resizeEvent()
 *  Called when the widget needs to resize itself, but seeing as a paint event
 *  always follows a resize event, we'll move the work into the paint event
 */
void QtView::resizeEvent(QResizeEvent* /*event*/)
{
    d->m_needsResize = true;
}

} // namespace occ

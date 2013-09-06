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

#include "view.h"

#include <AIS_InteractiveContext.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <V3d_View.hxx>

#include <QtCore/QtDebug>
#include <QtCore/QHash>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
# include <QtWidgets/QApplication>
#else
# include <QtGui/QApplication>
#endif

#include <QtGui/QLinearGradient>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../utils.h"

#if defined(Q_OS_WIN32)
#include <WNT_Window.hxx>
#elif defined(Q_OS_MAC) && !defined(MACOSX_USE_GLX)
#include <Cocoa_Window.hxx>
#else
//#include <QX11Info>
//#include <GL/glx.h>
//#include <X11/Xutil.h>
//#include <X11/Xatom.h>
//#include <X11/Xmu/StdCmap.h>
//#include <X11/Xlib.h>
//#include <QtGui/QColormap>
#include <Aspect_DisplayConnection.hxx>
#include <Xw_Window.hxx> // OpenCascade
#include <X11/X.h>
#endif


/*!
 * \class occ::View
 * \brief Qt wrapper around the V3d_View class
 *
 * occ::View widgets are explicitely bound to a context ie an AIS_InteractiveContext. The context
 * can be retrieved with context().
 *
 * An occ::View does not handle input devices interaction like keyboard and mouse. It delegates this
 * responsability to an OccViewController.
 */

namespace occ {

class View::Private
{
public:
  Private(const Handle_AIS_InteractiveContext& context3d, View* backPtr);

  void initialize();

  Handle_AIS_InteractiveContext m_context;
  Handle_V3d_View m_internalView;
  bool m_isInitialized;
  bool m_needsResize;
  QList<View::PaintCallback> m_paintCallbacks;
  QHash<int, QList<View::PaintCallback>::iterator> m_paintCallbackMapping;
  int m_paintCallbackLastId;
  Aspect_GraphicCallbackStruct* m_callbackData;

  View* m_backPtr;
};

//! Callback executed each time a paint is requested (on paintEvent())
int paintCallBack(Aspect_Drawable drawable,
                  void* pointer,
                  Aspect_GraphicCallbackStruct* data)
{
  Q_UNUSED(drawable);

  View::Private* d = reinterpret_cast<View::Private*>(pointer);
  d->m_callbackData = data;

  foreach (const View::PaintCallback& callback, d->m_paintCallbacks)
    callback.execute();

  d->m_callbackData = NULL;

  /*    View* view = reinterpret_cast<View*>(pointer);

        glDisable(GL_LIGHTING);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        GLfloat left   = -1.0f;
        GLfloat right  =  1.0f;
        GLfloat bottom = -1.0f;
        GLfloat top    =  1.0f;
        GLfloat depth  =  1.0f;

        glOrtho(left, right, bottom, top, 1.0, -1.0);

    #ifndef OCC_PATCHED
        glEnable(GL_BLEND);
        if (view->internalView()->ColorScaleIsDisplayed())
        {
          // Not needed on patched OCC 6.2 versions, but is the lowest
          // common denominator working code on collaborators OpenGL
          // graphics cards.
          glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
        }
    #endif

        glBegin(GL_QUADS);
        {
          glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
          glVertex3d(left, bottom, depth);
          glVertex3d(right, bottom, depth);
          glColor4f(0.8f, 0.8f, 0.9f, 1.0f);
          glVertex3d(right,    top, depth);
          glVertex3d(left,    top, depth);
        }
        glEnd();

        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    */
  return 0;
}

View::Private::Private(const Handle_AIS_InteractiveContext &context3d, View* backPtr)
  : m_context(context3d),
    m_isInitialized(false),
    m_needsResize(false),
    m_paintCallbackLastId(0),
    m_callbackData(NULL),
    m_backPtr(backPtr)
{
}

void View::Private::initialize()
{
  if (!m_isInitialized && m_backPtr->winId() != 0) {
    m_internalView = m_context->CurrentViewer()->CreateView();

#if defined(Q_OS_WIN32)
    Aspect_Handle winHandle = (Aspect_Handle)m_backPtr->winId();
    Handle(WNT_Window) hWnd = new WNT_Window(winHandle);
#elif defined(Q_OS_MAC) && !defined(MACOSX_USE_GLX)
    NSView* viewHandle = (NSView*)m_backPtr->winId();
    Handle_Cocoa_Window hWnd = new Cocoa_Window(viewHandle);
#else
    Window winHandle = (Window)m_backPtr->winId();
    Handle_Aspect_DisplayConnection dispConnection = m_context->CurrentViewer()->Driver()->GetDisplayConnection();
    Handle_Xw_Window hWnd = new Xw_Window(dispConnection, winHandle);
#endif
    m_internalView->SetWindow(hWnd);
    if (!hWnd->IsMapped())
      hWnd->Map();

    m_internalView->SetBgGradientColors(occ::rgbColor(128, 147, 255), occ::rgbColor(255, 255, 255),
                                        Aspect_GFM_VER);

    m_internalView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER,
                                    occ::rgbColor(100, 100, 100).Name(),
                                    0.1,
                                    V3d_ZBUFFER);

    m_internalView->MustBeResized();
    m_isInitialized = true;
    m_needsResize = true;
  }
}

//! Construct an occ:View bound to the interactive context \p context3d, and
//! having \p parent as its Qt widget parent
View::View(const Handle_AIS_InteractiveContext& context3d, QWidget* parent) :
  QWidget(parent),
  d(new Private(context3d, this))
{
  this->setMouseTracking(true);

  // Avoid Qt background clears to improve resizing speed, along with a couple of other attributes
  this->setAutoFillBackground(false);
  this->setAttribute(Qt::WA_NoSystemBackground);

  // This next attribute seems to be the secret of allowing OCC on Win32 to "own" the window, even
  // though its only supposed to work on X11
  this->setAttribute(Qt::WA_PaintOnScreen);
  this->setAttribute (Qt::WA_OpaquePaintEvent);
#if (QT_VERSION >= QT_VERSION_CHECK(4, 4, 0))
  this->setAttribute(Qt::WA_NativeWindow);
#endif
}

View::~View()
{
  delete d;
}

// --- Access

//! Mutable bound interactive context
Handle_AIS_InteractiveContext& View::context()
{
  return d->m_context;
}

//! Read-only bound interactive context
const Handle_AIS_InteractiveContext& View::context() const
{
  return d->m_context;
}

Handle_V3d_View& View::internalView()
{
  return d->m_internalView;
}

const Handle_V3d_View& View::internalView() const
{
  return d->m_internalView;
}

// --- Drawing

//! Hack for Qt 4.5.x
QPaintEngine* View::paintEngine() const
{
  return NULL;
}

//! Force a redraw of the view (forcing depends on \p status )
void View::redraw(RedrawStatus /*status*/)
{
  if (!d->m_internalView.IsNull()) {
    if (d->m_needsResize) {
      d->m_internalView->MustBeResized();
      //this->viewPrecision( true );
    }
    else {
      d->m_internalView->Redraw();
      /*        // Don't repaint if we are already redrawing
        // elsewhere due to a keypress or mouse gesture
        if (status != IsPaintingStatus ||
            (status == IsPaintingStatus &&
             QApplication::mouseButtons() == Qt::NoButton))
        {
          m_internalView->Redraw();
        }*/
    }
  }
  d->m_needsResize = false;
}

int View::addPaintCallback(const PaintCallback &callback)
{
  if (callback.isValid()) {
    d->m_paintCallbacks.append(callback);
    d->m_paintCallbackMapping.insert(d->m_paintCallbackLastId, --(d->m_paintCallbacks.end()));
    return ++(d->m_paintCallbackLastId);
  }
  return -1;
}

void View::removePaintCallback(int callbackId)
{
  QList<PaintCallback>::iterator callbackIt =
      d->m_paintCallbackMapping.value(callbackId, d->m_paintCallbacks.end());
  if (callbackIt != d->m_paintCallbacks.end())
    d->m_paintCallbacks.erase(callbackIt);
}

Aspect_GraphicCallbackStruct *View::paintCallbackData() const
{
  return d->m_callbackData;
}

// --- Actions

void View::fitAll()
{
  if (!d->m_internalView.IsNull()) {
    d->m_internalView->ZFitAll();
    d->m_internalView->FitAll();
  }
}

// --- Event handling

/*! \brief Reimplemented from QWidget::paintEvent()
   */
void View::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event);

  d->initialize();
  if (!d->m_context->CurrentViewer().IsNull())
    this->redraw(IsPaintingStatus);
}

/*! \brief Reimplemented from QWidget::resizeEvent()
 *  Called when the Widget needs to resize itself, but seeing as a paint event always follows a
 *  resize event, we'll move the work into the paint event
 */
void View::resizeEvent(QResizeEvent* event)
{
  Q_UNUSED(event);
  d->m_needsResize = true;
}

} // namespace occ

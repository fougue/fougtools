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

#include "occtools/ui/view.h"

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#ifdef WNT
# include <Graphic3d_WNTGraphicDevice.hxx>
# include <WNT_Window.hxx>
#else
# include <Graphic3d_GraphicDevice.hxx>
# include <Xw_Window.hxx>
#endif // WNT

#include <QtGui/QApplication>
#include <QtGui/QLinearGradient>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtCore/QtDebug>
#include <GL/gl.h>
#include <GL/glu.h>

/*!
 * \class occ::View
 * \brief Qt wrapper around the V3d_View class
 *
 * occ::View widgets are explicitely bound to a context ie an
 * AIS_InteractiveContext. The context can be retrieved with context().
 *
 * An occ::View does not handle input devices interaction like keyboard and
 * mouse. It delegates this responsability to an OccViewController.
*/

namespace occ {

//! Construct an occ:View bound to the interactive context \p context3d, and
//! having \p parent as its Qt widget parent
View::View(const Handle_AIS_InteractiveContext& context3d, QWidget* parent) :
  QWidget(parent),
  _context(context3d),
  _isInitialized(false),
  _needsResize(false)
{
  this->setMouseTracking(true);
  // Avoid Qt background clears to improve resizing speed,
  // along with a couple of other attributes
  this->setAutoFillBackground(false);
  this->setAttribute(Qt::WA_NoSystemBackground);
  // This next attribute seems to be the secret of allowing OCC on Win32
  // to "own" the window, even though its only supposed to work on X11.
  this->setAttribute(Qt::WA_PaintOnScreen);
  this->setAttribute (Qt::WA_OpaquePaintEvent);
#if (QT_VERSION >= QT_VERSION_CHECK(4, 4, 0))
  this->setAttribute(Qt::WA_NativeWindow);
#endif
}

// --- Access

//! Mutable bound interactive context
Handle_AIS_InteractiveContext& View::context()
{
  return _context;
}

//! Read-only bound interactive context
const Handle_AIS_InteractiveContext& View::context() const
{
  return _context;
}

Handle_V3d_View& View::internalView()
{
  return _internalView;
}

const Handle_V3d_View& View::internalView() const
{
  return _internalView;
}

// --- Drawing

//! Hack for Qt 4.5.x
QPaintEngine* View::paintEngine() const
{
  return 0;
}

//! Force a redraw of the view (forcing depends on \p status )
void View::redraw(RedrawStatus /*status*/)
{
  if (!_internalView.IsNull()) {
    if (_needsResize) {
      _internalView->MustBeResized();
      //this->viewPrecision( true );
    }
    else
    {
      _internalView->Redraw();
      /*        // Don't repaint if we are already redrawing
        // elsewhere due to a keypress or mouse gesture
        if (status != IsPaintingStatus ||
            (status == IsPaintingStatus &&
             QApplication::mouseButtons() == Qt::NoButton))
        {
          _internalView->Redraw();
        }*/
    }
  }
  _needsResize = false;
}

// --- Actions

void View::fitAll()
{
  if (!_internalView.IsNull()) {
    _internalView->ZFitAll();
    _internalView->FitAll();
  }
}

// --- Event handling

/*! \brief Reimplemented from QWidget::paintEvent()
   */
void View::paintEvent(QPaintEvent* /*e*/)
{
  this->initialize();
  if (!_context->CurrentViewer().IsNull())
    this->redraw(IsPaintingStatus);
}

/*! \brief Reimplemented from QWidget::resizeEvent()
   *  Called when the Widget needs to resize itself, but seeing as a paint
   *  event always follows a resize event, we'll move the work into the
   *  paint event
  */
void View::resizeEvent(QResizeEvent* /*e*/)
{
  _needsResize = true;
}

// --- Implementation

//! Callback executed each time a paint is requested (on paintEvent())
int paintCallBack(Aspect_Drawable /*drawable*/,
                  void* /*pointer*/,
                  Aspect_GraphicCallbackStruct* /*data*/)
{
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

//! Initialize the internal V3d_View
void View::initialize()
{
  if (!_isInitialized && this->winId() != 0) {
    _internalView = _context->CurrentViewer()->CreateView();
    int windowHandle = (int)(this->winId());
    short hi = static_cast<short>(windowHandle >> 16);
    short lo = static_cast<short>(windowHandle);
    Handle_Aspect_GraphicDevice device =
        _context->CurrentViewer()->Device();
#ifdef WNT
    Handle_WNT_Window hWnd =
        new WNT_Window(Handle_Graphic3d_WNTGraphicDevice::DownCast(device),
                       static_cast<Standard_Integer>(hi),
                       static_cast<Standard_Integer>(lo));
    hWnd->SetFlags(WDF_NOERASEBKGRND);
#else
    Handle_Xw_Window hWnd =
        new Xw_Window(Handle(Graphic3d_GraphicDevice)::DownCast(device),
                      static_cast<Standard_Integer>(hi),
                      static_cast<Standard_Integer>(lo),
                      Xw_WQ_SAMEQUALITY);
#endif // WNT
    Aspect_RenderingContext rc = 0;
    _internalView->SetWindow(hWnd, rc, paintCallBack, this);
    //_internalView->SetScale(2);
    if (!hWnd->IsMapped())
      hWnd->Map();

    const int w = 5;
    const int h = 500;
    QPixmap pixmap(w, h);
    QPainter painter(&pixmap);
    QLinearGradient gradient(0.0, 0.0, w, h);
    gradient.setColorAt(0.0, QColor(128, 147, 255));
    gradient.setColorAt(1.0, Qt::white);
    painter.setBrush(gradient);
    painter.fillRect(0.0, 0.0, w, h, gradient);
    if (pixmap.save("temp_bkgnd.bmp"))
    {
      _internalView->SetBackgroundImage("temp_bkgnd.bmp");
      _internalView->SetBgImageStyle(Aspect_FM_STRETCH);
    }

    _internalView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER,
                                         Quantity_NOC_BLACK,
                                         0.1, V3d_ZBUFFER);
    _internalView->MustBeResized();
    _isInitialized = true;
    _needsResize = true;
  }
}

} // namespace occ

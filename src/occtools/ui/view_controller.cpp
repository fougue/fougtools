#include "occtools/ui/view_controller.h"

#include <QtGui/QKeyEvent>
#include <QtGui/QPlastiqueStyle>
#include <QtGui/QRubberBand>
#include "occtools/ui/view.h"

namespace occ {

ViewController::ViewController(View* view) :
  QObject(view),
  _view(view),
  _rubberBand(0)
{
}

// -- Rubber band handling

void ViewController::beginRubberBandDraw(const QPoint& startPos)
{
  this->createRubberBand();
  _startRubberBandPos = startPos;
  _rubberBand->setGeometry(QRect(startPos, QSize()));
  _rubberBand->show();
}

void ViewController::updateRubberBandDraw(const QPoint& currPos)
{
  this->createRubberBand();
  _rubberBand->hide();
  QRect window(_startRubberBandPos, currPos);
  _rubberBand->setGeometry(window.normalized());
  _rubberBand->show();
}

void ViewController::endRubberBandDraw()
{
  this->createRubberBand();
  _rubberBand->hide();
}

// --- Event handling

bool ViewController::eventFilter(QObject* object, QEvent* event)
{
  return QObject::eventFilter(object, event);
}

void ViewController::notifyContextSelectionChanged()
{
  emit contextSelectionChanged();
}

void ViewController::notifyEscaped()
{
  emit escaped();
}

// --- Access

const Handle_V3d_View& ViewController::internalOccView() const
{
  return _view->internalView();
}

Handle_V3d_View& ViewController::internalOccView()
{
  return _view->internalView();
}

const Handle_AIS_InteractiveContext& ViewController::context() const
{
  return _view->context();
}

Handle_AIS_InteractiveContext& ViewController::context()
{
  return _view->context();
}

const View* ViewController::view() const
{
  return _view;
}

View* ViewController::view()
{
  return _view;
}

const QRect ViewController::rubberBandGeometry() const
{
  if (_rubberBand == 0)
    return QRect();
  return _rubberBand->geometry();
}

// --- Implementation

void ViewController::createRubberBand()
{
  if (_rubberBand == 0) {
    _rubberBand = new QRubberBand(QRubberBand::Rectangle, this->view());
    //_rubberBand->setWindowOpacity(0.7);
    // TODO Is this instruction really needed ?
    _rubberBand->setStyle(static_cast<QStyle*>(new QPlastiqueStyle()));
  }
}

} // namespace occ

#ifndef OCC_VIEW_CONTROLLER_H
#define OCC_VIEW_CONTROLLER_H

#include "occtools/occtools.h"
#include <Handle_AIS_InteractiveContext.hxx>
#include <Handle_V3d_View.hxx>
#include <QtCore/QObject>
#include <QtCore/QRect>
class QPoint;
class QRubberBand;

namespace occ {

class View;
class ViewControllerDelegate;

class OCCTOOLS_EXPORT ViewController : public QObject
{
  Q_OBJECT

public:
  friend class ViewControllerDelegate;

  ViewController(View* view);

signals:
  void contextSelectionChanged();
  void escaped();

protected:
  // -- Rubber band handling
  virtual void beginRubberBandDraw(const QPoint& startPos);
  virtual void updateRubberBandDraw(const QPoint& currPos);
  virtual void endRubberBandDraw();

  // --- Event handling
  bool eventFilter(QObject* object, QEvent* event);
  void notifyContextSelectionChanged();
  void notifyEscaped();

public:
  // --- Access
  const Handle_V3d_View& internalOccView() const;
  Handle_V3d_View& internalOccView();

  const Handle_AIS_InteractiveContext& context() const;
  Handle_AIS_InteractiveContext& context();

  const View* view() const;
  View* view();

protected:
  const QRect rubberBandGeometry() const;

  View* _view;

private:
  void createRubberBand();

  QPoint _startRubberBandPos;
  QRubberBand* _rubberBand;
};

} // namespace occ

#endif // OCC_VIEW_CONTROLLER_H

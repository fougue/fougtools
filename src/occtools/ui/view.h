#ifndef OCC_VIEW_H
#define OCC_VIEW_H

#include "occtools/occtools.h"
#include <QtGui/QWidget>
#include <Handle_AIS_InteractiveContext.hxx>
#include <Handle_V3d_View.hxx>

namespace occ {

class OCCTOOLS_EXPORT View : public QWidget
{
  Q_OBJECT

public:
  enum RedrawStatus
  {
    IsPaintingStatus,
    NopStatus
  };

  View(const Handle_AIS_InteractiveContext& context3d, QWidget* parent = 0);

  Handle_AIS_InteractiveContext& context();
  const Handle_AIS_InteractiveContext& context() const;

  Handle_V3d_View& internalView();
  const Handle_V3d_View& internalView() const;

  QPaintEngine* paintEngine() const;

  void redraw(RedrawStatus status = NopStatus);

public slots:
  void fitAll();

protected:
  void paintEvent(QPaintEvent* e);
  void resizeEvent(QResizeEvent* e);

private:
  void initialize();

  Handle_AIS_InteractiveContext _context;
  Handle_V3d_View _internalView;
  bool _isInitialized;
  bool _needsResize;
};

} // namespace occ

#endif // OCC_VIEW_H

#ifndef OCC_PROJECTION_SELECTOR_ACTION_MANAGER_H
#define OCC_PROJECTION_SELECTOR_ACTION_MANAGER_H

#include "occtools/occtools.h"
#include <QtCore/QObject>
#include <V3d_TypeOfOrientation.hxx>
class QAction;
class QSignalMapper;

namespace occ {

class OCCTOOLS_EXPORT ProjectionSelectorActionManager : public QObject
{
  Q_OBJECT

public:
  ProjectionSelectorActionManager(QObject* parent = 0);

  QAction* mainAction();

  void triggerViewProjection(V3d_TypeOfOrientation proj);

signals:
  void viewProjectionTriggered(V3d_TypeOfOrientation proj);

private slots:
  void onMainActionTriggered(bool checked);
  void onViewProjActionTriggered(int projId);

private:
  QAction* mappedAction(int projId) const;

  QAction* _mainAction;
  V3d_TypeOfOrientation _currOrientation;
  QSignalMapper* _signalMapper;
};

} // namespace occ

#endif // OCC_PROJECTION_SELECTOR_ACTION_MANAGER_H

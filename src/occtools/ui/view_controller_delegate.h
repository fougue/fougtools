#ifndef OCC_VIEW_CONTROLLER_DELEGATE_H
#define OCC_VIEW_CONTROLLER_DELEGATE_H

#include "occtools/occtools.h"
class QString;

namespace occ {

class ViewController;

class OCCTOOLS_EXPORT ViewControllerDelegate
{
public:
  virtual void tellController(occ::ViewController* ctrl) = 0;

protected:
  virtual occ::ViewController* controller() = 0;

  void notifyContextSelectionChanged();
  void notifyEscaped();
};

} // namespace occ

#endif // OCC_VIEW_CONTROLLER_DELEGATE_H

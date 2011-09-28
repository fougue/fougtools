#include "occtools/ui/view_controller_delegate.h"

#include "occtools/ui/view_controller.h"

namespace occ {

// --- Event management

void ViewControllerDelegate::notifyContextSelectionChanged()
{
  if (0 != this->controller())
    this->controller()->notifyContextSelectionChanged();
}

void ViewControllerDelegate::notifyEscaped()
{
  if (0 != this->controller())
    this->controller()->notifyEscaped();
}

} // namespace occ

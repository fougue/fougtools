/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
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

#include "strict_stack_widget.h"

#include <QtCore/QStack>
#include <QStackedWidget>
#include <QBoxLayout>

namespace qttools {

class StrictStackWidget::Private
{
public:
  Private(StrictStackWidget* backPtr)
    : m_implWidget(backPtr)
  {
  }

  QStackedWidget* stackWidget()
  {
    return &m_implWidget;
  }

  QStack<int> m_stackWidgetId;

private:
  QStackedWidget m_implWidget;
};

/*! \class StrictStackWidget
 *  \brief Provides a stack of widgets similar to QStackedWidget but with "strict" stack semantics
 *
 *  QStackedWidget can be seen as a page-based widget rather than a stack widget. StrictStackWidget
 *  provides strict stack semantics applied to widgets : the only widget visible is the top widget.
 *
 *  When popWidget() is called it destroys the top widget and then makes visible the previous
 *  widget (if any), becoming the new top widget.
 *
 *  \headerfile strict_stack_widget.h <qttools/gui/strict_stack_widget.h>
 *  \ingroup qttools_gui
 */

StrictStackWidget::StrictStackWidget(QWidget *parent)
  : QWidget(parent),
    d(new Private(this))
{
  QBoxLayout* boxLayout = new QVBoxLayout;
  boxLayout->addWidget(d->stackWidget());
  boxLayout->setContentsMargins(0, 0, 0, 0);
  this->setLayout(boxLayout);
}

StrictStackWidget::~StrictStackWidget()
{
  delete d;
}

/*! \brief Adds \p widget to the top of the stack (and makes it the visible widget)
 */
void StrictStackWidget::pushWidget(QWidget *widget)
{
  if (widget != NULL) {
    const int widgetId = d->stackWidget()->addWidget(widget);
    d->m_stackWidgetId.push(widgetId);
    d->stackWidget()->setCurrentIndex(widgetId);
  }
}

/*! \brief Destroys the top widget from the stack
 *
 *  Does nothing if stack is empty
 */
QWidget *StrictStackWidget::popWidget()
{
  if (!this->isEmpty()) {
    const int widgetId = d->m_stackWidgetId.pop();
    QWidget* widget = d->stackWidget()->widget(widgetId);
    d->stackWidget()->removeWidget(widget);
    if (!this->isEmpty())
      d->stackWidget()->setCurrentIndex(d->m_stackWidgetId.top());
    return widget;
  }
  else {
    return NULL;
  }
}

/*! \brief Retruns \c true if the stack contains no widget, otherwise returns \c false
 */
bool StrictStackWidget::isEmpty() const
{
  return d->m_stackWidgetId.isEmpty();
}

/*! \brief Returns a pointer to the stack's top widget
 *
 *  If stack is empty, NULL is returned
 */
QWidget *StrictStackWidget::topWidget() const
{
  if (!this->isEmpty())
    return d->stackWidget()->widget(d->m_stackWidgetId.top());
  else
    return NULL;
}

} // namespace qttools

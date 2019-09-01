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

#include "strict_stack_widget.h"

#include <QtCore/QStack>
#include <QStackedWidget>
#include <QBoxLayout>

namespace qtgui {

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
 *  \brief Provides a stack of widgets similar to QStackedWidget but with
 *         "strict" stack semantics
 *
 *  QStackedWidget can be seen as a page-based widget rather than a stack
 *  widget. StrictStackWidget provides strict stack semantics applied to
 *  widgets : the only widget visible is the top widget.
 *
 *  When popWidget() is called it destroys the top widget and then makes visible
 *  the previous widget (if any), becoming the new top widget.
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

/*! Adds \p widget to the top of the stack (and makes it the visible widget)
 */
void StrictStackWidget::pushWidget(QWidget *widget)
{
    if (widget != NULL) {
        const int widgetId = d->stackWidget()->addWidget(widget);
        d->m_stackWidgetId.push(widgetId);
        d->stackWidget()->setCurrentIndex(widgetId);
    }
}

/*! Destroys the top widget from the stack
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

/*! \brief Returns \c true if the stack contains no widget, otherwise returns \c false
 */
bool StrictStackWidget::isEmpty() const
{
    return d->m_stackWidgetId.isEmpty();
}

/*! Returns a pointer to the stack's top widget
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

} // namespace qtgui

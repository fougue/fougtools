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

#pragma once

#include "occtools.h"
#include <Handle_AIS_InteractiveContext.hxx>
#include <Handle_V3d_View.hxx>
#include <QtCore/QObject>
#include <QtCore/QRect>
class QPoint;
class QRubberBand;

namespace occ {

class QtView;
class ViewControllerDelegate;

class OCCTOOLS_EXPORT QtViewController : public QObject
{
    Q_OBJECT

public:
    friend class ViewControllerDelegate;

    QtViewController(QtView* view);

    bool eventFilter(QObject* object, QEvent* event);

signals:
    void contextSelectionChanged();
    void escaped();

protected:
    virtual void beginRubberBandDraw(const QPoint& startPos);
    virtual void updateRubberBandDraw(const QPoint& currPos);
    virtual void endRubberBandDraw();

    void notifyContextSelectionChanged();
    void notifyEscaped();

public:
    Handle_V3d_View internalOccView() const;
    Handle_AIS_InteractiveContext context() const;
    QtView* view() const;

protected:
    const QRect rubberBandGeometry() const;

private:
    void createRubberBand();

    QtView* m_view;
    QPoint m_startRubberBandPos;
    QRubberBand* m_rubberBand;
};

} // namespace occ

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

#ifndef OCCTOOLS_QTVIEW_NO_PAINTCALLBACK
# include <functional>
#endif

#include <QWidget>

#include <Aspect_GraphicCallbackProc.hxx>
#include <Handle_AIS_InteractiveContext.hxx>
#include <Handle_V3d_View.hxx>

namespace occ {

// Obsolete use QWidgetView3d
class OCCTOOLS_EXPORT QtView : public QWidget
{
    Q_OBJECT

public:
    QtView(const Handle_AIS_InteractiveContext& context3d,
           QWidget* parent = NULL);
    ~QtView();

    Handle_AIS_InteractiveContext context() const;
    Handle_V3d_View internalView() const;

#ifndef OCCTOOLS_QTVIEW_NO_PAINTCALLBACK
    typedef std::function<void()> PaintCallback;
    int addPaintCallback(const PaintCallback& callback);
    void removePaintCallback(int callbackId);
    Aspect_GraphicCallbackStruct* paintCallbackData() const;
#endif

    QPaintEngine* paintEngine() const override;

public slots:
    void redraw();
    void fitAll();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    friend int occ_QtView_paintCallBack(
            Aspect_Drawable, void*, Aspect_GraphicCallbackStruct*);
    class Private;
    Private* const d;
};

} // namespace occ

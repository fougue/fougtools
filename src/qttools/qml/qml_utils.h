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

#include "qml.h"
#include <QtCore/QObject>
#if QT_VERSION >= 0x050000
class QQmlContext;
#else
class QDeclarativeContext;
#endif // QT_VERSION

namespace qtqml {

class QTTOOLS_QML_EXPORT QmlUtils : public QObject
{
    Q_OBJECT

public:
    QmlUtils(QObject* parent = NULL);

    Q_INVOKABLE void setOverrideCursor(int shape);
    Q_INVOKABLE void restoreOverrideCursor();

#if QT_VERSION >= 0x050000
    static void declareObject(QQmlContext* context, QmlUtils* obj);
#else
    static void declareObject(QDeclarativeContext* context, QmlUtils* obj);
#endif // QT_VERSION
};

} // namespace qtqml

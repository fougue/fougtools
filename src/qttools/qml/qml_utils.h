/****************************************************************************
**
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
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

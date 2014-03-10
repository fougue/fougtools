include(../../../qmake/config.pri)

TEMPLATE = app
TARGET   = qtviewer$$TARGET_SUFFIX

QT += gui
isEqual(QT_MAJOR_VERSION, 5): QT += widgets

FOUGTOOLS_SRCDIR = $$PWD/../../../src
INCLUDEPATH += $$FOUGTOOLS_SRCDIR

HEADERS += \
    $$FOUGTOOLS_SRCDIR/occtools/qt_view.h \
    $$PWD/qt_view_controller.h

SOURCES += \
    $$FOUGTOOLS_SRCDIR/occtools/qt_view.cpp \
    $$PWD/main.cpp \
    $$PWD/qt_view_controller.cpp

include(../../../src/occtools/occ.pri)
LIBS += -lTKernel -lTKMath -lTKBRep -lTKService -lTKV3d

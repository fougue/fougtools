include(../../../qmake/config.pri)

TEMPLATE = app
TARGET   = tree_combo_box$$TARGET_SUFFIX

QT += gui
isEqual(QT_MAJOR_VERSION, 5): QT += widgets

FOUGTOOLS_SRCDIR = $$PWD/../../../src
INCLUDEPATH += $$FOUGTOOLS_SRCDIR

HEADERS += \
    $$FOUGTOOLS_SRCDIR/qttools/gui/tree_combo_box.h

SOURCES += \
    $$FOUGTOOLS_SRCDIR/qttools/gui/tree_combo_box.cpp \
    $$PWD/main.cpp

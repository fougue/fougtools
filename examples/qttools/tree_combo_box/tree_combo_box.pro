TEMPLATE = app
TARGET   = tree_combo_box

CONFIG += console

QT += gui
isEqual(QT_MAJOR_VERSION, 5): QT += widgets

FOUGTOOLS_SRCDIR = ../../../src
INCLUDEPATH += $$FOUGTOOLS_SRCDIR

HEADERS += \
    $$FOUGTOOLS_SRCDIR/qttools/gui/tree_combo_box.h

SOURCES += \
    $$FOUGTOOLS_SRCDIR/qttools/gui/tree_combo_box.cpp \
    main.cpp

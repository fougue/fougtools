TEMPLATE = app
TARGET   = length_editor

CONFIG += console

QT += gui
isEqual(QT_MAJOR_VERSION, 5): QT += widgets

FOUGTOOLS_SRCDIR = ../../../src
INCLUDEPATH += $$FOUGTOOLS_SRCDIR

HEADERS += \
    $$FOUGTOOLS_SRCDIR/qttools/gui/abstract_length_editor.h \
    $$FOUGTOOLS_SRCDIR/qttools/gui/abstract_quantity_editor.h \
    $$FOUGTOOLS_SRCDIR/qttools/gui/length_double_spinbox.h \
    $$FOUGTOOLS_SRCDIR/qttools/gui/quantity_editor_manager.h \
    length_editor_widget.h

SOURCES += \
    $$FOUGTOOLS_SRCDIR/qttools/gui/abstract_length_editor.cpp \
    $$FOUGTOOLS_SRCDIR/qttools/gui/abstract_quantity_editor.cpp \
    $$FOUGTOOLS_SRCDIR/qttools/gui/length_double_spinbox.cpp \
    $$FOUGTOOLS_SRCDIR/qttools/gui/quantity_editor_manager.cpp \
    main.cpp \
    length_editor_widget.cpp

FORMS += \
    length_editor_widget.ui

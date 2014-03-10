include(../../../qmake/config.pri)

TEMPLATE = app
TARGET   = item_view_buttons$$TARGET_SUFFIX

QT += gui
isEqual(QT_MAJOR_VERSION, 5): QT += widgets

FOUGTOOLS_SRCDIR = $$PWD/../../../src
INCLUDEPATH += $$FOUGTOOLS_SRCDIR

HEADERS += \
    $$FOUGTOOLS_SRCDIR/qttools/gui/proxy_styled_item_delegate.h \
    $$FOUGTOOLS_SRCDIR/qttools/gui/item_view_buttons.h

SOURCES += \
    $$FOUGTOOLS_SRCDIR/qttools/gui/proxy_styled_item_delegate.cpp \
    $$FOUGTOOLS_SRCDIR/qttools/gui/item_view_buttons.cpp \
    $$PWD/main.cpp

RESOURCES += $$PWD/item_view_buttons.qrc

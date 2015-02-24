INCLUDEPATH *= $$PWD/.. $$PWD/../..

QT += gui
isEqual(QT_MAJOR_VERSION, 4): QT += declarative
isEqual(QT_MAJOR_VERSION, 5): QT += qml

HEADERS += \
    $$PWD/qml.h \
    $$PWD/qml_utils.h

SOURCES += \
    $$PWD/qml_utils.cpp

TEMPLATE = app
TARGET = utest

CONFIG *= console
QT *= testlib

HEADERS += \
    test_cpptools.h \
    test_qttools_core.h \
    \
    ../src/qttools/core/wait_loop.h

SOURCES += \
    main.cpp \
    test_cpptools.cpp \
    test_qttools_core.cpp \
    \
    ../src/qttools/core/wait_loop.cpp

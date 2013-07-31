TEMPLATE = app

CONFIG(debug, debug|release) {
  TARGET_SUFFIX = .debug
} else {
  TARGET_SUFFIX = .release
}
TARGET = utest$$TARGET_SUFFIX

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

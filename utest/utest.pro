include(../qmake/config.pri)

TEMPLATE = app

CONFIG(debug, debug|release) {
  TARGET_SUFFIX = _d
} else {
  TARGET_SUFFIX =
}
TARGET = utest$$TARGET_SUFFIX

CONFIG += console
QT += testlib  script

HEADERS += \
    $$PWD/test_cpptools.h \
    $$PWD/test_qttools_core.h \
    $$PWD/test_qttools_script.h \
    \
    $$PWD/../src/qttools/core/qlocale_tools.h \
    $$PWD/../src/qttools/core/wait_loop.h \
    $$PWD/../src/qttools/core/wait_loop_stop_condition.h \
    $$PWD/../src/qttools/core/internal/wait_loop_p.h \
    $$PWD/../src/qttools/core/internal/wait_loop_time_out_stop_condition.h \
    \
    $$PWD/../src/qttools/script/calculator.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/test_cpptools.cpp \
    $$PWD/test_qttools_core.cpp \
    $$PWD/test_qttools_script.cpp \
    \
    $$PWD/../src/qttools/core/qlocale_tools.cpp \
    $$PWD/../src/qttools/core/wait_loop.cpp \
    $$PWD/../src/qttools/core/wait_loop_stop_condition.cpp \
    $$PWD/../src/qttools/core/internal/wait_loop_p.cpp \
    $$PWD/../src/qttools/core/internal/wait_loop_time_out_stop_condition.cpp \
    \
    $$PWD/../src/qttools/script/calculator.cpp

include(../config.pri)

TEMPLATE = lib

TARGET = qttools_core$$TARGET_SUFFIX

QT -= gui
CONFIG += dll
CONFIG(dll):DEFINES += QTTOOLS_CORE_DLL QTTOOLS_CORE_MAKE_DLL

include(../../src/qttools/core/qttools_core.pri)

qttools_core_include.path  = $$QTTOOLS_INC_PATH/qttools/core
qttools_core_include.files = ../../src/qttools/core/*.h
target.path = $$QTTOOLS_LIB_PATH
INSTALLS += qttools_core_include target

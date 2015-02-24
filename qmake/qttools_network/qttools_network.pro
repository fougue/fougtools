include(../config.pri)

TEMPLATE = lib
TARGET = qttools_network$$TARGET_SUFFIX

CONFIG += dll
CONFIG(dll):DEFINES += QTTOOLS_NETWORK_DLL QTTOOLS_NETWORK_MAKE_DLL

QT -= gui

include(../../src/qttools/network/qttools_network.pri)

qttools_network_include.path  = $$QTTOOLS_INC_PATH/qttools/network
qttools_network_include.files = ../../src/qttools/network/*.h
target.path = $$QTTOOLS_LIB_PATH
INSTALLS += qttools_network_include target

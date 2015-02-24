include(../lib_config.pri)

TARGET = qttools_network$$TARGET_SUFFIX

QT -= gui
CONFIG(dll):DEFINES += QTTOOLS_NETWORK_DLL QTTOOLS_NETWORK_MAKE_DLL

include(../../src/qttools/network/qttools_network.pri)

qttools_network_include.path  = $$QTTOOLS_INC_PATH/qttools/network
qttools_network_include.files = ../../src/qttools/network/*.h
target.path = $$QTTOOLS_LIB_PATH
INSTALLS += qttools_network_include target

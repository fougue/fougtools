include(../config.pri)

TEMPLATE = lib

TARGET = qttools_qml$$TARGET_SUFFIX

CONFIG += dll
CONFIG(dll):DEFINES += QTTOOLS_QML_DLL QTTOOLS_QML_MAKE_DLL

include(../../src/qttools/qml/qttools_qml.pri)

qttools_qml_include.path  = $$QTTOOLS_INC_PATH/qttools/qml
qttools_qml_include.files = ../../src/qttools/qml/*.h
target.path = $$QTTOOLS_LIB_PATH
INSTALLS += qttools_qml_include target

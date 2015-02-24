include(../config.pri)

TEMPLATE = lib

TARGET = qttools_gui$$TARGET_SUFFIX

CONFIG += dll
CONFIG(dll):DEFINES += QTTOOLS_GUI_DLL QTTOOLS_GUI_MAKE_DLL

include(../../src/qttools/gui/qttools_gui.pri)

qttools_gui_include.path  = $$QTTOOLS_INC_PATH/qttools/gui
qttools_gui_include.files = ../../src/qttools/gui/*.h
target.path = $$QTTOOLS_LIB_PATH
INSTALLS += qttools_gui_include target

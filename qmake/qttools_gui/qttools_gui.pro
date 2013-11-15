include(../config.pri)
CONFIG *= dll
include(../../src/qttools/gui/build_qttools_gui.pri)

qttools_gui_include.path  = $$QTTOOLS_INC_PATH/qttools/gui
qttools_gui_include.files = ../../src/qttools/gui/*.h
INSTALLS += qttools_gui_include

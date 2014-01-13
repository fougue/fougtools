include(../config.pri)
CONFIG += dll
#DEFINES *= DEBUG_ABSTRACT_PLUGIN_LOADER
include(../../src/qttools/script/build_qttools_script.pri)

qttools_script_include.path  = $$QTTOOLS_INC_PATH/qttools/script
qttools_script_include.files = ../../src/qttools/script/*.h
INSTALLS += qttools_script_include

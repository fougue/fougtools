include(../config.pri)
CONFIG += dll
#DEFINES *= DEBUG_ABSTRACT_PLUGIN_LOADER
include(../../src/qttools/core/build_qttools_core.pri)

qttools_core_include.path  = $$QTTOOLS_INC_PATH/qttools/core
qttools_core_include.files = ../../src/qttools/core/*.h
INSTALLS += qttools_core_include

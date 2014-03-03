include(../config.pri)
CONFIG += dll
#DEFINES += DEBUG_ABSTRACT_PLUGIN_LOADER
include(../../src/qttools/script/build_qttools_script.pri)

qttools_script_include.path  = $$QTTOOLS_INC_PATH/qttools/script
qttools_script_include.files = ../../src/qttools/script/*.h

qttools_script_src.path  = $$PREFIX_DIR/src/qttools/script
qttools_script_src.files = ../../src/qttools/script/*.h \
                           ../../src/qttools/script/*.cpp \
                           ../../src/qttools/script/qttools_script.pri

target.path = $$QTTOOLS_LIB_PATH

INSTALLS += qttools_script_include \
            qttools_script_src \
            target

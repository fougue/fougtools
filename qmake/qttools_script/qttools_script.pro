include(../lib_config.pri)

TARGET = qttools_script$$TARGET_SUFFIX

CONFIG(dll):DEFINES += QTTOOLS_SCRIPT_DLL QTTOOLS_SCRIPT_MAKE_DLL

include(../../src/qttools/script/qttools_script.pri)

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

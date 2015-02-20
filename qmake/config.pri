include(func_cleanpath.pri)

isEmpty(FOUGTOOLS_BUILD_ROOT) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    FOUGTOOLS_BUILD_ROOT = $$cleanPath($$OUT_PWD)
    FOUGTOOLS_BUILD_ROOT ~= s,$$re_escape($$sub_dir)$,,
}
#message($$FOUGTOOLS_BUILD_ROOT)

include(compiler_config.pri)
!include($$FOUGTOOLS_BUILD_ROOT/_local_config.pri) {
    error(File $$FOUGTOOLS_BUILD_ROOT/_local_config.pri not found)
}

QTTOOLS_INC_PATH = $$PREFIX_DIR/include
QTTOOLS_LIB_PATH = $$PREFIX_DIR/lib
OCCTOOLS_INC_PATH = $$PREFIX_DIR/include
OCCTOOLS_LIB_PATH = $$PREFIX_DIR/lib
CONFIG(debug, debug|release) {
    TARGET_SUFFIX = _d
} else {
    TARGET_SUFFIX =
}
CONFIG += build_all

occtools:DEFINES += FOUGTOOLS_OCCTOOLS

# Declare and define function cleanPath(string)
isEqual(QT_MAJOR_VERSION, 5) {

    defineReplace(cleanPath) {
        return($$clean_path($$1))
    }

} else { # qt5

    defineReplace(cleanPath) {
        win32:1 ~= s|\\\\|/|g
        contains(1, ^/.*):pfx = /
        else:pfx =
        segs = $$split(1, /)
        out =
        for(seg, segs) {
            equals(seg, ..):out = $$member(out, 0, -2)
            else:!equals(seg, .):out += $$seg
        }
        return($$join(out, /, $$pfx))
    }

} # qt5

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
CONFIG *= build_all debug_and_release

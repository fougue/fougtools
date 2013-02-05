include(compiler_config.pri)
!include(_local_config.pri) {
  error(File _local_config.pri not found)
}

QTTOOLS_INC_PATH = $$PREFIX_DIR/include
QTTOOLS_LIB_PATH = $$PREFIX_DIR/lib
OCCTOOLS_INC_PATH = $$PREFIX_DIR/include
OCCTOOLS_LIB_PATH = $$PREFIX_DIR/lib
CONFIG(debug, debug|release) {
  TARGET_SUFFIX = .debug
} else {
  TARGET_SUFFIX = .release
}
CONFIG *= build_all debug_and_release

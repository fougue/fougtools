include(compiler_config.pri)
!include(_local_config.pri) {
  error(File _local_config.pri not found)
}
CASCADE_ROOT = $$(CASROOT)

QTTOOLS_INC_PATH = $$_PREFIX/include
QTTOOLS_LIB_PATH = $$_PREFIX/lib
OCCTOOLS_INC_PATH = $$_PREFIX/include
OCCTOOLS_LIB_PATH = $$_PREFIX/lib
CONFIG(debug, debug|release) {
  TARGET_SUFFIX = .debug
} else {
  TARGET_SUFFIX = .release
}
CONFIG *= build_all debug_and_release

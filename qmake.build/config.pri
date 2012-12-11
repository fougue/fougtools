include(compiler_config.pri)
!include(_local_config.pri) {
  error(File _local_config.pri not found)
}
CASCADE_ROOT = $$(CASROOT)

QTTOOLS_LIB_PATH = $$PWD/bin
OCCTOOLS_LIB_PATH = $$PWD/bin
CONFIG(debug, debug|release) {
  TARGET_SUFFIX = .debug
} else {
  TARGET_SUFFIX = .release
}
CONFIG *= build_all debug_and_release

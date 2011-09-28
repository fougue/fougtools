include(compiler_config.pri)
QTTOOLS_LIB_PATH = $$PWD/bin
CONFIG(debug, debug|release) {
  TARGET_SUFFIX = .debug
} else {
  TARGET_SUFFIX = .release
}
message($$QTTOOLS_LIB_PATH)

!include($$[QT_INSTALL_PREFIX]/qttools/src/qtconcurrent/codegenerator/codegenerator.pri) {
  error(Not found $$[QT_INSTALL_PREFIX])
}

TEMPLATE = app

SOURCES += main.cpp

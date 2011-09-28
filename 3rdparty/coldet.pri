message($$COLDET_ROOT)
INCLUDEPATH *= $$COLDET_ROOT/src
LIBS *= -L$$COLDET_ROOT/bin
CONFIG(debug, debug|release) {
  LIBS += -lcoldet_debug
}
else {
  LIBS += -lcoldet_release
}

INCLUDEPATH *= $$COLDET_ROOT/src
LIBS *= -L$$COLDET_ROOT/bin
CONFIG(debug, debug|release) {
  LIBS += -lcoldet.debug
}
else {
  LIBS += -lcoldet.release
}

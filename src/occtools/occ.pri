# Return the input path re-written using the system-dependent separator
defineReplace(sysPath) {
  win*:result = $$replace(1, /, \\)
  else:result = $$1
  return($$result)
}

INCLUDEPATH += $$CASCADE_ROOT/inc

linux-*:DEFINES *= HAVE_CONFIG_H \
                   HAVE_FSTREAM \
                   HAVE_IOSTREAM \
                   HAVE_IOMANIP \
                   HAVE_LIMITS_H

win32-*:DEFINES *= WNT
linux-*:DEFINES *= LIN LININTEL OCC_CONVERT_SIGNALS

MSVC_VERSION = xx
win32-msvc2005:MSVC_VERSION = 8
win32-msvc2008:MSVC_VERSION = 9
win32-msvc2010:MSVC_VERSION = 10
win32-msvc2012:MSVC_VERSION = 11
win32-msvc2013:MSVC_VERSION = 12

equals(QT_ARCH, i386) {
  CASCADE_SUB_LIB_PATH = win32/vc$$MSVC_VERSION/lib
} else:equals(QT_ARCH, x86_64) {
  CASCADE_SUB_LIB_PATH = win64/vc$$MSVC_VERSION/lib
  DEFINES += _OCC64
}
else {
  error(Platform architecture not supported (QT_ARCH = $$QT_ARCH))
}

CASCADE_LIB_PATH += $$CASCADE_ROOT/$$CASCADE_SUB_LIB_PATH
LIBS += $$sysPath($$join(CASCADE_LIB_PATH, " -L", -L))
QMAKE_RPATHDIR += $$CASCADE_LIB_PATH

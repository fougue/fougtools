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
*-64:DEFINES *= _OCC64

CASCADE_LIB_PATH += $$CASCADE_ROOT/lib
LIBS += $$sysPath($$join(CASCADE_LIB_PATH, " -L", -L))
QMAKE_RPATHDIR += $$CASCADE_LIB_PATH

# There is a weird bug with qmake on windows : it fails to correctly link with TKSTEP209 due to the
# name of library mixing characters and digits.
#   Or maybe nmake is the problem ?
#   Note : you have to rename TKSTEP209 to TKSTEP_tzn in $$CASCADE_ROOT/win32/lib
win32-msvc* {
  OCC_TKSTEP = TKSTEP_tzn
}
else {
  OCC_TKSTEP = TKSTEP209
}

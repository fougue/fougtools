INCLUDEPATH += $$PWD/../include
LIBS += -L$$PWD/../lib
QMAKE_RPATHDIR += $$PWD/../lib

FOUGTOOLS_LIBLIST = qttools_core qttools_gui qttools_qml qttools_network qttools_script qttools_sql occtools
for(fouglib, FOUGTOOLS) {
  !contains(FOUGTOOLS_LIBLIST, $${fouglib}): error(Invalid FougTools module name : $${fouglib})
  DEFINES += $$upper($${fouglib})_DLL
  LIBS += -l$${fouglib}$$TARGET_SUFFIX
}
contains(FOUGTOOLS, qttools_core): QT += core

contains(FOUGTOOLS, qttools_gui) {
  QT += gui
  isEqual(QT_MAJOR_VERSION, 5): QT += widgets
}

contains(FOUGTOOLS, qttools_qml) {
  QT += gui
  isEqual(QT_MAJOR_VERSION, 4): QT += declarative
  isEqual(QT_MAJOR_VERSION, 5): QT += qml
}

contains(FOUGTOOLS, qttools_network): QT += network
contains(FOUGTOOLS, qttools_script):  QT += script
contains(FOUGTOOLS, qttools_sql):     QT += sql

contains(FOUGTOOLS, occtools) {
  include(occ.pri)
  LIBS += -lTKBRep -lTKernel -lTKG2d -lTKG3d -lTKGeomAlgo -lTKGeomBase \
          -lTKIGES -lTKMath -lTKMesh -lTKOpenGl -lTKPrim -lTKService -lTKShHealing \
          -lTKSTEP -lTKSTEPAttr -lTKSTEPBase -l$$OCC_TKSTEP -lTKSTL -lTKTopAlgo \
          -lTKV3d -lTKXSBase
}

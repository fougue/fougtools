include(../lib_config.pri)

TARGET = occtools$$TARGET_SUFFIX

QT += gui
isEqual(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG(dll):DEFINES += OCCTOOLS_DLL OCCTOOLS_MAKE_DLL

include(../../src/occtools/occtools.pri)

QMAKE_RPATHDIR += $$CASCADE_LIB_PATH

occtools_occpri.path  = $$PREFIX_DIR/qmake
occtools_occpri.files = ../../src/occtools/occ.pri
occtools_include.path  = $$OCCTOOLS_INC_PATH/occtools
occtools_include.files = ../../src/occtools/*.h
target.path = $$OCCTOOLS_LIB_PATH
INSTALLS += occtools_occpri \
            occtools_include \
            target

include(../config.pri)
CONFIG += dll
include(../../src/occtools/build_occtools.pri)

QMAKE_RPATHDIR += $$CASCADE_LIB_PATH

occtools_occpri.path  = $$PREFIX_DIR/qmake
occtools_occpri.files = ../../src/occtools/occ.pri
occtools_include.path   = $$OCCTOOLS_INC_PATH/occtools
occtools_include.files  = ../../src/occtools/*.h
target.path = $$OCCTOOLS_LIB_PATH
INSTALLS += occtools_occpri \
            occtools_include \
            target

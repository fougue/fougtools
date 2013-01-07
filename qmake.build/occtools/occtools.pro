include(../config.pri)
CONFIG *= dll
include(../../src/occtools/build_occtools.pri)

QMAKE_RPATHDIR += $$CASCADE_LIB_PATH

occtools_occpri.path  = $$PREFIX_DIR/3rdparty
occtools_occpri.files = ../../3rdparty/occ.pri
occtools_include.path   = $$OCCTOOLS_INC_PATH/occtools
occtools_include.files  = ../../src/occtools/*.h
occtools_ui_include.path   = $$OCCTOOLS_INC_PATH/occtools/ui
occtools_ui_include.files  = ../../src/occtools/ui/*.h
INSTALLS += occtools_occpri \
            occtools_include \
            occtools_ui_include

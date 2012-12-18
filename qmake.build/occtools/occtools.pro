include(../config.pri)
CONFIG *= dll
include(../../src/occtools/build_occtools.pri)

occtools_include.path   = $$OCCTOOLS_INC_PATH/occtools
occtools_include.files  = ../../src/occtools/*.h
occtools_ui_include.path   = $$OCCTOOLS_INC_PATH/occtools/ui
occtools_ui_include.files  = ../../src/occtools/ui/*.h
INSTALLS += occtools_include occtools_ui_include

include(../config.pri)
CONFIG *= dll
include(../../src/qttools/qml/build_qttools_qml.pri)

qttools_qml_include.path  = $$QTTOOLS_INC_PATH/qttools/qml
qttools_qml_include.files = ../../src/qttools/qml/*.h
INSTALLS += qttools_qml_include

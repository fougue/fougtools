include(../config.pri)
CONFIG += dll
include(../../src/qttools/Task/build_qttools_task.pri)

qttools_task_include.path  = $$QTTOOLS_INC_PATH/qttools/Task
qttools_task_include.files = ../../src/qttools/Task/*.h
target.path = $$QTTOOLS_LIB_PATH
INSTALLS += qttools_task_include target

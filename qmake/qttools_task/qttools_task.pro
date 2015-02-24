include(../lib_config.pri)

TARGET = qttools_task$$TARGET_SUFFIX

QT = core
CONFIG(dll):DEFINES += QTTOOLS_TASK_DLL QTTOOLS_TASK_MAKE_DLL

include(../../src/qttools/Task/qttools_task.pri)

qttools_task_include.path  = $$QTTOOLS_INC_PATH/qttools/Task
qttools_task_include.files = ../../src/qttools/Task/*.h
target.path = $$QTTOOLS_LIB_PATH
INSTALLS += qttools_task_include target

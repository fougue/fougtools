include(../lib_config.pri)

TARGET = qttools_sql$$TARGET_SUFFIX

QT -= gui

CONFIG(dll):DEFINES += QTTOOLS_SQL_DLL QTTOOLS_SQL_MAKE_DLL

include(../../src/qttools/sql/qttools_sql.pri)

qttools_sql_include.path  = $$QTTOOLS_INC_PATH/qttools/sql
qttools_sql_include.files = ../../src/qttools/sql/*.h
target.path = $$QTTOOLS_LIB_PATH
INSTALLS += qttools_sql_include target

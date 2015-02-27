QT += sql

HEADERS += \
    $$PWD/database_settings.h \
    $$PWD/database_manager.h \
    $$PWD/sql.h \
    $$PWD/composite_type_helper.h \
    $$PWD/qsql_query_utils.h

SOURCES += \
    $$PWD/database_settings.cpp \
    $$PWD/database_manager.cpp \
    $$PWD/composite_type_helper.cpp \
    $$PWD/qsql_query_utils.cpp

include(../shared_config.pri)

TARGET = cpptools$$TARGET_SUFFIX

HEADERS += \
    abstract_functor.h \
    bool_utils.h \
    c_array_utils.h \
    circular_iterator.h \
    null.h \
    scoped_value.h \
    identifier.h \
    memory_utils.h \
    functional.h

SOURCES += \
    doxygen.cpp


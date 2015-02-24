INCLUDEPATH *= $$PWD/.. $$PWD/../..

HEADERS += \
    $$PWD/QThreadPoolRunner.h \
    $$PWD/QThreadRunner.h \
    $$PWD/CurrentThreadRunner.h \
    $$PWD/BaseRunner.h \
    $$PWD/Manager.h \
    $$PWD/Progress.h \
    $$PWD/Runnable.h \
    $$PWD/RunnableSignals.h \
    $$PWD/StdAsyncRunner.h

SOURCES += \
    $$PWD/QThreadPoolRunner.cpp \
    $$PWD/QThreadRunner.cpp \
    $$PWD/CurrentThreadRunner.cpp \
    $$PWD/BaseRunner.cpp \
    $$PWD/Manager.cpp \
    $$PWD/Progress.cpp \
    $$PWD/Runnable.cpp \
    $$PWD/RunnableSignals.cpp \
    $$PWD/StdAsyncRunner.cpp

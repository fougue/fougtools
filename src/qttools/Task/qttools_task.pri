INCLUDEPATH *= $$PWD/.. $$PWD/../..

HEADERS += \
    $$PWD/BaseRunner.h \
    $$PWD/BaseRunnerSignals.h \
    $$PWD/Manager.h \
    $$PWD/Progress.h \
    $$PWD/RunnerCurrentThread.h \
    $$PWD/RunnerQThreadPool.h \
    $$PWD/RunnerQThread.h \
    $$PWD/RunnerStdAsync.h

SOURCES += \
    $$PWD/BaseRunner.cpp \
    $$PWD/BaseRunnerSignals.cpp \
    $$PWD/Manager.cpp \
    $$PWD/Progress.cpp

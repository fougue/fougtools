INCLUDEPATH *= $$PWD/.. $$PWD/../..

QT += network

HEADERS += \
    $$PWD/mail_send.h \
    $$PWD/message.h \
    $$PWD/network.h \
    $$PWD/smtp_account.h

SOURCES += \
    $$PWD/mail_send.cpp \
    $$PWD/message.cpp \
    $$PWD/smtp_account.cpp

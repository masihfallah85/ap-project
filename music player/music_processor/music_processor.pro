QT       += core gui widgets multimedia
QT += multimedia
CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    musicprocessor.cpp

HEADERS += \
    mainwindow.h \
    musicprocessor.h

FORMS += \
    mainwindow.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

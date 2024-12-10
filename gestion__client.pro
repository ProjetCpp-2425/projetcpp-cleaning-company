QT       += core gui
QT       += core gui sql
QT       += core gui widgets printsupport
QT       += sql
QT     +=core gui widgets charts
QT   +=network
QT   +=core
QT += quickwidgets
QT += quick positioning
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Arduino.cpp \
    Client.cpp \
    Connection.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Arduino.h \
    Client.h \
    Connection.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    maps.qrc

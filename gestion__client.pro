QT       += core gui
QT       += core gui sql
QT       += core gui widgets printsupport serialport
QT       += sql
QT     +=core gui widgets charts
QT   +=network
QT   +=core
QT += quickwidgets
QT += quick positioning

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
    MaterielAvance.cpp \
    calendrier.cpp \
    employe.cpp \
    fournisseur.cpp \
    graphiquewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    materiel.cpp \
    meteoservices.cpp \
    services.cpp \
    sms.cpp \
    statistique.cpp \
    transaction.cpp

HEADERS += \
    Arduino.h \
    Client.h \
    Connection.h \
    MaterielAvance.h \
    calendrier.h \
    employe.h \
    fournisseur.h \
    graphiquewidget.h \
    mainwindow.h \
    materiel.h \
    meteoservices.h \
    services.h \
    sms.h \
    statistique.h \
    transaction.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    maps.qrc

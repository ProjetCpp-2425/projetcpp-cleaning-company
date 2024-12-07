QT += core gui sql serialport printsupport charts widgets
QT += core gui network
# Fichiers source
SOURCES += \
    connection.cpp \
    graphiquewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    meteoservices.cpp \
    services.cpp

# Fichiers d'en-tête
HEADERS += \
    connection.h \
    graphiquewidget.h \
    mainwindow.h \
    meteoservices.h \
    services.h

# Fichiers de formulaire (UI)
FORMS += \
    mainwindow.ui

# Fichiers supplémentaires
DISTFILES += \
    homewindow.pro.user

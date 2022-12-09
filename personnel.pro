QT       += core gui sql network multimedia multimediawidgets printsupport widgets axcontainer
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Excel.cpp \
    affaire.cpp \
    arduino.cpp \
    connexion.cpp \
    gestion_affaire.cpp \
    gestion_rdv.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    personnel.cpp \
    qcustomplot.cpp \
    rdv.cpp \
    smtp.cpp

HEADERS += \
    Excel.h \
    affaire.h \
    arduino.h \
    connexion.h \
    gestion_affaire.h \
    gestion_rdv.h \
    mainwindow.h \
    menu.h \
    personnel.h \
    qcustomplot.h \
    rdv.h \
    smtp.h

FORMS += \
    gestion_affaire.ui \
    gestion_rdv.ui \
    mainwindow.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basketballteam.cpp \
    gamesimulator.cpp \
    main.cpp \
    mainwindow.cpp \
    match.cpp \
    matchlogdialog.cpp \
    player.cpp \
    playerfactory.cpp \
    standings.cpp \
    standingsobserver.cpp

HEADERS += \
    basketballteam.h \
    gamesimulator.h \
    mainwindow.h \
    match.h \
    matchlogdialog.h \
    observer.h \
    player.h \
    playerfactory.h \
    standings.h \
    standingsobserver.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

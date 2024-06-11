QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bodypart.cpp \
    bullet.cpp \
    centipede.cpp \
    game.cpp \
    main.cpp \
    mushroom.cpp \
    player.cpp \
    spider.cpp \
    widget.cpp

HEADERS += \
    bodypart.h \
    bullet.h \
    centipede.h \
    game.h \
    mushroom.h \
    player.h \
    spider.h \
    typeDef.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#-------------------------------------------------
#
# Project created by QtCreator 2015-10-24T08:33:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project1
TEMPLATE = app


SOURCES += main.cpp\
    guessentry.cpp \
    playspace.cpp \
    logindialog.cpp \
    codedialog.cpp \
    guessscene.cpp \
    codescene.cpp \
    user.cpp \
    newuserdialog.cpp \
    game.cpp \
    mainwindow.cpp \
    computer.cpp \
    newgamedialog.cpp \
    player.cpp

HEADERS  += \
    guessentry.h \
    playspace.h \
    empty.h \
    invalidargument.h \
    list.h \
    logindialog.h \
    codedialog.h \
    guessscene.h \
    codescene.h \
    game.h \
    user.h \
    newuserdialog.h \
    guess.h \
    mainwindow.h \
    computer.h \
    newgamedialog.h \
    connection.h \
    queue.h \
    stack.h \
    tree.h \
    player.h

FORMS    += \
    newuserdialog.ui

RESOURCES += \
    codebreaker.qrc

DISTFILES +=



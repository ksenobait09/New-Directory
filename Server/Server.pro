QT -= gui
QT += network
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    serverthread.cpp \
    server.cpp \
<<<<<<< HEAD
    networking.cpp \
    database.cpp \
    user.cpp \
    simplecrypt.cpp
=======
<<<<<<< HEAD
    database.cpp \
    user.cpp \
    simplecrypt.cpp
=======
    networking.cpp \
    database.cpp
>>>>>>> b093a0be471820a735f7c71b50e5befa060751c8

>>>>>>> e2aac4930cb7c606401d958da4710331d327c445

HEADERS += \
    server.h \
    serverthread.h \
<<<<<<< HEAD
    networking.h \
    database.h \
    user.h \
    simplecrypt.h
=======
<<<<<<< HEAD
    database.h \
    user.h \
    simplecrypt.h
=======
    networking.h \
    database.h \
>>>>>>> b093a0be471820a735f7c71b50e5befa060751c8
>>>>>>> e2aac4930cb7c606401d958da4710331d327c445

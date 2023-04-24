#-------------------------------------------------
#
# Project created by QtCreator 2023-04-20T09:28:32
#
#-------------------------------------------------

QT       -= gui

TARGET = QtDeikstraAlgorythm
TEMPLATE = lib

DEFINES += QTDEIKSTRAALGORYTHM_LIBRARY

SOURCES += qtdeikstraalgorythm.cpp

HEADERS += qtdeikstraalgorythm.h\
        qtdeikstraalgorythm_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

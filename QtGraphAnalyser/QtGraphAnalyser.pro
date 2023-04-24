#-------------------------------------------------
#
# Project created by QtCreator 2023-04-04T11:01:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGraphAnalyser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphreader.cpp \
    graphpathfinder.cpp \
    graphwriter.cpp \
    help.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    graphreader.h \
    graphpathfinder.h \
    sharedstructs.h \
    graphwriter.h \
    help.h \
    about.h \
    openordelete.h

FORMS    += mainwindow.ui \
    help.ui \
    about.ui


win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/QtDeikstraAlgorythmBuild/debug/ -lQtDeikstraAlgorythm
else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/QtDeikstraAlgorythmBuild/release/ -lQtDeikstraAlgorythm
else:unix: LIBS += -L$$PWD/QtDeikstraAlgorythmBuild/ -lQtDeikstraAlgorythm

INCLUDEPATH += $$PWD/QtDeikstraAlgorythm
DEPENDPATH += $$PWD/QtDeikstraAlgorythm

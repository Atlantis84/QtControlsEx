#-------------------------------------------------
#
# Project created by QtCreator 2021-09-30T14:45:39
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = QtControlsEx
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QMAKE_CXXFLAGS_RELEASE = -Od -ZI -MD
QMAKE_LFLAGS_RELEASE = /DEBUG /INCREMENTAL:NO

SOURCES += \
        bassdywgt.cpp \
        bassstwgt.cpp \
        basswgt.cpp \
        centralmainwindow.cpp \
        centralwgt.cpp \
        dialplatewgt.cpp \
        dynamiclabel.cpp \
        gradientcolumnwgt.cpp \
        leftwidget.cpp \
        main.cpp \
        mainwindow.cpp \
        mousetracer.cpp \
        pathtohit.cpp \
        qcustomplot.cpp \
        qcustomplotex.cpp \
        testdrawwgt.cpp \
        title/TitleBar.cpp \
        title/titlewidget.cpp \
        welcomewidget.cpp

HEADERS += \
        bass.h \
        bassdywgt.h \
        bassstwgt.h \
        basswgt.h \
        centralmainwindow.h \
        centralwgt.h \
        dialplatewgt.h \
        dynamiclabel.h \
        gradientcolumnwgt.h \
        leftwidget.h \
        mainwindow.h \
        mousetracer.h \
        pathtohit.h \
        qcustomplot.h \
        qcustomplotex.h \
        testdrawwgt.h \
        title/TitleBar.h \
        title/titlewidget.h \
        welcomewidget.h

INCLUDEPATH += .\title

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    proj.qrc

LIBS += -L$$PWD/bin/release -lbass

#INCLUDEPATH += $$PWD/bin/release
DEPENDPATH += $$PWD/bin/release

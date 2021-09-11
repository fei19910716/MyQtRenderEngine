#-------------------------------------------------
#
# Project created by QtCreator 2021-08-22T17:42:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CFRenderEngine
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

SOURCES += \
        src/Components/component.cpp \
        src/Components/componentwidget.cpp \
        src/Entities/entity.cpp \
        src/Render/Render.cpp \
        src/Render/RenderEngine.cpp \
        src/Render/renderthread.cpp \
        src/Render/texturebuffer.cpp \
        src/Systems/Render/DrawTriangleSystem.cpp \
        main.cpp \
        src/mainwindow.cpp \
        src/renderview.cpp

HEADERS += \
        src/Components/component.h \
        src/Components/Appearance/Triangle.h \
        src/Components/componentwidget.h \
        src/Entities/entity.h \
        src/Render/Render.h \
        src/Render/RenderEngine.h \
        src/Render/renderthread.h \
        src/Render/texturebuffer.h \
        src/Systems/Render/Appearance.h \
        src/Systems/Render/DrawTriangleSystem.h \
        src/mainwindow.h \
        src/renderview.h

FORMS += \
        src/UI/mainwindow.ui

INCLUDEPATH += src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

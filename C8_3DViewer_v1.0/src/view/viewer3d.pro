macx {  #win32, macx, unix
    QT       += core gui openglwidgets
    LIBS     += -framework GLUT -framework OpenGL -framework Cocoa
} else {
    QT       += core gui opengl openglwidgets
    LIBS     += -lOpenGL -lGLU -lglut
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(3rdparty/qtgifimage/src/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../core/parser.c \
    ../core/transformations.c \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../core/parser.h \
    ../core/s21_3dviewer.h \
    ../core/transformations.h \
    glwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#-------------------------------------------------
# Cours de Réalité Virtuelle
# leo.donati@univ-cotedazur.fr
#
# EPU 2020-21
#
# Tutoriel n°1
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rvwidget.cpp

HEADERS += \
    mainwindow.h \
    rvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Ici les fichiers complémentaires qui contiennent les shaders
DISTFILES += \
    FS_simple.fsh \
    VS_simple.vsh

# Fichier contenant les ressources
RESOURCES += \
    RVResources.qrc

# Instruction de compilation complémentaire pour Windows
windows:LIBS += -lopengl32

FORMS += \
    mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T17:20:59
#
#-------------------------------------------------

QT      += core\
        gui\
        widgets\
        xmlpatterns


TARGET = SchedConfigTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlmanager.cpp \
    aboutwindow.cpp

HEADERS  += \
    types.hpp \
    xmlmanager.hpp \
    mainwindow.h \
    aboutwindow.h

FORMS    += mainwindow.ui \
    aboutwindow.ui

OTHER_FILES += \
    xsd/schema.xsd

RESOURCES += \
    resources.qrc

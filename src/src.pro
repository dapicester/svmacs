TEMPLATE = app
TARGET = svmacs
DESTDIR = ../bin
DEPENDPATH += . gui jack
INCLUDEPATH += . gui jack

# Input
HEADERS += cli/svmacscli.h gui/svmacsgui.h jack/jackclient.h
FORMS += gui/svmacsgui.ui
SOURCES += main.cpp gui/svmacsgui.cpp jack/jackclient.cpp
RESOURCES += application.qrc

# Libraries
LIBS += -lrlog
LIBS += -ljack 
LIBS += -L../lib -ljackcpp

contains(CONFIG,debug) {
    message("Enabling logging")
    DEFINES += DEBUG_LEVEL
}

TEMPLATE = app
TARGET = svmacs
DESTDIR = ../bin
DEPENDPATH += . gui jack
INCLUDEPATH += . gui jack

# Input
HEADERS += cli/svmaccli.h gui/svmacgui.h jack/jackclient.h
FORMS += gui/svmacgui.ui
SOURCES += main.cpp cli/svmaccli.cpp gui/svmacgui.cpp jack/jackclient.cpp 
RESOURCES += application.qrc

# Libraries
LIBS += -lrlog
LIBS += -ljack 
LIBS += -L../lib -ljackcpp

# Debug
contains (CONFIG, debug) {
    DEFINES += ENABLE_DEBUG
}

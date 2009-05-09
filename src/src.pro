TEMPLATE = app
TARGET = svmacs
DESTDIR = ../bin
DEPENDPATH += . gui jack
INCLUDEPATH += . gui jack

# Input
HEADERS += jack/jackclient.h cli/svmaccli.h gui/svmacgui.h 
FORMS += gui/svmacgui.ui
SOURCES += jack/jackclient.cpp cli/svmaccli.cpp gui/svmacgui.cpp main.cpp
RESOURCES += application.qrc

# Libraries
LIBS += -lrlog
LIBS += -ljack 
LIBS += -L../lib -ljackcpp

# Debug
contains(CONFIG, debug){
    DEFINES += ENABLE_DEBUG
}

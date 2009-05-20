TEMPLATE = app
TARGET = svmacs
DESTDIR = ../bin
DEPENDPATH += . gui jack
INCLUDEPATH += . gui jack

# Input
HEADERS += jack/jackclient.h \
           jack/ringbufferread.h \
           cli/svmaccli.h \
           gui/svmacgui.h \
 processor.h
SOURCES += jack/jackclient.cpp \
           jack/ringbufferread.cpp \
           cli/svmaccli.cpp \
           gui/svmacgui.cpp \
           main.cpp 
FORMS += gui/svmacgui.ui
RESOURCES += application.qrc

# Libraries
LIBS += `pkg-config --cflags --libs jack`
LIBS += -lrlog 
LIBS += -L../lib -ljackcpp

# Debug
contains(CONFIG, debug){
    DEFINES += ENABLE_DEBUG
}

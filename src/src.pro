TEMPLATE = app
LANGUAGE = C++
TARGET = svmacs
DESTDIR = ../bin
DEPENDPATH += . gui jack
INCLUDEPATH += . gui jack
CONFIG += debug

# Input
HEADERS += jack/jackclient.h \
 jack/ringbufferread.h \
 cli/svmaccli.h \
 gui/svmacgui.h \
 features/processor.h \
 features/feature.h \
 features/zcr.h \
 features/energy.h
SOURCES += jack/jackclient.cpp \
 jack/ringbufferread.cpp \
 cli/svmaccli.cpp \
 gui/svmacgui.cpp \
 main.cpp \
 features/processor.cpp \
 features/zcr.cpp \
 features/energy.cpp
FORMS += gui/svmacgui.ui
RESOURCES += application.qrc

# Libraries
CONFIG += link_pkgconfig
PKGCONFIG += jack
#LIBS += -ljack -lpthread -lrt
LIBS += `itpp-config --debug --cflags --static --libs`
LIBS += -lrlog 
LIBS += -L../lib -ljackcpp

# Debug
contains(CONFIG, debug){
    DEFINES += ENABLE_DEBUG
}

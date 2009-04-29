HEADERS += svmacsgui.h \
           jackclient.h
SOURCES += svmacsgui.cpp \
           main.cpp \
           jackclient.cpp
FORMS += svmacsgui.ui

TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = svmacs
DESTDIR = ../bin
RESOURCES = application.qrc

unix:LIBS += -ljack -L../lib -ljackcpp
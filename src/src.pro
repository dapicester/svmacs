SOURCES += svmacs.cpp \
           main.cpp
HEADERS += svmacs.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = svmacs
DESTDIR = ../bin
RESOURCES = application.qrc

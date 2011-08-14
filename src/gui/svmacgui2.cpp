/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "svmacgui.h"
#include <QtGui>

#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>

void SvmacGui::about() {
      QMessageBox::about(this, tr("About"),
            "<center>"  
            "<p><b>SVM Audio Classification</b></p>"
            "<p>version: XX.XX.XX\n\n</p>"
            "<p>Copyright 2009-2011 Paolo D'Apice</p>"
            "<p>dapicester@gmail.com</p>"
            "</center>");
}

void SvmacGui::enable(QWidget* widget) {
    widget->setEnabled(true);    
}

void SvmacGui::disable(QWidget* widget) {
    widget->setEnabled(false);
}

void SvmacGui::setTextRed(QLabel* label) {
    rDebug("text in RED");    
    label->setStyleSheet("QLabel { color : red; }"); // TODO: bold echo text
}

void SvmacGui::setTextDefault(QLabel* label) {
    rDebug("text in BLACK");
    label->setStyleSheet("QLabel { color : black; }");
}

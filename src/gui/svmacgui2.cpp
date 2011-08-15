/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "svmacgui.h"
#include <QtGui>

#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>

const QString SvmacGui::eventStylesheet = "QLabel[event=\"true\"] {"
        "border: 1px solid black;"
        "border-radius: 10px;"
        "border-color: black;"
        "padding: 6px;"
        "min-width: 5em;"
    "}";


void SvmacGui::adapterSlot(const Event& event) {
    Q_EMIT adapterSignal(event);
}

void SvmacGui::showAbout() {
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
    label->setStyleSheet("background-color: red"); 
}

void SvmacGui::setTextDefault(QLabel* label) {
    label->setStyleSheet("background-color: ");
}

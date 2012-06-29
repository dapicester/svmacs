/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "version.h"
#include "svmacgui.h"
using namespace svmacs;

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

void
SvmacGui::adapterSlot(const Event& event) {
    Q_EMIT adapterSignal(event);
}

void
SvmacGui::showAbout() {
    static const QString message = QString(
            "<center>"
            "<p><b>SVM Audio Classification</b></p>"
            "<p>version: %1.%2.%3\n\n</p>"
            "<p>Copyright 2009-2011 Paolo D'Apice</p>"
            "<p>paolo.dapice@gmail.com</p>"
            "</center>").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);
    QMessageBox::about(this, tr("About"), message);
}

void
SvmacGui::enable(QWidget* widget) {
    widget->setEnabled(true);
}

void
SvmacGui::disable(QWidget* widget) {
    widget->setEnabled(false);
}

void
SvmacGui::setTextRed(QLabel* label) {
    label->setStyleSheet("background-color: red");
}

void
SvmacGui::setTextDefault(QLabel* label) {
    label->setStyleSheet("background-color: ");
}

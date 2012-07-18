/*
 * Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

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

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

// TODO: refactoring
QPalette SvmacGui::getPalette(Color color) {
    rDebug("getting palette ");
    if (color == BLACK) {
        QPalette palette(QColor(255,255,255));
        palette.setColor( QPalette::Foreground, QColor(0,0,0) );
        return palette;
    } else { 
        QPalette palette(QColor(255,255,255));
        palette.setColor( QPalette::Foreground, QColor(255,0,0) );
        return palette;
    }
}

QPalette SvmacGui::red = getPalette(RED);

QPalette SvmacGui::black = getPalette(BLACK);

void SvmacGui::redLabel(QLabel* label) {
    rDebug("text in RED");    
    /*
    QPalette palette(QColor(255,255,255));
    palette.setColor( QPalette::Foreground, QColor(255,0,0) );
    label->setPalette(palette);
    */
    label->setPalette(red);
}

void SvmacGui::blackLabel(QLabel* label) {
    rDebug("text in BLACK");
    /*
    QPalette palette(QColor(255,255,255));
    palette.setColor( QPalette::Foreground, QColor(0,0,0) );
    label->setPalette(palette);
    */
    label->setPalette(black);
}

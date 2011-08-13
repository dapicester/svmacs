/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "svmacgui.h"

#define RLOG_COMPONENT "guiutils"
#include <rlog/rlog.h>

#include <QtGui>

void SvmacGui::about() {
      QMessageBox::about(this, "About",
            "<center>"  
            "<p><b>SVM Audio Classification</b></p>"
            "<p>version: XX.XX.XX\n\n</p>"
            "<p>Copyright 2009-2011 Paolo D'Apice</p>"
            "<p>dapicester@gmail.com</p>"
            "</center>");
}

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

void SvmacGui::enableButton(QAbstractButton* button) {
    button->setEnabled(true);    
}

void SvmacGui::disableButton(QAbstractButton* button) {
    button->setEnabled(false);
}

void SvmacGui::enableSpinBox(QAbstractSpinBox* spinbox) {
    spinbox->setEnabled(true);    
}

void SvmacGui::disableSpinBox(QAbstractSpinBox* spinbox) {
    spinbox->setEnabled(false);    
}

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

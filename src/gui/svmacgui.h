/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVMACS_GUI_H
#define SVMACS_GUI_H

#include "ui_svmacgui.h"
#include "../jack/jackclient.h"
using jack::JackClient;

/** 
@class SvmacGui
@brief GUI interface for the SVM Audio Classifier. 
@author Paolo D'Apice
*/
class SvmacGui : public QWidget, private Ui::SvmacQt {
    Q_OBJECT
    /** Pointer to the Jack client */
    JackClient* client;

protected:
    /// Enable the specified button
    void enableButton(QAbstractButton* button);
    /// Disable the specified button
    void disableButton(QAbstractButton* button);
    /// Enable the spin box
    void enableSpinBox(QAbstractSpinBox* spinbox);
    /// Disable the spin box
    void disableSpinBox(QAbstractSpinBox* spinbox);

public:
    /** Constructor. */
    SvmacGui(QWidget *parent = 0);

public slots:
    /// Start the Jack client
    void startJackClient();
    /// Stop the Jack client
    void stopJackClient();
    /// Quit the application
    void quitApp();    
    /// Show the about dialog
    void about();

};

#endif //SVMACS_GUI_H

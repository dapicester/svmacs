/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVMACS_GUI_H
#define SVMACS_GUI_H

#include "ui_svmacgui.h"
#include "../jack/jackclient.h"
using jack::JackClient;

#include "../model/classifier.h"
using model::EventType;

/** 
@class SvmacGui
@brief GUI interface for the SVM Audio Classifier. 
@author Paolo D'Apice
*/
class SvmacGui : public QWidget, private Ui::SvmacQt {
    Q_OBJECT
    /** Pointer to the Jack client */
    JackClient* client;

    static bool flag;
protected:
    /// Enable the specified button
    void enableButton(QAbstractButton* button);
    /// Disable the specified button
    void disableButton(QAbstractButton* button);
    /// Enable the spin box
    void enableSpinBox(QAbstractSpinBox* spinbox);
    /// Disable the spin box
    void disableSpinBox(QAbstractSpinBox* spinbox);
    /// Highlight a label using red color
    void redLabel(QLabel* label);
    /// Apply standard palette to the label
    void stdLabel(QLabel* label);

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
    
    /// Highlight the event label
    void highlightEvent(EventType type);

    void test();

};

#endif //SVMACS_GUI_H

/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVMACS_GUI_H
#define SVMACS_GUI_H

#include "ui_svmacgui.h"
#include "../jack/jackclient.h"
using jack::JackClient;

#include "../model/event.h"
using model::Event;


/** 
@class SvmacGui
@brief GUI interface for the SVM Audio Classifier. 
@author Paolo D'Apice
*/
class SvmacGui : public QWidget, private Ui::SvmacQt {
    Q_OBJECT
    /** Pointer to the Jack client */
    JackClient* client;
    /// Enumeration for palette color
    enum Color { BLACK, RED };
    /// Build a palette with the given color
    static QPalette getPalette(Color color);
    /// The palette with red text foreground
    static QPalette red;
    /// The palette with black text foreground
    static QPalette black;
    
protected: //TODO private
    /// Enable the specified button
    void enableButton(QAbstractButton* button);
    /// Disable the specified button
    void disableButton(QAbstractButton* button);
    /// Enable the spin box
    void enableSpinBox(QAbstractSpinBox* spinbox);
    /// Disable the spin box
    void disableSpinBox(QAbstractSpinBox* spinbox);
    /// Set text foreground to red
    void redLabel(QLabel* label);
    /// Set text foreground to black
    void blackLabel(QLabel* label);

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
    void highlightEvent(const Event& event);

#ifdef ENABLE_DEBUG
    void test();
private:    
    static bool flag;
#endif

};

#endif //SVMACS_GUI_H

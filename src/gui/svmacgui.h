/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apic                               *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_GUI_H
#define SVMACS_GUI_H

#include <QObject>
#include "ui_svmacgui.h"
#include "model/event.h"

class Engine;

/** 
@class SvmacGui
@brief GUI interface for the SVM Audio Classifier. 
@author Paolo D'Apice
*/
class SvmacGui : public QWidget, private Ui::SvmacQt {
    Q_OBJECT

public:
    /**
     * Constructor
     * @param length
     *          frame length (in seconds)
     * @param overlap
     *          frame overlapping ratio (percentage)
     * @param parent
     */
    SvmacGui(float length, float overlap, QWidget *parent = 0);

    /// Slot for highlighting the event label
    void highlightEvent(const Event& event);
   
public Q_SLOTS:
    /// Start the engine
    void start();
    /// Stop the engine
    void stop();
    
    /// Quit the application
    void quitApp();    
    /// Show the about dialog
    void about();
    
private:
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

private:
    /// pointer to the engine
    Engine* engine;
    
    /// Enumeration for palette color
    enum Color { BLACK, RED };
    
    /// Build a palette with the given color
    static QPalette getPalette(Color color);
    /// The palette with red text foreground
    static QPalette red;
    /// The palette with black text foreground
    static QPalette black;

#ifdef ENABLE_DEBUG
    void test();
private:    
    static bool flag;
#endif

};

#endif //SVMACS_GUI_H

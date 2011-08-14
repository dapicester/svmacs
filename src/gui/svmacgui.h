/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apic                               *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_GUI_H
#define SVMACS_GUI_H

#include "ui_svmacgui.h"
#include "model/event.h"
#include <QObject>

class Engine;

/** 
 * @class SvmacGui
 * @brief GUI interface for the SVM Audio Classifier. 
 * @author Paolo D'Apice
 */
class SvmacGui : public QWidget, private Ui::SvmacQt {
    Q_OBJECT

public:
    /**
     * Constructor.
     * @param length
     *          frame length (in seconds)
     * @param overlap
     *          frame overlapping ratio (percentage)
     * @param parent
     */
    SvmacGui(float length, float overlap, QWidget *parent = 0);

    /// Action performed on event detection
    void eventDetected(const Event& event);
   
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
    /// Enable the specified widget
    void enable(QWidget* widget);
    /// Disable the specified widget
    void disable(QWidget* widget);
    
    /// Set text foreground to red
    void setTextRed(QLabel* label);
    /// Set text foreground to black
    void setTextDefault(QLabel* label);

private:
    /// pointer to the engine
    Engine* engine;

};

#endif //SVMACS_GUI_H

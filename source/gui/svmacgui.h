/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apic                               *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_SVMACGUI_H
#define SVMACS_SVMACGUI_H

#include "config.h"
#include "ui_svmacgui.h"
#include "engine/engine.h"
#include "model/event.h"
//#include "gui/qdebugstream.h"

#include <QObject>
#include <QScopedPointer>

/**
 * GUI interface for the SVM Audio Classifier.
 */
class SvmacGui : public QWidget, private Ui::SvmacGui {
    Q_OBJECT

public:

    /**
     * Constructor.
     * @param length frame length (in seconds)
     * @param overlap frame overlapping ratio (percentage)
     * @param dmodel path to the detection model file
     * @param cmodel path to the classification model file
     * @param parent
     */
    SvmacGui(const float length, const float overlap,
            const std::string& dmodel, const std::string& cmodel,
            QWidget *parent = 0);

public Q_SLOTS:

    /// Start the engine.
    void startEngine();
    /// Stop the engine.
    void stopEngine();

    /// Quit the application.
    void quitApp();
    /// Show the about dialog.
    void showAbout();

    /// Action performed on event detection.
    void eventDetected(const svmacs::Event& event);

protected:

    /* TODO: graph
     *
     * Boost - Qt signals/slots adapter scheme:
     *
     * Engine::eventDetected(Event)      Boost signal
     *     |
     *     V
     * SvmacGui::adapterSlot(Event)      Boost slot
     *  emit adapterSignal(Event)        Qt signal
     *     |
     *     V
     * SvmacGui::eventDetected(Event)    Qt slot
     */

    /// Adapter Boost slot, converting Boost -> Qt signal.
    void adapterSlot(const svmacs::Event& event);

Q_SIGNALS:

    /// Adapter Qt signal for Boost signal Engine::eventDetected.
    void adapterSignal(const svmacs::Event& event);

private:

    /// Enable the specified widget.
    void enable(QWidget* widget);
    /// Disable the specified widget.
    void disable(QWidget* widget);

    /// Set text foreground to red.
    void setTextRed(QLabel* label);
    /// Set text foreground to black.
    void setTextDefault(QLabel* label);

private:

    const std::string dmodel;
    const std::string cmodel;

    QScopedPointer<svmacs::Engine> engine; ///< The actual running audio engine.

    //QDebugStream qout; ///< capture cout

    static const QString eventStylesheet;
};

#endif // SVMACS_SVMACGUI_H

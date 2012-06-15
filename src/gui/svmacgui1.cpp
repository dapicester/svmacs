/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "version.h"
#include "svmacgui.h"
#include "engine/engine.h"

using namespace svmacs;

#include <QtGui>
#include <boost/bind.hpp>

#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>

SvmacGui::SvmacGui(float length, float overlap, QWidget *parent) 
        /*: qout(std::cout, textEdit) */ {
    // initialise gui
    setupUi(this);
    
    this->setFixedSize(400, 450);
    this->setStyleSheet(eventStylesheet);
    
    gunshotLabel->setProperty("event", true);
    screamLabel->setProperty("event", true);
    glassLabel->setProperty("event", true);

    // connect start and stop buttons
    connect(startButton, SIGNAL(clicked()), this, SLOT(startEngine()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopEngine()));

    // connect about and quit buttons
    connect(aboutButton, SIGNAL(clicked()), this, SLOT(showAbout()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitApp()));

    // set initial values
    NspinBox->setValue(length);
    RspinBox->setValue(overlap);

    engine = 0;
    
    rInfo("GUI ready");
}

void SvmacGui::startEngine() {
    rInfo("starting ...");
    textEdit->append(tr("starting ..."));

    float length = NspinBox->value();
    rDebug("frame length N = %f seconds", length);

    float overlap = (float) RspinBox->value() / 100;
    rDebug("overlapping  R = %f percent", overlap);

    rInfo("initializing Engine ...");
    textEdit->append(tr("initializing Engine ..."));
    try {
        // defensive programming!!
        if (engine) {
            delete engine;
            engine = 0;
        }
        engine = new Engine(length, overlap);
        engine->start();
    } catch (JackException& e) {
        rError("%s", e.what());
        textEdit->append("failed:");
        textEdit->append(e.what()); // TODO parametrizzare

        QMessageBox::critical(this, tr("Error"),
                tr("Could not start the engine.\n"
                "Please check if the Jackd server is running.")); // TODO: show e.what()
        return;
    }

    disable(startButton);
    enable(stopButton);
    disable(NspinBox);
    disable(RspinBox);

    // connect event detection signal and slot
    engine->eventDetected.connect(boost::bind(&SvmacGui::adapterSlot, this, _1));
    qRegisterMetaType<Event>("Event");
    connect(this, SIGNAL(adapterSignal(const Event&)), this, SLOT(eventDetected(const Event&)) );
    
    rDebug("started");
    textEdit->insertPlainText(tr("started"));
}

void SvmacGui::stopEngine() {
    rDebug("stopping the Engine ...");
    textEdit->append(tr("stopping the Engine ..."));
    engine->eventDetected.disconnect(boost::bind(&SvmacGui::adapterSlot, this, _1));
    engine->stop();
    delete engine;
    engine = 0;

    disable(stopButton);
    enable(startButton);
    enable(NspinBox);
    enable(RspinBox);

    setTextDefault(gunshotLabel);
    setTextDefault(screamLabel);
    setTextDefault(glassLabel);

    rDebug("stopped");
    textEdit->insertPlainText(tr("done"));
}

void SvmacGui::quitApp() {
    rDebug("quitting");
    textEdit->append(tr("quitting"));

    if (engine) {
        stopEngine();
    }
    
    rInfo("quitting GUI");
    qApp->quit();
}

void SvmacGui::eventDetected(const Event& event) {
    EventType type = event.getType();
    switch (type) {
        // TODO: refactoring (si puo` fare di meglio...)
        case GUNSHOT:
            setTextRed(gunshotLabel);
            setTextDefault(screamLabel);
            setTextDefault(glassLabel);
            break;
        case SCREAM:
            setTextRed(screamLabel);
            setTextDefault(gunshotLabel);
            setTextDefault(glassLabel);
            break;
        case GLASS:
            setTextRed(glassLabel);
            setTextDefault(gunshotLabel);
            setTextDefault(screamLabel);
            break;
        case NONE:
            setTextDefault(gunshotLabel);
            setTextDefault(screamLabel);
            setTextDefault(glassLabel);
            break;
        default:
            break;
    }
    /* TODO
    if (type != NONE) {
        textEdit->append("detected event: "
                          event.getDescription());
    }
     */
}

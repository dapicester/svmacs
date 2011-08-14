/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "version.h"
#include "svmacgui.h"
#include "engine/engine.h"

#include <QtGui>
#include <boost/bind.hpp>

#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>


SvmacGui::SvmacGui(float length, float overlap, QWidget *parent) {
    // initialise gui
    setupUi(this);

    // connect start and stop buttons
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));

    // connect about and quit buttons
    connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitApp()));

    // set initial values
    NspinBox->setValue(length);
    RspinBox->setValue(overlap);

    engine = 0;
}

void SvmacGui::start() {
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
        rError(e.what());
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
    engine->eventDetected.connect(boost::bind(&SvmacGui::eventDetected, this, _1));

    rDebug("started");
    textEdit->insertPlainText(tr("started"));
}

void SvmacGui::stop() {
    rDebug("stopping the Engine ...");
    textEdit->append(tr("stopping the Engine ..."));
    engine->stop();
    delete engine;
    engine = 0;

    disable(stopButton);
    enable(startButton);
    enable(NspinBox);
    enable(RspinBox);

    blackLabel(gunshotLabel);
    blackLabel(screamLabel);
    blackLabel(glassLabel);

    rDebug("stopped");
    textEdit->insertPlainText(tr("done"));
}

void SvmacGui::quitApp() {
    rDebug("quitting");
    textEdit->append(tr("quitting"));

    if (engine) {
        stop();
    }
    
    qApp->quit();
}

void SvmacGui::eventDetected(const Event& event) {
    EventType type = event.getType();
    switch (type) {
        case NONE:
            blackLabel(gunshotLabel);
            blackLabel(screamLabel);
            blackLabel(glassLabel);
            break;
        case GUNSHOT:
            redLabel(gunshotLabel);
            blackLabel(screamLabel);
            blackLabel(glassLabel);
            break;
        case SCREAM:
            redLabel(screamLabel);
            blackLabel(gunshotLabel);
            blackLabel(glassLabel);
            break;
        case GLASS:
            redLabel(glassLabel);
            blackLabel(gunshotLabel);
            blackLabel(screamLabel);
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

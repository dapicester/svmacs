/*
 * Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "svmacgui.h"

using namespace svmacs;

#include <QtGui>
#include <boost/bind.hpp>

#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>

SvmacGui::SvmacGui(const float length, const float overlap,
        const std::string& dm, const std::string& cm,
        QWidget *parent) : dmodel(dm), cmodel(cm)
        /*, qout(std::cout, textEdit) */ {
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

    rInfo("GUI ready");
}

void
SvmacGui::startEngine() {
    rInfo("starting ...");
    textEdit->append(tr("starting ..."));

    float length = NspinBox->value();
    rDebug("frame length N = %f seconds", length);

    float overlap = static_cast<float>(RspinBox->value()) / 100.0;
    rDebug("overlapping  R = %f percent", overlap);

    rInfo("initializing Engine ...");
    textEdit->append(tr("initializing Engine ..."));
    try {
        engine.reset(new Engine(length, overlap, dmodel, cmodel));
        engine->start();
    } catch (JackException& e) {
        rError("%s", e.what());
        textEdit->append("failed:");
        textEdit->append(e.what()); // TODO parametrizzare

        QMessageBox::critical(this, tr("Error"),
                tr("Could not start the engine."));
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

void
SvmacGui::stopEngine() {
    rDebug("stopping the Engine ...");
    textEdit->append(tr("stopping the Engine ..."));
    engine->eventDetected.disconnect(boost::bind(&SvmacGui::adapterSlot, this, _1));
    engine->stop();

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

void
SvmacGui::quitApp() {
    rDebug("quitting");
    textEdit->append(tr("quitting"));

    if (engine) {
        stopEngine();
    }

    rInfo("quitting GUI");
    qApp->quit();
}

void
SvmacGui::eventDetected(const Event& event) {
    Event::Type type = event.getType();
    switch (type) {
        // TODO: refactoring (si puo` fare di meglio...)
        case Event::GUNSHOT:
            setTextRed(gunshotLabel);
            setTextDefault(screamLabel);
            setTextDefault(glassLabel);
            break;
        case Event::SCREAM:
            setTextRed(screamLabel);
            setTextDefault(gunshotLabel);
            setTextDefault(glassLabel);
            break;
        case Event::GLASS:
            setTextRed(glassLabel);
            setTextDefault(gunshotLabel);
            setTextDefault(screamLabel);
            break;
        case Event::NONE:
            setTextDefault(gunshotLabel);
            setTextDefault(screamLabel);
            setTextDefault(glassLabel);
            break;
        default:
            break;
    }
    /* TODO
    if (type != Event::NONE) {
        textEdit->append("detected event: "
                          event.getDescription());
    }
     */
}

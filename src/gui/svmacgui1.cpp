/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "version.h"
#include "svmacgui.h"
#include "engine/engine.h"

#include <boost/bind.hpp>

#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>

#include <QtGui>

SvmacGui::SvmacGui(float length, float overlap, QWidget *parent) {
   setupUi(this);
   
   // start and stop buttons
   connect(startButton, SIGNAL(clicked()), this, SLOT(start()) );
   connect(stopButton,  SIGNAL(clicked()), this, SLOT(stop()) );
   
   // about and quit buttons
   connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()) ); 
   connect(quitButton,  SIGNAL(clicked()), this, SLOT(quitApp()) );
   
   // set initial values
   NspinBox->setValue(length);
   RspinBox->setValue(overlap);

   engine = 0;
}

void SvmacGui::quitApp() {
    rDebug("quitting");
    textEdit->append("quitting");
    
    if (engine) {
        stop();
    }
    qApp->quit();
}

void SvmacGui::start() {
    rInfo("starting ...");
    textEdit->append("starting ...");
    
    float length = NspinBox->value();
    rDebug("frame length N = %f seconds", length);
    
    float overlap = (float) RspinBox->value() / 100;
    rDebug("overlapping  R = %f percent", overlap);
       
    rInfo("initializing Engine ...");
    textEdit->append("initializing Engine ...");
    try {
        if (!engine) {
             engine = new Engine(length, overlap);
        }
        engine->start();
    } catch (JackException& e) {
        rError(e.what());
        textEdit->append("failed:");
        textEdit->append(e.what());
        
        QMessageBox::critical(this, tr("Error"),
            tr("Could not start the engine.\n"
               "Please check if the Jackd server is running."));
        // TODO: show e.what()
        return;
    } 
    
    disableButton(startButton);
    enableButton(stopButton);
    
    disableSpinBox(NspinBox);
    disableSpinBox(RspinBox);
    
    engine->eventDetected.connect(boost::bind(&SvmacGui::highlightEvent, this, _1));
    
    textEdit->insertPlainText("started");
    rDebug("started");
}

void SvmacGui::stop() {
    rDebug("stopping the Engine ...");
    textEdit->append("stopping the Engine ...");
    engine->stop();
    delete engine;
    engine = 0;
    
    disableButton(stopButton);
    enableButton(startButton);
    
    enableSpinBox(NspinBox);
    enableSpinBox(RspinBox);
    
    blackLabel(gunshotLabel);
    blackLabel(screamLabel);
    blackLabel(glassLabel);
        
    textEdit->insertPlainText("done");
    rDebug("stopped");
}

void SvmacGui::highlightEvent(const Event& event) {
    EventType type = event.getType();
    switch(type) {
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

//    if (type != NONE) {
//        textEdit->append("detected event: "
//                         event.getDescription());
//    }
}

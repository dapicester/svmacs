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
   
   connect(startButton, SIGNAL(clicked()), this, SLOT(start()) );
   connect(stopButton,  SIGNAL(clicked()), this, SLOT(stop()) );
   
   connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()) ); 
   connect(quitButton,  SIGNAL(clicked()), this, SLOT(quitApp()) );
#ifdef ENABLE_DEBUG
   connect(testButton, SIGNAL(clicked()), this, SLOT(test()) );
#else
   testButton->hide();
#endif
   
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
    
    //qRegisterMetaType<Event>("Event");
    //connect( client, SIGNAL(eventDetected(const Event&)), this, SLOT(highlightEvent(const Event&)) );
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

#ifdef ENABLE_DEBUG
bool SvmacGui::flag = false;

void SvmacGui::test() {
    rDebug("test button");
    if (flag == false) {
        rDebug("text in RED");    
        gunshotLabel->setPalette(red);
    } else {
        rDebug("text in BLACK");
        gunshotLabel->setPalette(black);
    }
    flag = !flag;
}
#endif

void SvmacGui::highlightEvent(const Event& event) {
    EventType type = event.getType();
    switch(type) {
    case 0: //NONE:
        blackLabel(gunshotLabel);
        blackLabel(screamLabel);
        blackLabel(glassLabel);
        break;
    case 1: //GUNSHOT:
	redLabel(gunshotLabel);
	blackLabel(screamLabel);
        blackLabel(glassLabel);
	break;
    case 2: //SCREAM:
	redLabel(screamLabel);
	blackLabel(gunshotLabel);
        blackLabel(glassLabel);
	break;
    case 3: //GLASS:
	redLabel(glassLabel);
	blackLabel(gunshotLabel);
        blackLabel(screamLabel);
        break;
    default:
        break;    
    }
//    if (type != 0)
//        textEdit->append(event.getDescription());
}

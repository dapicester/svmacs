/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "svmacgui.h"

#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>

#include <QtGui>

SvmacGui::SvmacGui(QWidget *parent) {
   setupUi(this);
   
   connect(startButton, SIGNAL(clicked()), this, SLOT(startJackClient()) );
   connect(stopButton,  SIGNAL(clicked()), this, SLOT(stopJackClient()) );
   connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()) ); 
   connect(quitButton,  SIGNAL(clicked()), this, SLOT(quitApp()) );
   //connect(client, SIGNAL(eventDetected(EventType)), this, SLOT(highlightEvent(EventType)) );

   connect(testButton, SIGNAL(clicked()), this, SLOT(test()) );
   
   client = 0;
}

void SvmacGui::about() {
      QMessageBox::about(this, "About",
            "This is the <b>SVM Audio Classification GUI</b>\n\n"
            "Copyright 2008-2009 Paolo D'Apice - dapicester@gmail.com");
}

void SvmacGui::quitApp() {
    rDebug("quitting");
    textEdit->append("quitting");
    
    if (client != 0) {
        stopJackClient();
    }
    qApp->quit();
}

void SvmacGui::startJackClient() {
    rDebug("starting the Jack client ...");
    textEdit->append("starting the Jack client...");
    
    float N = NspinBox->value();
    rInfo("frame length N = %f seconds", N);
    
    float R = (float) RspinBox->value() / 100;
    rInfo("overlapping  R = %f percent", R);
       
    rInfo("Starting the Jack client ... ");
    client = JackClient::getInstance(N,R);
    if (client == 0) {
        rDebug("client not created");
        textEdit->insertPlainText("failed");
        
        QMessageBox::warning(this, tr("Title"),
            tr("Could not start the client.\n"
               "Please check if the Jackd server is running."));
        return;
    } 
    
    // setup & start
    client->start();
    if (!client->isRealTime())
        rWarning("WARNING! Not Realtime"); 
        
    // connecting
    try {
        if (inputCheckBox->isChecked()) {
            rDebug("connecting from input port");
            client->connectFromPhysical(0,0);
        }
	if (outputCheckBox->isChecked()) {
            rDebug("connecting to output port");
            client->connectToPhysical(0,0);
        }
    } catch (std::runtime_error e){
        rWarning("WARNING! %s", e.what());
    }    
    
    disableButton(startButton);
    enableButton(stopButton);
    
    disableSpinBox(NspinBox);
    disableSpinBox(RspinBox);
    
    disableButton(inputCheckBox);
    disableButton(outputCheckBox);
    
    textEdit->insertPlainText("started");
    rDebug("started");
}

void SvmacGui::stopJackClient() {
    rDebug("stopping the Jack client ...");
    textEdit->append("stopping the Jack client...");
    
    rDebug("disconnecting ports");
    for(unsigned int i = 0; i < client->inPorts(); i++)
        client->disconnectInPort(i);
    for(unsigned int i = 0; i < client->outPorts(); i++)
        client->disconnectOutPort(i);
    
    rDebug("cleaning up");
    client->stop();
    delete client;
    client = 0;
    
    disableButton(stopButton);
    enableButton(startButton);
    
    enableSpinBox(NspinBox);
    enableSpinBox(RspinBox);
    
    enableButton(inputCheckBox);
    enableButton(outputCheckBox);
    
    textEdit->insertPlainText("done");
    rDebug("stopped");
}

bool SvmacGui::flag = false;

void SvmacGui::test() {
	rInfo("test button");
//TODO QThread: attenzione mutex/semaphore
	if (flag == false) {
		QPalette palette(QColor(255,255,255));
		palette.setColor( QPalette::Text, QColor(255,0,0) );
		palette.setColor( QPalette::Foreground, QColor(255,0,0) );
		gunshotLabel->setPalette(palette);
	} else {
		QPalette palette2(QColor(255,255,255));
		palette2.setColor( QPalette::Text, QColor(0,255,0) );
		palette2.setColor( QPalette::Foreground, QColor(0,255,0) );
		gunshotLabel->setPalette(palette2);
	}
	flag = !flag;
}

void SvmacGui::highlightEvent(model::EventType type) {
    switch(type) {
    case 1:
	redLabel(gunshotLabel);
	break;
    case 2:
	redLabel(screamLabel);
	break;
    case 3:
	redLabel(glassLabel);
	break;
    }
}

void SvmacGui::enableButton(QAbstractButton* button) {
    button->setEnabled(true);    
}

void SvmacGui::disableButton(QAbstractButton* button) {
    button->setEnabled(false);
}

void SvmacGui::enableSpinBox(QAbstractSpinBox* spinbox) {
    spinbox->setEnabled(true);    
}

void SvmacGui::disableSpinBox(QAbstractSpinBox* spinbox) {
    spinbox->setEnabled(false);    
}

void SvmacGui::redLabel(QLabel* label) {
// colora rosso, aspetta un secondo e colora nomrmale
	QPalette palette;
	palette.setColor( QPalette::Text, QColor( Qt::red ) );
	label->setPalette(palette);
}

void SvmacGui::stdLabel(QLabel* label) {

}

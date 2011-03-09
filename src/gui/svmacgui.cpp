/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <gui/svmacgui.h>

#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>

#include <QtGui>

QPalette 
SvmacGui::getPalette(Color color) {
    rDebug("getting palette ");
    if (color == BLACK) {
        QPalette palette(QColor(255,255,255));
        palette.setColor( QPalette::Foreground, QColor(0,0,0) );
        return palette;
    } else { 
        QPalette palette(QColor(255,255,255));
        palette.setColor( QPalette::Foreground, QColor(255,0,0) );
        return palette;
    }
}

QPalette 
SvmacGui::red = getPalette(RED);

QPalette 
SvmacGui::black = getPalette(BLACK);

SvmacGui::SvmacGui(QWidget *parent) {
   setupUi(this);
   
   connect(startButton, SIGNAL(clicked()), this, SLOT(startJackClient()) );
   connect(stopButton,  SIGNAL(clicked()), this, SLOT(stopJackClient()) );
   connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()) ); 
   connect(quitButton,  SIGNAL(clicked()), this, SLOT(quitApp()) );
#ifdef ENABLE_DEBUG
   connect(testButton, SIGNAL(clicked()), this, SLOT(test()) );
#endif
#ifndef ENABLE_DEBUG
   testButton->hide();
#endif
   client = 0;
}

SvmacGui::~SvmacGui() {
    delete client;
}

void 
SvmacGui::about() {
      QMessageBox::about(this, "About",
            "This is the <b>SVM Audio Classification GUI</b>\n\n"
            "Copyright 2008-2009 Paolo D'Apice - dapicester@gmail.com");
}

void 
SvmacGui::quitApp() {
    rDebug("quitting");
    textEdit->append("quitting");
    
    if (client != 0) {
        stopJackClient();
    }
    qApp->quit();
}

void 
SvmacGui::startJackClient() {
    rDebug("starting the Jack client ...");
    textEdit->append("starting the Jack client...");
    
    float N = NspinBox->value();
    rInfo("frame length N = %f seconds", N);
    
    float R = (float) RspinBox->value() / 100;
    rInfo("overlapping  R = %f percent", R);
       
    rInfo("Starting the Jack client ... ");
    client = jack::JackClient::getInstance(N,R);
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
    
    qRegisterMetaType<model::Event>("Event");
    connect( client, SIGNAL(eventDetected(const model::Event&)), this, SLOT(highlightEvent(const model::Event&)) );
    
    textEdit->insertPlainText("started");
    rDebug("started");
}

void 
SvmacGui::stopJackClient() {
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
    
    blackLabel(gunshotLabel);
    blackLabel(screamLabel);
    blackLabel(glassLabel);
        
    textEdit->insertPlainText("done");
    rDebug("stopped");
}

#ifdef ENABLE_DEBUG
bool SvmacGui::flag = false;

void 
SvmacGui::test() {
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

void 
SvmacGui::highlightEvent(const model::Event& event) {
    model::EventType type = event.getType();
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
    }
//    if (type != 0)
//        textEdit->append(event.getDescription());
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
    rDebug("text in RED");    
    /*
    QPalette palette(QColor(255,255,255));
    palette.setColor( QPalette::Foreground, QColor(255,0,0) );
    label->setPalette(palette);
    */
    label->setPalette(red);
}

void SvmacGui::blackLabel(QLabel* label) {
    rDebug("text in BLACK");
    /*
    QPalette palette(QColor(255,255,255));
    palette.setColor( QPalette::Foreground, QColor(0,0,0) );
    label->setPalette(palette);
    */
    label->setPalette(black);
}

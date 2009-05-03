/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#define RLOG_COMPONENT "gui"
#include <rlog/rlog.h>

#include <QtGui>
#include "svmacgui.h"

SvmacGui::SvmacGui(QWidget *parent) {
   setupUi(this);
   
   connect(startButton, SIGNAL(clicked()), this, SLOT(startJackClient()) );
   connect(stopButton,  SIGNAL(clicked()), this, SLOT(stopJackClient()) );
   connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()) ); 
   connect(quitButton,  SIGNAL(clicked()), this, SLOT(quitApp()) );
   
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
    
    client = JackClient::getInstance();
    if (client == 0) {
        rDebug("client not created");
        textEdit->insertPlainText("failed");
        
        QMessageBox::warning(this, tr("Title"),
            tr("Could not start the client.\n"
               "Please check if the Jackd server is running."));
        return;
    } 
    client->start();
    
    disableButton(startButton);
    enableButton(stopButton);
    
    textEdit->insertPlainText("started");
    rDebug("started");
}

void SvmacGui::stopJackClient() {
    rDebug("stopping the Jack client ...");
    textEdit->append("stopping the Jack client...");
    
    client->stop();
    delete client;
    
    disableButton(stopButton);
    enableButton(startButton);
    
    textEdit->insertPlainText("done");
    rDebug("stopped");
}

void SvmacGui::enableButton(QPushButton* button) {
    button->setEnabled(true);    
}

void SvmacGui::disableButton(QPushButton* button) {
    button->setEnabled(false);
}

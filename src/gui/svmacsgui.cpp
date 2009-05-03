/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#define RLOG_COMPONENT "jackclient"
#include <rlog/rlog.h>

#include <QtGui>
#include "svmacsgui.h"

SvmacGui::SvmacGui(QWidget *parent) {
   setupUi(this);
   
   connect( startButton, SIGNAL( clicked() ), this, SLOT( startJackClient() ) );
   connect( stopButton, SIGNAL( clicked() ), this, SLOT( stopJackClient() ) );   
   connect( quitButton, SIGNAL( clicked() ), this, SLOT( quitApp() ) );
   
   client = 0;
}

void SvmacGui::about() {
      QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
                  "write modern GUI applications using Qt, with a menu bar, "
                  "toolbars, and a status bar."));
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
    textEdit->append("starting the Jack client ...");
    
    client = new JackClient;
    client->start();
    
    disableButton(startButton);
    enableButton(stopButton);
    
    rDebug("started");
}

void SvmacGui::stopJackClient() {
    rDebug("stopping the Jack client ...");
    textEdit->append("stopping the Jack client ...");
    
    client->stop();
    delete client;
    
    disableButton(stopButton);
    enableButton(startButton);
    
    rDebug("stopped");
}

void SvmacGui::enableButton(QPushButton* button) {
    button->setEnabled(true);    
}

void SvmacGui::disableButton(QPushButton* button) {
    button->setEnabled(false);
}

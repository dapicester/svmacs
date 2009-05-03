/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#define RLOG_COMPONENT "cli"
#include <rlog/rlog.h>

#include <iostream>
#include <csignal>

#include "svmaccli.h"

using namespace std;

SvmacCli::SvmacCli() {
    rDebug("constructor invoked");
}

SvmacCli::~SvmacCli() {
     rDebug("destructor invoked");
}

int SvmacCli::mainLoop() {
    rDebug("CLI main loop");
 /*   
    cout << "Starting the Jack client ... ";
    
    client = JackClient::getInstance();
    if (client == 0) {
        rDebug("client not created");
        cout << "failed!" << endl;
        
        cout << "Could not start the client. "
                "Please check if the Jackd server is running." << endl;
        exit(1);
    } 
    client->start();
    cout << "ok" << endl;
  */  
    cout << "use CTRL-C to quit" << endl;
    
    // loop
    signal(SIGABRT, &quitproc);
    signal(SIGTERM, &quitproc);
    signal(SIGINT, &quitproc);
    while(1) {}
    
    return 0;
}

void quitproc(int) {
    rDebug("CTRL-C trapped");
    cout << "quitting" << endl << endl;
    exit(0);
}

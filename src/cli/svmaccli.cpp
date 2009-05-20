/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "svmaccli.h"
using namespace cli;

#define RLOG_COMPONENT "cli"
#include <rlog/rlog.h>

#include <iostream>
#include <csignal>

using namespace std;

SvmacCli* SvmacCli::instance = 0;

SvmacCli::SvmacCli() {
    rDebug("constructor invoked");
}

SvmacCli::~SvmacCli() {
     rDebug("destructor invoked");
}

SvmacCli* SvmacCli::getInstance() {
    if (instance == 0) {
        rDebug("instantiating singleton");
        instance = new SvmacCli();
    } 
    return instance;
}

void SvmacCli::mainLoop(float N, float R) {
    rDebug("CLI main loop");
    
    cout << "Starting the Jack client ... " << endl;
    
    //TODO aggiungere parametro N
    client = JackClient::getInstance(R);
    if (client == 0) {
        rDebug("client not created");
        cout << "failed!" << endl;
        
        cout << "Could not start the client. "
                "Please check if the Jackd server is running." << endl;
        exit(1);
    } 
    
    // setup & start
    client->start();
    if (!client->isRealTime())
        cout << "WARNING! Not Realtime" << endl; 
    cout << "Jack client started" << endl;

#ifdef ENABLE_DEBUG    
    // status
    rDebug("inport names:");
    for(unsigned int i = 0; i < client->inPorts(); i++)
        rDebug("   %s", client->getInputPortName(i).c_str());
    
    rDebug("outport names:");
    for(unsigned int i = 0; i < client->outPorts(); i++)
        rDebug("   %s", client->getOutputPortName(i).c_str());
#endif

    try {
	client->connectFromPhysical(0,0);
	client->connectToPhysical(0,0);
    } catch (std::runtime_error e){
        cout << "WARNING! " << e.what() << endl;
    }
    
    // trap signals
    cout << "use CTRL-C to quit" << endl;
    signal(SIGABRT, &cleanup);
    signal(SIGTERM, &cleanup);
    signal(SIGINT, &cleanup);
    
    // main loop
    while(true) {
        //client->getAudioFrame();
        sleep(1);        
    }
    
    //sleep(3);
    cleanup(99);
}

void SvmacCli::cleanup(int signal) {  
    if (signal == 99) rDebug("timeout"); 
    else rDebug("CTRL-C trapped");
    cout << "quitting ... ";

    rDebug("getting client pointer");
    JackClient* client = SvmacCli::getInstance()->client;
    
    rDebug("disconnecting ports");
    for(unsigned int i = 0; i < client->inPorts(); i++)
        client->disconnectInPort(i);
    for(unsigned int i = 0; i < client->outPorts(); i++)
        client->disconnectOutPort(i);
        
    rDebug("cleaning up");
    client->close();	// stop client.
    delete client;
    
    cout << "done" << endl << endl;
    exit(0);
}

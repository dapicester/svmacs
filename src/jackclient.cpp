/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include"jackclient.h"
#define MIN(x,y) ((x) < (y) ? (x) : (y))

JackClient* JackClient::instance = 0;

JackClient* JackClient::getInstance() {
    if ( instance == 0 ) {
        // initial ports from constructor created here.
        instance = new JackClient;  
    }
    return instance;        
}

JackClient::JackClient() : JackCpp::AudioIO("jackcpp-test", 2, 2) {
    instance->start();  // activate the client
    
    //connect our ports to physical ports
    instance->connectToPhysical(0,0);    // connects this client out port 0 to physical destination port 0
    instance->connectToPhysical(1,1);    // connects this client out port 1 to physical destination port 1
    instance->connectFromPhysical(0,0);  // connects this client in port 0 to physical source port 0
    instance->connectFromPhysical(1,1);  // connects this client in port 1 to physical source port 1
    
    sleep(20);    // sleep to allow the callback to run for 20 seconds.
    instance->close();  // stop client.
    delete instance;  // always clean up after yourself.
    exit(0);
}

int JackClient::audioCallback(jack_nframes_t nframes, 
                                      audioBufVector inBufs,
                                      audioBufVector outBufs) {
    for(unsigned int i = 0; i < MIN(inBufs.size(),outBufs.size()); i++) {
        // A simple example: copy the input to the output.
        for(unsigned int j = 0; j < nframes; j++) {
            outBufs[i][j] = inBufs[i][j];  
        }
    }
    //0 on success
    return 0;
}   
    

/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#define RLOG_COMPONENT "jackclient"
#include <rlog/rlog.h>

#include"jackclient.h"
#define MIN(x,y) ((x) < (y) ? (x) : (y))

JackClient* JackClient::getInstance() {
    JackClient* client = 0;
    try {
        client = new JackClient;
    } catch (std::runtime_error) {
        rWarning("Could not create the client: Jackd not running!");
    }
    return client;
}

JackClient::JackClient() : JackCpp::AudioIO("svm-acs", NUM_INPUT, NUM_OUTPUT, false) {
    rDebug("constructor called");
}

JackClient::~JackClient() {
//     delete instance;
    rDebug("destructor called");
}

/** Jack Audio callback. */
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
    

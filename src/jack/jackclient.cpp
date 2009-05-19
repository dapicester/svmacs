/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include"jackclient.h"

#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define RLOG_COMPONENT "jackclient"
#include <rlog/rlog.h>

#include <iostream>
using namespace std;

JackClient::JackClient() : 
                JackCpp::AudioIO("svm-acs", NUM_INPUT, NUM_OUTPUT, false),
                buffer(this->getSampleRate() * 2.0) {
    rDebug("constructor called");

    reserveInPorts(MAX_IN);
    reserveOutPorts(MAX_OUT);
    
    rInfo("create a Jack client named %s with #in=%d and #out=%d","svn-acs", NUM_INPUT, NUM_OUTPUT);
}

JackClient::~JackClient() {
    rDebug("destructor called");
}

JackClient* JackClient::getInstance() {
    JackClient* client = 0;
    try {
        client = new JackClient;
        rInfo("sample rate: %f", (float) client->getSampleRate());       
    } catch (std::runtime_error) {
        rWarning("Could not create the client: Jackd not running!");
    }
    return client;
}

/** Jack Audio callback. */
int JackClient::audioCallback(jack_nframes_t nframes, 
                              audioBufVector inBufs,
                              audioBufVector outBufs) {
    for(unsigned int i = 0; i < inBufs.size(); i++) {
        for(unsigned int j = 0; j < nframes; j++) {
            //outBufs[i][j] = inBufs[i][j];  
            buffer.write(inBufs[i][j]);
        }
    }
    //0 on success
    return 0;
}   

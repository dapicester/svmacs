/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include"jackclient.h"
using namespace jack;

#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define RLOG_COMPONENT "jackclient"
#include <rlog/rlog.h>

#include <cmath>

#include <iostream>
using namespace std;

JackClient::JackClient(float length, float overlap) : 
                JackCpp::AudioIO("svm-acs", NUM_INPUT, NUM_OUTPUT, false),
                N(floor(length * getSampleRate())),
                R(floor(N * overlap)),            
                input(N * 2.0 + 1.0), 
                processor(getSampleRate()) {
    rDebug("constructor called");

    // reserve ports
    reserveInPorts(MAX_IN);
    reserveOutPorts(MAX_OUT);
    rDebug("reserved ports: %d IN, %d OUT", MAX_IN, MAX_OUT); 
    
    // allocate buffer for current frame
    frame = new double[N];               
    
    rInfo("create a Jack client named %s with #in=%d and #out=%d","svn-acs", NUM_INPUT, NUM_OUTPUT);
}

void JackClient::init() {
    //TODO if necessary, extra init here ...
}

JackClient::~JackClient() {
    rDebug("destructor called");
}

JackClient* JackClient::getInstance(float length, float overlap) {
    JackClient* client = 0;
    try {
        client = new JackClient(length, overlap);
        client->init();
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
    //rDebug("callback");
    for(uint i = 0; i < inBufs.size(); i++) {
        for(uint j = 0; j < nframes; j++) {
            // fill the buffer
            input.write(inBufs[i][j]);
            // copy to output
            outBufs[i][j] = inBufs[i][j];
            
            // FIXME che fare col valore ritornato?
            processFrame();
            
        }
    }
    //0 on success
    return 0;
}

vec* JackClient::processFrame() {
    vec* out = 0;
    if (input.getReadSpace() >= N) {
        rDebug("there are %d samples in the input buffer", N);
        if (R > 0) { // overlapping frames
            input.read(frame, R);    // read the first R samples
            input.peek(frame+R, N-R);// and peek the remaining N-R samples 
        } else { // no overlapping frames
            input.read(frame, N);
        }
        vec* vframe = new vec(frame, N);
        out = processor.process(*vframe);
    } 
    return out;
}

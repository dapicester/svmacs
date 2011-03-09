/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <jack/jackclient.h>
using namespace jack;

#include <model/svmclassifier.h>
using namespace model;

#define RLOG_COMPONENT "jackclient"
#include <rlog/rlog.h>

#include <cmath>
#include <iostream>
using namespace std;

JackClient::JackClient(float length, float overlap) : 
                JackCpp::AudioIO("svmacs", NUM_INPUT, NUM_OUTPUT, false),
                N(floor(length * getSampleRate())),
                R(floor(N * overlap)), 
                input(N * 2.0 + 1.0), 
                processor(getSampleRate()) {
    rDebug("constructor invoked");
    
    // reserve ports
    reserveInPorts(MAX_IN);
    reserveOutPorts(MAX_OUT);
    rDebug("reserved ports: %d IN, %d OUT", MAX_IN, MAX_OUT); 
    
    // allocate buffer for current frame
    frame = new double[N];
    
    // instantiate a classifier
    classifier = new SvmClassifier();
    prev = NONE;
    
    rInfo("created a Jack client named %s with #in=%d and #out=%d","svn-acs", NUM_INPUT, NUM_OUTPUT);
}

JackClient::~JackClient() {
    rDebug("destructor called");
    delete[] frame;
    delete classifier;
}

JackClient* JackClient::getInstance(float length, float overlap) {
    JackClient* client = 0;
    try {
        client = new JackClient(length, overlap);
        rInfo("sample rate: %5.0f", (float) client->getSampleRate());
    } catch (std::runtime_error) {
        rWarning("Could not create the client: Jackd not running!");
    }
    return client;
}

// Jack Audio callback.
int 
JackClient::audioCallback(jack_nframes_t nframes, 
                          audioBufVector inBufs,
                          audioBufVector outBufs) {
    //rDebug("callback");
    for(uint i = 0; i < inBufs.size(); i++) {
        for(uint j = 0; j < nframes; j++) {
            // fill the buffer
            input.write(inBufs[i][j]);
            // copy to output
            outBufs[i][j] = inBufs[i][j];
            
            processFrame();
        }
    }
    //0 on success
    return 0;
}

void 
JackClient::processFrame() {
    if (input.getReadSpace() >= N) {
        rDebug("there are %d samples in the input buffer", N);
        if (R > 0) { // overlapping frames
            input.read(frame, R);    // read the first R samples
            input.peek(frame+R, N-R);// and peek the remaining N-R samples 
        } else { // no overlapping frames
            input.read(frame, N);
        }

#if 1 // enable input processing
        itpp::vec vframe(frame,N);
        itpp::vec ff = processor.process(vframe);
#endif

#if 0
#ifdef ENABLE_LOG
        rDebug("feature vector:");
        cout << ff << endl;
#endif
#endif

#if 1 // enable the classifier        
        EventType type = classifier->classify(ff);
        if (type != prev) {
            const char* message;
            if (type != NONE) {
                switch (type) {
                case NONE:    message = "none";    break;
                case GUNSHOT: message = "GUNSHOT"; break;
                case SCREAM:  message = "SCREAM";  break;
                case GLASS:   message = "GLASS";   break;
                } 
                rInfo("Detected EventType: %s", message);
            }
            Event e(type, message);
            emit eventDetected(e);
            prev = type;
        }
#endif
    } 
}

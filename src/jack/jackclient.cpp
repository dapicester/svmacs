/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "jackclient.h"
#include "jack/ringbufferread.h"
#include "engine/engine.h"

#define RLOG_COMPONENT "jackclient"
#include <rlog/rlog.h>

#include <cmath>
#include <iostream>

/// Maximum number of input ports
static const unsigned int MAX_IN = 1;
/// Maximum number of output ports
static const unsigned int MAX_OUT = 1;

/// Number of input ports
static const unsigned int NUM_INPUT = 1; // mono input
/// Number of output ports
static const unsigned int NUM_OUTPUT = 1; // monitor output

/// Client name
static const char* CLIENT_NAME = "svmacs";

JackClient::JackClient(float len, float olap, Engine* e) :
        JackCpp::AudioIO("svmacs", NUM_INPUT, NUM_OUTPUT, false) {
    rInfo("initializing JackClient ...");

    reserveInPorts(MAX_IN);
    reserveOutPorts(MAX_OUT);
    rDebug("reserved ports: %d IN, %d OUT", MAX_IN, MAX_OUT);

    // init attributes
    length = std::floor(len * getSampleRate());
    overlap = std::floor(length * olap/100);
    rDebug("frame length set to %d samples with %d overlapping samples", length, overlap);

    rDebug("initializing input buffer");
    input = new RingBufferRead(length * 2 + 1);
    // allocating buffer for current frame
    frame = new double[static_cast<int>(length)];

    rWarning("Jack %s running in realtime mode", isRealTime() ? "is" : "is not");

    rDebug("input port names:");
    for(unsigned int i = 0; i < inPorts(); i++)
        rDebug("   [%s]", getInputPortName(i).c_str());

    rDebug("output port names:");
    for(unsigned int i = 0; i < outPorts(); i++)
        rDebug("   [%s]", getOutputPortName(i).c_str());

    rDebug("saving pointer to Engine");
    engine = e;

    rInfo("JackClient [%s] created (#in=%d, #out=%d)", CLIENT_NAME, NUM_INPUT, NUM_OUTPUT);
}

JackClient::~JackClient() {
    rDebug("closing JackClient ...");
    close();

    delete[] frame;
    delete input;

    rInfo("JackClient correctly destroyed");
}

void JackClient::connect() {
    try {
#if 0 /* enable/disable auto connect from audio input */
        rDebug("connecting from input port ...");
        connectFromPhysical(0, 0);
#endif

#if 0 /* enable/disable auto connect to audio output */
        rDebug("connecting to output port ...");
        connectToPhysical(0, 0);
#endif
    } catch (std::runtime_error e){
        rWarning(e.what());
        //throw e; // continue processing?
    }
}

void JackClient::disconnect() {
    rDebug("disconnecting ports");

    for(unsigned int i = 0; i < inPorts(); i++)
        disconnectInPort(i);

    for(unsigned int i = 0; i < outPorts(); i++)
        disconnectOutPort(i);
}

// Jack Audio callback.
int JackClient::audioCallback(jack_nframes_t nframes,
                          audioBufVector inBufs,
                          audioBufVector outBufs) {
    for(unsigned int i = 0; i < inBufs.size(); i++) {
        for(unsigned int j = 0; j < nframes; j++) {
            // fill the buffer
            input->write(inBufs[i][j]);
            // copy to output
            outBufs[i][j] = inBufs[i][j];

            checkData();
        }
    }



    //0 on success
    return 0;
}

void JackClient::checkData() {
    if (input->getReadSpace() < length) {
        //rDebug("not enough samples in the input buffer (%d)", input->getReadSpace());
        return;
    }

    //rDebug("there are enough samples in the input buffer (%d)", input->getReadSpace());
    if (overlap > 0) { // overlapping frames
        input->read(frame, length - overlap);      // read the first (R - N) non overlapping samples
        input->peek(frame + overlap, overlap);     // and peek the remaining overlapping (R) samples
    } else {           // non overlapping frames
        input->read(frame, length);
    }

    // send signal
    itpp::vec data(frame, length);
    //gotInputData(data);
    engine->processFrame(data);
}

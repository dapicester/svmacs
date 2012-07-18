/*
 * Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "jackclient.h"
#include "engine/engine.h"

#define RLOG_COMPONENT "jackclient"
#include <rlog/rlog.h>

#include <cmath>
#include <iostream>

NS_SVMACS_BEGIN

/// Maximum number of input ports
const unsigned int MAX_IN = 1;
/// Maximum number of output ports
const unsigned int MAX_OUT = 1;

/// Number of input ports
const unsigned int NUM_INPUT = 1; // mono input
/// Number of output ports
const unsigned int NUM_OUTPUT = 1; // monitor output

/// Client name
const char CLIENT_NAME[] = "svmacs";

JackClient::JackClient(const float len, const float olap, const Engine& e) :
        JackCpp::AudioIO("svmacs", NUM_INPUT, NUM_OUTPUT, false), engine(e) {
    rInfo("initializing JackClient ...");

    reserveInPorts(MAX_IN);
    reserveOutPorts(MAX_OUT);
    rDebug("reserved ports: %d IN, %d OUT", MAX_IN, MAX_OUT);

    // init attributes
    length = std::floor(len * getSampleRate());
    overlap = std::floor(length * olap/100);
    rDebug("frame length set to %d samples with %d overlapping samples", length, overlap);

    rDebug("initializing input buffer");
    input.reset(new RingBuffer(length * 2 + 1));
    // allocating buffer for current frame
    frame.reset(new double[static_cast<int>(length)]);

    rWarning("Jack %s running in realtime mode: %s",
            isRealTime() ? "is" : "is not",
            isRealTime() ? "NOT good!" : "ok" );

    rDebug("input port names:");
    for(unsigned int i = 0; i < inPorts(); i++)
        rDebug("   [%s]", getInputPortName(i).c_str());

    rDebug("output port names:");
    for(unsigned int i = 0; i < outPorts(); i++)
        rDebug("   [%s]", getOutputPortName(i).c_str());

    rInfo("JackClient [%s] created (#in=%d, #out=%d)", CLIENT_NAME, NUM_INPUT, NUM_OUTPUT);
}

JackClient::~JackClient() {
    rDebug("closing JackClient ...");
    close();

    rInfo("JackClient correctly destroyed");
}

void
JackClient::connect() {
    try {
#if 0 /* enable/disable auto connect from audio input */
        rDebug("connecting from input port ...");
        connectFromPhysical(0, 0);
#endif

#if 0 /* enable/disable auto connect to audio output */
        rDebug("connecting to output port ...");
        connectToPhysical(0, 0);
#endif
    } catch (std::runtime_error& e){
        rWarning("%s", e.what());
        //throw e; // continue processing?
    }
}

void
JackClient::disconnect() {
    rDebug("disconnecting ports");

    for(unsigned int i = 0; i < inPorts(); i++)
        disconnectInPort(i);

    for(unsigned int i = 0; i < outPorts(); i++)
        disconnectOutPort(i);
}

// Jack Audio callback.
int
JackClient::audioCallback(jack_nframes_t nframes,
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

    return 0; // 0 on success
}

void
JackClient::checkData() {
    if (input->getReadSpace() < length) {
        //rDebug("not enough samples in the input buffer (%d)", input->getReadSpace());
        return;
    }

    //rDebug("there are enough samples in the input buffer (%d)", input->getReadSpace());
    if (overlap > 0) { // overlapping frames
        input->read(frame.get(), length - overlap);      // read the first (R - N) non overlapping samples
        input->peek(frame.get() + overlap, overlap);     // and peek the remaining overlapping (R) samples
    } else {           // non overlapping frames
        input->read(frame.get(), length);
    }

    itpp::vec data(frame.get(), length); // TODO: use pointer!
    engine.processFrame(data);
}

NS_SVMACS_END

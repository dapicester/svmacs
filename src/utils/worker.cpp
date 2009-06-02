/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "worker.h"
using utils::Worker;

//Worker::Worker(Processor* processor, RingBufferRead* buffer) : Thread() {
//Worker::Worker(Processor* processor) : Thread() {
Worker::Worker(JackClient* client) : Thread()  {
    //p = processor;
    //b = buffer;
    c = client;
}

Worker::~Worker() {}

void Worker::run() {
/*    while(true) {
        client->processFrame();
        Thread::microSleep(500000);
    }
 */
/*
    if (input->getReadSpace() >= N) {
        //rDebug("there are %d samples in the input buffer", N);
        if (R > 0) { // overlapping frames
            input.read(frame, R);    // read the first R samples
            input.peek(frame+R, N-R);// and peek the remaining N-R samples 
        } else { // no overlapping frames
            input.read(frame, N);
        }
        vec* vframe = new vec(frame, N);
        out = processor.process(*vframe);
    } */
}

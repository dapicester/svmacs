/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef JACKCLIENT_H
#define JACKCLIENT_H

#include "ringbufferread.h"
#include <jackaudioio.hpp>

class JackClient : public JackCpp::AudioIO {

    static const int MAX_IN = 1;
    static const int MAX_OUT = 1;
    
    RingBufferRead<float> buffer;
    
     /** Constructor. */
    JackClient();
     /** Copy Constructor. */
    JackClient(JackClient&);
    
public:
    /** Get an instance of the Jack client. */
    static JackClient* getInstance();

    /** Destructor. */
    ~JackClient();
    
    /** Input ports. (mono input) */
    static const unsigned int NUM_INPUT = 1;
    /** Output ports. (no output) */
    static const unsigned int NUM_OUTPUT = 0;
    
    /** Audio callback. All audio processing goes in this function. */
    int audioCallback(jack_nframes_t nframes, 
                      audioBufVector inBufs,
                      audioBufVector outBufs);
                                                           
};

#endif // JACKCLIENT_H

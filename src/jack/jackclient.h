/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef JACKCLIENT_H
#define JACKCLIENT_H

#include "ringbufferread.h"
#include <jackaudioio.hpp>

namespace jack {

class JackClient : public JackCpp::AudioIO {

    static const uint MAX_IN = 1;
    static const uint MAX_OUT = 1;
    
    /** Overlap. */
    uint R; 
    /** Frame length. */
    uint N;
    /** Input buffer. */
    RingBufferRead input;
    /** Current frame. */
    RingBufferRead buffer;
    
    /// temporary storage 
    float* frame;
    
     /** Constructor. */
    JackClient(float overlap);
     /** Copy Constructor. */
    JackClient(JackClient&);
    
    /// Initializations.
    void init();
    
public:
    /** Get an instance of the Jack client. */
    static JackClient* getInstance(float overlap = 0.0);

    /** Destructor. */
    ~JackClient();
    
    /** Input ports. (mono input) */
    static const uint NUM_INPUT = 1;
    /** Output ports. (monitor output) */
    static const uint NUM_OUTPUT = 1;
    
    /** Audio callback. All audio processing goes in this function. */
    int audioCallback(jack_nframes_t nframes, 
                      audioBufVector inBufs,
                      audioBufVector outBufs);
                                                           
private:
    /** Read one audio frame */
    void getAudioFrame();
};

}

#endif // JACKCLIENT_H

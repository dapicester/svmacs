/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef JACKCLIENT_H
#define JACKCLIENT_H

#include "config.h"
#include <jackaudioio.hpp>

#include <itpp/base/vec.h>
#include <boost/noncopyable.hpp>
//#include <boost/signals2.hpp>

NS_SVMACS_BEGIN

class RingBufferRead;
class Engine;

/**
 * This class implement a Jack client, providing the implementation
 * of the Jack callback function.
 */
class JackClient 
        : public JackCpp::AudioIO , boost::noncopyable {

public:
    /**
     * Instantiate a new Jack client.
     * @param length
     *          frame length (seconds)
     * @param overlap
     *          frame overlapping ratio
     */
    JackClient(float length, float overlap, Engine* engine);
    ~JackClient();
    
    /**
     * Automatically connect input/output ports.
     */
    void connect();
    
    /**
     * disconnect all input/output ports.
     */
    void disconnect();

    /// Signals raised when input audio data are ready for processing
    //boost::signals2::signal<void (const itpp::vec&)> gotInputData;

private:
    /// frame length (samples)
    unsigned int length;
    /// frame overlap (samples)
    unsigned int overlap;
    
    /// The input ring buffer.
    RingBufferRead* input;
    /// The current frame.
    double* frame;

    /** 
     * Audio callback. 
     * All audio processing goes in this function. 
     */
    int audioCallback(jack_nframes_t nframes,
            audioBufVector inBufs,
            audioBufVector outBufs);
    
    /// access data in buffer and eventually send a signal
    void checkData();    
    
    Engine* engine;
};

NS_SVMACS_END
        
#endif // JACKCLIENT_H

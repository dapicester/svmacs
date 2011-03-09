/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef JACKCLIENT_H
#define JACKCLIENT_H

#include <features/processor.h>
#include <model/classifier.h>
#include <model/event.h>
#include <jack/ringbufferread.h>
#include <jackaudioio.hpp>

#include <itpp/itsignal.h>
#include <QObject>

namespace jack {

/**
 * This class implement a Jack client, providing the implementation
 * of the Jack callback function.
 */
class JackClient : public QObject, public JackCpp::AudioIO {

    Q_OBJECT

public:

    /**
     * Factory method.
     * Get the Jack client instance.
     * \param length frame length in seconds (defaults to 1 second)
     * \param overlap percentage of frame overlap (defaults to 0)
     */
    static JackClient* getInstance(float length = 0.5, float overlap = 0.25);

    JackClient(float length, float overlap);
    JackClient(JackClient&);
    ~JackClient();

signals:

    /// Signal emitted on event detection.
    void eventDetected(const model::Event&);

private:

    /// Maximum number of input ports
    static const uint MAX_IN = 1;
    /// Maximum number of output ports
    static const uint MAX_OUT = 1;
    /// Number of input ports 
    static const uint NUM_INPUT = 1; // mono input
    /// Number of output ports 
    static const uint NUM_OUTPUT = 1; // monitor output

    /// Frame length in samples
    uint N;
    /// Frame overlap in samples
    uint R;

    /// Input buffer
    RingBufferRead input;
    /// Current frame
    double* frame;

    /// Audio frame processor
    features::Processor processor;

    /// Audio classifier
    model::Classifier* classifier;

    /// Previous detected event type
    model::EventType prev;

    /** 
     * Audio callback. 
     * All audio processing goes in this function. 
     */
    int audioCallback(jack_nframes_t nframes,
            audioBufVector inBufs,
            audioBufVector outBufs);

    /// Process samples from the input buffer
    void processFrame();

};

}

#endif // JACKCLIENT_H

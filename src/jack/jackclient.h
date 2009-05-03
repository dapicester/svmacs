/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef JACKCLIENT_H
#define JACKCLIENT_H
#include <jackaudioio.hpp>

class JackClient : public JackCpp::AudioIO {
    /** Singleton instance */
//  static JackClient* instance;
    
     /** Constructor. */
//    JackClient();
     /** Copy Constructor. */
    JackClient(JackClient&);
    /** Destructor. */
//    ~JackClient();
    
public:
    JackClient();
    ~JackClient();
    
    /** Input ports. (mono input) */
    static const unsigned int NUM_INPUT = 1;
    
    /** Output ports. (no output) */
    static const unsigned int NUM_OUTPUT = 0;

    /** Get the singleton instance of the Jack client. */
    static JackClient* getInstance();
    
    /** Audio callback. All audio processing goes in this function. */
    int audioCallback(jack_nframes_t nframes, 
                              audioBufVector inBufs,
                              audioBufVector outBufs);
};

#endif // JACKCLIENT_H
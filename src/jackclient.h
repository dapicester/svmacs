/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef JACKCLIENT_H
#define JACKCLIENT_H
#include<jackaudioio.hpp>

class JackClient : public JackCpp::AudioIO {
    /** Singleton instance */
    static JackClient* instance;
    
     /** Constructor. */
    JackClient();
     /** Copy Constructor. */
    JackClient(JackClient&);
public:
   static JackClient* getInstance();
    
    /** Audio callback. All audio processing goes in this function. */
    virtual int audioCallback(jack_nframes_t nframes, 
                              audioBufVector inBufs,
                              audioBufVector outBufs);
};

#endif // JACKCLIENT_H

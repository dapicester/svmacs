/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef WORKER_H
#define WORKER_H
/* 
#include "../features/processor.h"
using features::Processor;
*/
/*
#include "../jack/ringbufferread.h"
using jack::RingBufferRead;
*/
#include "../jack/jackclient.h"
using jack::JackClient;
//using namespace jack;

#include <OpenThreads/Thread>
using OpenThreads::Thread;

namespace utils {
 
class Worker : public Thread {
    //Processor* p;
    //RingBufferRead *b;
    JackClient* c;  
public:
    //Worker(Processor* processor, RingBufferRead buffer);
    //Worker(Processor* processor);
    Worker(JackClient* client);
    ~Worker();
    
    void run();

};

}

#endif

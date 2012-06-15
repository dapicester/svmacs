/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "engine.h"

#include "processor/processor.h"
#include "classifier/svmclassifier.h"
#include "model/event.h"
#include "jack/jackclient.h"

#include <itpp/itbase.h>

#define RLOG_COMPONENT "engine"
#include <rlog/rlog.h>

NS_SVMACS_BEGIN

Engine::Engine(float length, float overlap) throw (JackException, BadModel)
        : previousEvent(NONE) {
    rDebug("frame length set to %.2f seconds with %.2f %% overlap", length, overlap);
       
    try {
        rDebug("connecting to Jack ...");
        client = new JackClient(length, overlap, this);
    } catch (std::runtime_error& e) {
        std::string msg = "could not create the client: is Jack server running?";
        rError("%s", msg.c_str());
        throw JackException(msg);
    }

    const int sampleRate = client->getSampleRate();
    rInfo("sample rate set to: %d samples/second", client->getSampleRate());
    
    //rDebug("connecting JackClient.gotInputData() signal to Engine.processFrame() slot");
    //client->gotInputData.connect(boost::bind(&Engine::processFrame, this, _1));

    rDebug("instantiating Processor");
    processor = new Processor(sampleRate);
    
    rDebug("instantiating Classifier");
    classifier = new SvmClassifier;
    
    rInfo("Engine ready");
}

Engine::~Engine() {
    delete classifier;
    delete processor;
    delete client;
    rInfo("Engine correctly destroyed");
}

void Engine::start() {
    rDebug("starting JackClient");
    client->start();
    client->connect();
    
    // TODO altro?
    rInfo("Engine started");
}

void Engine::stop() {
    rDebug("stopping JackClient");
    client->disconnect();
    client->stop();
    
    rInfo("Engine stopped");
}

void Engine::processFrame(const itpp::vec& frame) const {    
#if 1 // enable/disable input processing
    itpp::vec features = processor->process(frame);
    //rDebug("feature vector: %s", itpp::to_str(features).c_str());
#endif

#if 1 // enable/disable the classifier        
    EventType type = classifier->classify(features);
    if (type != previousEvent) {
        // FIXME sistemare!!!
        std::string message = "none";
        if (type != NONE) {
            switch (type) {
            case GUNSHOT: 
                message = "GUNSHOT"; 
                break;
            case SCREAM:  
                message = "SCREAM";  
                break;
            case GLASS:   
                message = "GLASS";   
                break;
            default: 
                break;
            } 
            rInfo("Detected EventType: %s", message.c_str());
        }
        Event e(type, message);
        // emit signal
        eventDetected(e);
        previousEvent = type;
    }
#endif
}

NS_SVMACS_END

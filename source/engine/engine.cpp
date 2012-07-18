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

#include "engine.h"

#include "processor/processor.h"
#include "classifier/svmclassifier.h"
#include "model/event.h"
#include "jack/jackclient.h"

#include <itpp/itbase.h>

#define RLOG_COMPONENT "engine"
#include <rlog/rlog.h>

NS_SVMACS_BEGIN

using std::string;

Engine::Engine(const float length, const float overlap,
        const string& dmodel, const string& cmodel)
        : previousEvent(Event::NONE) {
    rDebug("frame length set to %.2f seconds with %.2f %% overlap", length, overlap);

    try {
        rDebug("connecting to Jack ...");
        client.reset(new JackClient(length, overlap, *this));
    } catch (std::runtime_error& e) {
        string msg = "could not create the client: is Jack server running?";
        rError("%s", msg.c_str());
        throw JackException(msg);
    }

    const int sampleRate = client->getSampleRate();
    rInfo("sample rate set to: %d samples/second", client->getSampleRate());

    //rDebug("connecting JackClient.gotInputData() signal to Engine.processFrame() slot");
    //client->gotInputData.connect(boost::bind(&Engine::processFrame, this, _1));

    rDebug("instantiating Processor");
    processor.reset(new Processor(sampleRate));

    rDebug("instantiating Classifier");
    classifier.reset(new SvmClassifier(dmodel, cmodel));

    rInfo("Engine ready");
}

Engine::~Engine() {
    rInfo("Engine correctly destroyed");
}

void
Engine::start() {
    rDebug("starting JackClient");
    client->start();
    client->connect();

    // TODO altro?
    rInfo("Engine started");
}

void
Engine::stop() {
    rDebug("stopping JackClient");
    client->disconnect();
    client->stop();

    rInfo("Engine stopped");
}

void
Engine::processFrame(const itpp::vec& frame) const {
#if 1 // enable/disable input processing
    itpp::vec features = processor->process(frame);
    //rDebug("feature vector: %s", itpp::to_str(features).c_str());
#endif

#if 1 // enable/disable the classifier
    Event::Type type = classifier->classify(features);
    if (type != previousEvent) {
        // FIXME sistemare!!!
        string message = "none";
        if (type != Event::NONE) {
            switch (type) {
            case Event::GUNSHOT:
                message = "GUNSHOT";
                break;
            case Event::SCREAM:
                message = "SCREAM";
                break;
            case Event::GLASS:
                message = "GLASS";
                break;
            default:
                break;
            }
            rInfo("Detected event type: %s", message.c_str());
        }
        Event e(type, message);
        // emit signal
        eventDetected(e);
        previousEvent = type;
    }
#endif
}

NS_SVMACS_END

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

#ifndef SVMACS_ENGINE_H
#define SVMACS_ENGINE_H

#include "config.h"
#include "model/event.h"
#include "exceptions/exceptions.h"

#include <itpp/base/vec.h>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <boost/scoped_ptr.hpp>

NS_SVMACS_BEGIN

class JackClient;
class Processor;
class Classifier;

/**
 * The audio engine.
 * It is a façade to the other components.
 * @see JackClient
 * @see Processor
 * @see SvmClassifier
 */
class Engine : private boost::noncopyable {
public:

    /**
     * Constructor.
     * @param length frame length (seconds)
     * @param overlap frames overlapping ratio (percentage)
     * @param dmodel path to the detection model file
     * @param cmodel path to the classification model file
     * @throw JackExeption if cannot connect to Jack.
     * @throw BadModel if cannot read the model files.
     */
    Engine(const float length, const float overlap,
            const std::string& dmodel, const std::string& cmodel);

    /// Destructor.
    ~Engine();

    /// Start processing.
    void start();

    /// Stop processing.
    void stop();

    /// Signal raised on event detection.
    boost::signals2::signal<void (Event)> eventDetected;

    /// Slot for input processing
    void processFrame(const itpp::vec& frame) const;

private:

    boost::scoped_ptr<JackClient> client;     ///< The Jack audio client.
    boost::scoped_ptr<Processor> processor;   ///< The audio frame processor.
    boost::scoped_ptr<Classifier> classifier; ///< The classifier.

    mutable Event::Type previousEvent; ///< The previously detected event.
};

NS_SVMACS_END

#endif // SVMACS_ENGINE_H

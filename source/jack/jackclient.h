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

#ifndef SVMACS_JACKCLIENT_H
#define SVMACS_JACKCLIENT_H

#include "config.h"
#include "jackringbuffer.hpp"
#include <jackaudioio.hpp>

#include <itpp/base/vec.h>
#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>

NS_SVMACS_BEGIN

class Engine;

/**
 * The Jack client.
 * This class implement a Jack client, providing the implementation
 * of the Jack callback function.
 */
class JackClient : public JackCpp::AudioIO, private boost::noncopyable {
public:

    /**
     * Constructor.
     * @param length frame length (seconds)
     * @param overlap frame overlapping ratio
     * @param engine the current engine
     */
    JackClient(const float length, const float overlap, const Engine& engine);

    /// Destructor.
    ~JackClient();

    /// Automatically connect input/output ports.
    void connect();

    /// Disconnect all input/output ports.
    void disconnect();

private:

    /**
     * Jack API audio callback.
     * All audio processing goes in this function.
     */
    int audioCallback(jack_nframes_t nframes,
            audioBufVector inBufs,
            audioBufVector outBufs);

    /// Access data in the ring buffer and process (if any).
    void checkData();

private:

    const Engine& engine; ///< The current engine.

    unsigned int length;  ///< frame length (samples)
    unsigned int overlap; ///< frame overlap (samples)

    typedef JackRingBuffer<double> RingBuffer;
    boost::scoped_ptr<RingBuffer> input; ///< The input ring buffer.

    boost::scoped_array<double> frame;   ///< The current frame.
};

NS_SVMACS_END

#endif // SVMACS_JACKCLIENT_H

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

#define BOOST_TEST_MODULE signalsTest
#include <boost/test/unit_test.hpp>

#include <boost/signals2.hpp>
#include <boost/thread.hpp>

#include <iostream>
using std::cout;
using std::endl;

namespace test {

/// Boost signal emitter.
class Emitter {
public:
    boost::signals2::signal<void ()> sig;
};

/// Boost signal receiver.
class Receiver {
public:
    Receiver() {}

    void slot() {
        cout << "signal received" << endl;
        doStuff();
    }

    void smartSlot() {
        cout << "signal received, smart" << endl;
        boost::thread service(boost::bind(&Receiver::doStuff, this));
    }

    void doStuff() {
        cout << "doing time-consuming stuff ..." << endl;
        boost::posix_time::seconds sleepTime(3);
        boost::this_thread::sleep(sleepTime);
    }
};

} /* namespace test */

BOOST_AUTO_TEST_CASE(signal2_test) {
    using namespace test;

    Emitter e;
    Receiver r;

    //e.sig.connect(boost::bind(&Receiver::slot, r));
    e.sig.connect(boost::bind(&Receiver::smartSlot, r));

    cout << "emitting signal" << endl;
    e.sig();
    cout << "emitted" << endl;
}


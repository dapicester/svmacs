#include "signalsTest.h"

#include <boost/signals2.hpp>
#include <boost/thread.hpp>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(SignalsTest);

class Emitter {
public:
    boost::signals2::signal<void ()> sig;
};

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
        sleep(3);
    }
};

void SignalsTest::doTest() {
    cout << endl;
    
    Emitter e;
    Receiver r;
    //e.sig.connect(boost::bind(&Receiver::slot, r));
    e.sig.connect(boost::bind(&Receiver::smartSlot, r));
    
    cout << "emitting signal" << endl;
    e.sig();
    cout << "emitted" << endl;
}

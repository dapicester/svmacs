#define BOOST_TEST_MODULE signalsTest
#include <boost/test/unit_test.hpp>

#include <boost/signals2.hpp>
#include <boost/thread.hpp>

using namespace std;

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
        boost::posix_time::seconds sleepTime(3);
        boost::this_thread::sleep(sleepTime);
    }
};

BOOST_AUTO_TEST_CASE(signal2_test) {
    Emitter e;
    Receiver r;
    //e.sig.connect(boost::bind(&Receiver::slot, r));
    e.sig.connect(boost::bind(&Receiver::smartSlot, r));
    
    cout << "emitting signal" << endl;
    e.sig();
    cout << "emitted" << endl;
}


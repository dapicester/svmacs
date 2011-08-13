#include "threadsTest.h"

#include <iostream>
#include <boost/thread.hpp>
#include <itpp/base/vec.h>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(ThreadsTest);

class Worker {
public:
    Worker(int i = 1) : id(i) {
        // the thread is not-a-thread until we call start()
    }

    void startUsePointer(itpp::vec* v, int N) {
        m_Thread = boost::thread(&Worker::processPointer, this, v, N);
    }
    
    void startUseReference(itpp::vec& v, int N) {
        m_Thread = boost::thread(&Worker::processReference, this, v, N);
    }

    void join() {
        m_Thread.join();
    }

private:
    void processPointer(itpp::vec* v, unsigned N) {
        float ms = N * 1e3;
        boost::posix_time::milliseconds workTime(ms);

        cout << "Worker" << id << ": started, will work for "
                << ms << "ms" << endl;

        // write something to the vec
        (*v)[id] = N;
        
        // we're busy, honest!
        boost::this_thread::sleep(workTime);

        std::cout << "Worker" << id << ": v = " << *v << std::endl;
        std::cout << "Worker" << id << ": completed" << std::endl;
    }
    
    void processReference(itpp::vec& v, unsigned N) {
        float ms = N * 1e3;
        boost::posix_time::milliseconds workTime(ms);

        cout << "Worker" << id << ": started, will work for "
                << ms << "ms" << endl;

        // write something to the vec
        v[id] = N;
        
        // we're busy, honest!
        boost::this_thread::sleep(workTime);

        std::cout << "Worker" << id << ": v = " << v << std::endl;
        std::cout << "Worker" << id << ": completed" << std::endl;
    }
    
private:
    int id;
    boost::thread m_Thread;
};

void ThreadsTest::doTest() {
    cout << endl;
    
    std::cout << "main: startup" << std::endl;

    Worker worker1(1), worker2(2), worker3(3), worker4(4);
    
    itpp::vec vector = "0 0 0 0 0 0 0 0 0 0";
    std::cout << "main: vector = " << vector << std::endl;

    worker1.startUsePointer(&vector, 3); // write 3 at index 1
    worker2.startUsePointer(&vector, 4); // write 4 at index 2
    worker3.startUsePointer(&vector, 2); // write 2 at index 3
    // XXX: must pass pointer, if using reference, nothing is written
    worker4.startUseReference(vector, 1); // write 1 at index 4;
    
    std::cout << "main: waiting for threads" << std::endl;

    worker1.join();
    worker2.join();
    worker3.join();
    worker4.join();

    // can call join() multiple times 
    worker1.join();
    
    std::cout << "main: vector = " << vector << std::endl;
    
    std::cout << "main: done" << std::endl;
    
    CPPUNIT_ASSERT(vector[1] == 3); // worker1: OK
    CPPUNIT_ASSERT(vector[2] == 4); // worker2: OK
    CPPUNIT_ASSERT(vector[3] == 2); // worker3: OK
    CPPUNIT_ASSERT(vector[4] != 1); // worker4: NO
    
    itpp::vec expected = "0 3 4 2 0 0 0 0 0 0";
    CPPUNIT_ASSERT_EQUAL(expected, vector);
}

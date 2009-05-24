/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice 
 *   dapicester@gmail.com   
 *   Code taken from the class JackCpp::RingBuffer by Alex Norman
 ***************************************************************************/

#ifndef JACK_RING_BUFFER_READ_CLASS_H
#define JACK_RING_BUFFER_READ_ CLASS_H

extern "C" {
#include <jack/ringbuffer.h>
}
#include <string.h>

namespace jack {

class RingBufferRead {
private:
    /** Poiter to the Jack Ring Buffer. */
    jack_ringbuffer_t *mRingBufferPtr;
    size_t mLength;
    
    /// Size
    //static const int float_size = sizeof(float);
    static const int double_size = sizeof(double);
    
public:
    /** Constructor */
    RingBufferRead(size_t size, bool mlock = false);
    
    /** Destructor */
    ~RingBufferRead();
    
    /** Get the total length of the ring buffer. */
    size_t length();
    
    /** Get the number of items that can be read at this time */
    size_t getReadSpace();
    
    /** Get the number of items that can be written at this time. */
    size_t getWriteSpace();
    
    /** Read from the buffer into a variable. */
    int read(double &dest);	
    	
    /** Read from the buffer into a variable without moving the read pointer. */
    int peek(double &dest);
    
    /** Read from the buffer into an array. */
    int read(double dest[], unsigned cnt, bool peek = false);
			
    /** Read from the buffer into an array without move the read pointer. */
    int peek(double dest[], unsigned cnt);
			
    /** Write into the ring buffer. */
    int write(double src);
    
    /** Write an array of values into the ring buffer. */
    int write(double src[], unsigned int cnt);

    /** Reset the read and write pointers, effectively making the ring buffer empty (not threadsafe) */
    void reset();

};

}

#endif

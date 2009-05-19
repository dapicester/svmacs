/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice 
 *   dapicester@gmail.com   
 *   Code taken from the class JackCpp::RingBuffer by Alex Norman
 ***************************************************************************/

#ifndef JACK_RING_BUFFER_READ_CLASS_H
#define JACK_RING_BUFFER_READ_ CLASS_H

#ifndef NULL
#define NULL 0
#endif

extern "C" {
#include <jack/ringbuffer.h>
}
#include <string.h>

template<class Type>

/** 
@class RingBufferRead

@brief This template class wraps the Jack lock-free ringbuffer.

This class creates a lock-free ring buffer that accepts a specific data type.

The key attribute of a ringbuffer is that it can be safely accessed by two
threads simultaneously -- one reading from the buffer and the other writing to
it -- without using any synchronization or mutual exclusion primitives. For
this to work correctly, there can only be a single reader and a single writer
thread. Their identities cannot be interchanged.

@author Alex Norman
*/
class RingBufferRead {
private:
    jack_ringbuffer_t *mRingBufferPtr;
    size_t mLength;
public:
    /**
     @brief The Constructor
     \param size the number of items that the ring buffer should be able to hold
                 it will be rounded to the closest power of two 
     \param mlock a boolean indicating whether or not the ring buffer should be locked in memory
     */
    RingBufferRead(size_t size, bool mlock = false);
    
    ///The Destructor
    ~RingBufferRead();
    
    ///Get the total length of the ring buffer
    size_t length();
    
    ///Get the number of items that can be read at this time
    size_t getReadSpace();
    
    ///Get the number of items that can be written at this time
    size_t getWriteSpace();
    
    /**
     @brief Read into dest

     Read from the buffer into a variable.

     \param dest an item to be read into
     */
    int read(Type &dest);
    	
    /**
     @brief Read into dest
     Read from the buffer into a variable without moving the read poiter.

     \param dest an item to be read into
     */
    int peek(Type &dest);
    
    /**
     @brief Read into an array

     Read from the buffer into an array.

     \param dest an array to be read into
     \param cnt the number of elements to read into this array
     \param peek 
     */
    int read(Type *dest, unsigned cnt, bool peek = false);
			
    /**
     @brief Read into an array

     Read from the buffer into an array without move the read pointer.

     \param dest an array to be read into
     \param cnt the number of elements to read into this array
     */
    int peek(Type *dest, unsigned cnt);
			
    /**
     @brief Write into the ring buffer.

     \param src the value to write
     */
    int write(Type src);
    
    /**
     @brief Write an array of values into the ring buffer.

     \param src an array of values to write
     \param cnt the number of items from the array to write into our buffer
     */
    int write(Type *src, unsigned int cnt);

    /**
     @brief Reset

     This is not threadsafe.  This resets the read and write pointers,
     effectively making the ring buffer empty.
     */
    void reset();

};

template<class Type>
RingBufferRead<Type>::RingBufferRead(size_t size, bool mlock){
    mLength = size;
    mRingBufferPtr = jack_ringbuffer_create(mLength * sizeof(Type));

    //should we lock the memory for the ring buffer?
    if(mlock)
        jack_ringbuffer_mlock(mRingBufferPtr);
}

template<class Type>
RingBufferRead<Type>::~RingBufferRead(){
    if(mRingBufferPtr != NULL)
        jack_ringbuffer_free(mRingBufferPtr);
}

template<class Type>
size_t RingBufferRead<Type>::length(){
    return mLength;
}

template<class Type>
size_t RingBufferRead<Type>::getReadSpace(){ 
    return jack_ringbuffer_read_space(mRingBufferPtr) / sizeof(Type);
}

template<class Type>
size_t RingBufferRead<Type>::getWriteSpace(){
    return jack_ringbuffer_write_space(mRingBufferPtr) / sizeof(Type);
}

template<class Type>
int RingBufferRead<Type>::read(Type &dest){
    if(getReadSpace() <= 0){
        //throw error!!!!
        return 1;
    }
    jack_ringbuffer_read(mRingBufferPtr, (char *)&dest, sizeof(Type));
    return 0;
}

template<class Type>
int RingBufferRead<Type>::peek(Type &dest){
    if(getReadSpace() <= 0){
        //throw error!!!!
        return 1;
    }
    jack_ringbuffer_peek(mRingBufferPtr, (char *)&dest, sizeof(Type));
    return 0;
}

template<class Type>
int RingBufferRead<Type>::read(Type *dest, unsigned cnt, bool peek){
    jack_ringbuffer_data_t readVec[2];
    unsigned int read_size = sizeof(Type) * cnt;
    if(getReadSpace() <= 0){
        //throw error!!!!
        return 1;
    }

    //get the readvector
    jack_ringbuffer_get_read_vector(mRingBufferPtr, readVec);

    //if the first vector has enough data then just read from there
    if(readVec[0].len >= read_size){
        memcpy(dest, readVec[0].buf, read_size);
    } else {
        //if the first vector is zero length then read from the second
        if(readVec[0].len == 0){
            memcpy(dest, readVec[1].buf, read_size);
        } else {
            //this gets tricky
            char * byterep = (char *)dest;
            //first read the data out of the first vector
            memcpy(byterep, readVec[0].buf, readVec[0].len);
            //then read the rest out of the second
            memcpy(byterep + readVec[0].len, readVec[1].buf, read_size - readVec[0].len);
        }
    }
    
    //advance the read pointer
    if (!peek)
        jack_ringbuffer_read_advance(mRingBufferPtr, read_size);
    
    return 0;
}

template<class Type>
int RingBufferRead<Type>::peek(Type *dest, unsigned cnt){
    return read(dest, cnt, true);
}

template<class Type>
int RingBufferRead<Type>::write(Type src){
    if(getWriteSpace() <= 0){
        //throw error!!!!
        return 1;
    }
    jack_ringbuffer_write(mRingBufferPtr, (char *)&src, sizeof(Type));
    return 0;
}

template<class Type>
int RingBufferRead<Type>::write(Type *src, unsigned int cnt){
    jack_ringbuffer_data_t writeVec[2];
    unsigned int write_size = sizeof(Type) * cnt;
    if(cnt > getWriteSpace()){
        //throw error!!!!
        return 1;
    }

    //get the write vector
    jack_ringbuffer_get_write_vector(mRingBufferPtr, writeVec);
    //if there is enough room in the first vector then just write there
    if(writeVec[0].len >= write_size){
        memcpy(writeVec[0].buf,src,write_size);
    } else {
        //if there is no room in the first vector then write into the second
        if(writeVec[0].len == 0){
            memcpy(writeVec[1].buf,src,write_size);
        } else {
            //this is more tricky, we have to split the data up
            char * byterep = (char *)src;
            //copy the first chunck
            memcpy(writeVec[0].buf, byterep, writeVec[0].len);
            //copy the second chunck
            memcpy(writeVec[1].buf, byterep + writeVec[0].len, write_size - writeVec[0].len);
        }
    }
    jack_ringbuffer_write_advance(mRingBufferPtr, write_size);
    return 0;
}

template<class Type>
void RingBufferRead<Type>::reset(){
    jack_ringbuffer_reset(mRingBufferPtr);
}


#endif

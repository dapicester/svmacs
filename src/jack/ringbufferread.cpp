/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include <jack/ringbufferread.h>
using namespace jack;

#define RLOG_COMPONENT "ringbufferread"
#include <rlog/rlog.h>

#ifndef NULL
#define NULL 0
#endif

RingBufferRead::RingBufferRead(size_t size, bool mlock){
    mLength = size;
    mRingBufferPtr = jack_ringbuffer_create(mLength * double_size);

    //should we lock the memory for the ring buffer?
    if(mlock)
        jack_ringbuffer_mlock(mRingBufferPtr);
}

RingBufferRead::~RingBufferRead(){
    if(mRingBufferPtr != NULL)
        jack_ringbuffer_free(mRingBufferPtr);
}

size_t RingBufferRead::length(){
    return mLength;
}

size_t RingBufferRead::getReadSpace(){ 
    return jack_ringbuffer_read_space(mRingBufferPtr) / double_size;
}

size_t RingBufferRead::getWriteSpace(){
    return jack_ringbuffer_write_space(mRingBufferPtr) / double_size;
}

int RingBufferRead::read(double &dest){
    if(getReadSpace() <= 0){
        //throw error!!!!
        return 1;
    }
    jack_ringbuffer_read(mRingBufferPtr, (char *)&dest, double_size);
    return 0;
}

int RingBufferRead::peek(double &dest){
    if(getReadSpace() <= 0){
        //throw error!!!!
        return 1;
    }
    jack_ringbuffer_peek(mRingBufferPtr, (char *)&dest, double_size);
    return 0;
}

int RingBufferRead::read(double* dest, unsigned cnt, bool peek){
    jack_ringbuffer_data_t readVec[2];
    unsigned int read_size = double_size * cnt;
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

int RingBufferRead::peek(double *dest, unsigned cnt){
    return read(dest, cnt, true);
}

int RingBufferRead::write(double src){
    if(getWriteSpace() <= 0){
        //throw error!!!!
        return 1;
    }
    jack_ringbuffer_write(mRingBufferPtr, (char *)&src, double_size);
    return 0;
}

int RingBufferRead::write(double* src, unsigned int cnt){
    jack_ringbuffer_data_t writeVec[2];
    unsigned int write_size = double_size * cnt;
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

void RingBufferRead::reset(){
    jack_ringbuffer_reset(mRingBufferPtr);
}

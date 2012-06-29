/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice
 *   dapicester@gmail.com
 *   Code taken from the class JackCpp::JackRingBuffer by Alex Norman
 ***************************************************************************/

#ifndef SVMACS_JACKRINGBUFFER_H
#define SVMACS_JACKRINGBUFFER_H

#include "config.h"

extern "C" {
#include <jack/ringbuffer.h>
}

#include <boost/noncopyable.hpp>
#include <string.h>

NS_SVMACS_BEGIN

/**
 * Ring Buffer.
 * Class wrapping the JACK lock-free ring buffer.
 */
template <typename Type>
class JackRingBuffer : private boost::noncopyable {
public:

    /**
     * Constructor.
     * @param size the actual buffer size
     * @param mlock memory lock
     */
    JackRingBuffer(size_t size, bool mlock = false);

    /// Destructor.
    ~JackRingBuffer();

    /// Get the total length of the ring buffer.
    size_t length() const {
        return mLength;
    };

    /// Get the number of items that can be read at this time.
    size_t getReadSpace();

    /// Get the number of items that can be written at this time.
    size_t getWriteSpace();

    /// Read from the buffer into a variable.
    size_t read(Type& dest);

    /// Read from the buffer into a variable without moving the read pointer.
    size_t peek(Type& dest);

    /// Read from the buffer into an array, optionally moving the read pointer.
    size_t read(Type dest[], size_t cnt, bool peek = false);

    /// Read from the buffer into an array without move the read pointer.
    size_t peek(Type dest[], size_t cnt);

    /// Write into the ring buffer.
    size_t write(Type src);

    /// Write an array of values into the ring buffer.
    size_t write(Type src[], size_t cnt);

    /// Reset the read and write pointers, effectively making the ring buffer empty (not threadsafe).
    void reset();

private:

    /// Pointer to the Jack Ring Buffer.
    jack_ringbuffer_t* mJackRingBufferPtr;

    /// Size of the Jack buffer.
    size_t mLength;
};


template <typename Type>
JackRingBuffer<Type>::JackRingBuffer(size_t size, bool mlock)
        : mLength(size) {
    mJackRingBufferPtr = jack_ringbuffer_create(mLength * sizeof(Type));

    // should we lock the memory for the ring buffer?
    if (mlock) {
        jack_ringbuffer_mlock(mJackRingBufferPtr);
    }
}

template <typename Type>
JackRingBuffer<Type>::~JackRingBuffer() {
    if (mJackRingBufferPtr != NULL) {
        jack_ringbuffer_free(mJackRingBufferPtr);
    }
}

template <typename Type>
inline size_t JackRingBuffer<Type>::getReadSpace() {
    return jack_ringbuffer_read_space(mJackRingBufferPtr) / sizeof(Type);
}

template <typename Type>
inline size_t JackRingBuffer<Type>::getWriteSpace() {
    return jack_ringbuffer_write_space(mJackRingBufferPtr) / sizeof(Type);
}

template <typename Type>
size_t JackRingBuffer<Type>::read(Type& dest) {
    if (getReadSpace() <= 0) {
        // throw?
        return 0;
    }
    return jack_ringbuffer_read(mJackRingBufferPtr, reinterpret_cast<char*>(&dest), sizeof(Type));
}

template <typename Type>
size_t JackRingBuffer<Type>::peek(Type &dest) {
    if (getReadSpace() <= 0) {
        // throw?
        return 0;
    }
    return jack_ringbuffer_peek(mJackRingBufferPtr, reinterpret_cast<char*>(&dest), sizeof(Type));
}

template <typename Type>
size_t JackRingBuffer<Type>::read(Type* dest, size_t cnt, bool peek) {
    jack_ringbuffer_data_t readVec[2];
    size_t read_size = sizeof(Type) * cnt;
    if (getReadSpace() <= 0) {
        // throw?
        return 0;
    }

    // get the readvector
    jack_ringbuffer_get_read_vector(mJackRingBufferPtr, readVec);

    // if the first vector has enough data then just read from there
    if (readVec[0].len >= read_size) {
        memcpy(dest, readVec[0].buf, read_size);
    } else {
        // if the first vector is zero length then read from the second
        if (readVec[0].len == 0) {
            memcpy(dest, readVec[1].buf, read_size);
        } else {
            // this gets tricky
            char* byterep = reinterpret_cast<char*>(dest);
            // first read the data out of the first vector
            memcpy(byterep, readVec[0].buf, readVec[0].len);
            // then read the rest out of the second
            memcpy(byterep + readVec[0].len, readVec[1].buf, read_size - readVec[0].len);
        }
    }

    if (!peek) {
        // advance the read pointer
        jack_ringbuffer_read_advance(mJackRingBufferPtr, read_size);
    }

    return read_size;
}

template <typename Type>
inline size_t JackRingBuffer<Type>::peek(Type *dest, size_t cnt) {
    return read(dest, cnt, true);
}

template <typename Type>
size_t JackRingBuffer<Type>::write(Type src) {
    if (getWriteSpace() <= 0) {
        // throw?
        return 0;
    }
    return jack_ringbuffer_write(mJackRingBufferPtr, (char*) &src, sizeof(Type));
}

template <typename Type>
size_t JackRingBuffer<Type>::write(Type* src, size_t cnt) {
    jack_ringbuffer_data_t writeVec[2];
    size_t write_size = sizeof(Type) * cnt;
    if (cnt > getWriteSpace()) {
        // throw?
        return 0;
    }

    // get the write vector
    jack_ringbuffer_get_write_vector(mJackRingBufferPtr, writeVec);
    // if there is enough room in the first vector then just write there
    if (writeVec[0].len >= write_size) {
        memcpy(writeVec[0].buf, src, write_size);
    } else {
        // if there is no room in the first vector then write into the second
        if (writeVec[0].len == 0) {
            memcpy(writeVec[1].buf, src, write_size);
        } else {
            // this is more tricky, we have to split the data up
            char* byterep = reinterpret_cast<char*>(src);
            // copy the first chunck
            memcpy(writeVec[0].buf, byterep, writeVec[0].len);
            // copy the second chunck
            memcpy(writeVec[1].buf, byterep + writeVec[0].len, write_size - writeVec[0].len);
        }
    }
    jack_ringbuffer_write_advance(mJackRingBufferPtr, write_size);
    return write_size;
}

template <typename Type>
inline void JackRingBuffer<Type>::reset() {
    jack_ringbuffer_reset(mJackRingBufferPtr);
}

NS_SVMACS_END

#endif // SVMACS_JACKRINGBUFFER_H

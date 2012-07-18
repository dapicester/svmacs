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

#define BOOST_TEST_MODULE JackRingBufferTest
#include <boost/test/unit_test.hpp>

#include "jack/jackringbuffer.hpp"
using svmacs::JackRingBuffer;

#define P(X) std::cout << #X << X << std::endl;

/// @class svmacs::JackRingBuffer
/// @test Tests read and write operations.
BOOST_AUTO_TEST_CASE(buffer_test) {
    // test data
    double array[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.0};
    const size_t arraySize = 10;

    const size_t bufferSize = 2 * arraySize + 1;
    JackRingBuffer<double> buffer(bufferSize);

    BOOST_CHECK_EQUAL(bufferSize, buffer.length());
    BOOST_CHECK(buffer.getWriteSpace() >= buffer.length());
    BOOST_CHECK_EQUAL(0, buffer.getReadSpace());

    // write
    buffer.write(array, arraySize); // FIXME: cannot use const double*
    BOOST_CHECK(buffer.getWriteSpace() >= (buffer.length() - arraySize));
    BOOST_CHECK_EQUAL(arraySize, buffer.getReadSpace());

    // read
    size_t readSize = buffer.getReadSpace();
    for (int i = 0 ; buffer.getReadSpace() != 0; i++){
        BOOST_CHECK_EQUAL(readSize - i, buffer.getReadSpace());

        double peekValue;
        buffer.peek(peekValue);
        BOOST_CHECK_EQUAL(array[i], peekValue);
        BOOST_CHECK_EQUAL(readSize - i, buffer.getReadSpace());

        double readValue;
        buffer.read(readValue);
        BOOST_CHECK_EQUAL(array[i], readValue);
        BOOST_CHECK_EQUAL(readSize - i - 1, buffer.getReadSpace());
    }
    BOOST_CHECK_EQUAL(0, buffer.getReadSpace());
}

/// @class svmacs::JackRingBuffer
/// @test Tests the read and peek operations.
BOOST_AUTO_TEST_CASE(peek_test) {
    const int length = 4;
    const int overlap = 2;

    double data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int data_len = 10;

    JackRingBuffer<double> buffer(2 * length + 1);
    buffer.write(data, data_len); // FIXME: cannot use const double*

    const double expected[][4] = {
        { 0, 1, 2, 3 },
        { 2, 3, 4, 5 },
        { 4, 5, 6, 7 },
        { 6, 7, 8, 9 }
    };

    double frame[length];
    for (int i = 0; buffer.getReadSpace() >= length; i++) {
        buffer.read(frame, length - overlap);
        buffer.peek(frame + overlap, overlap);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected[i], expected[i] + length, frame, frame + length);
    }
}


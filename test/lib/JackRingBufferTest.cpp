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

#include <jackringbuffer.hpp>

/// @class JackCpp::RingBuffer
/// @test Ring buffer usage.
BOOST_AUTO_TEST_CASE(jackringbuffer) {
    const size_t SIZE = 20;
    JackCpp::RingBuffer<int> buffer(SIZE);
    BOOST_CHECK_EQUAL(SIZE, buffer.length());
    BOOST_CHECK( buffer.getWriteSpace() >= buffer.length());
    BOOST_CHECK_EQUAL(0, buffer.getReadSpace());

    // test data
    const size_t N = 10;
    int array[N];
    for (int i = 1; i <= N; i++) array[i] = i;

    // write
    buffer.write(array, N);
    BOOST_CHECK( buffer.getWriteSpace() >= (buffer.length() - N));
    BOOST_CHECK_EQUAL(N, (int) buffer.getReadSpace());

    // read
    int readSize = buffer.getReadSpace();
    for (int i = 0 ; buffer.getReadSpace() != 0; i++){
        BOOST_CHECK_EQUAL(readSize - i, (int) buffer.getReadSpace());

        int readValue;
        buffer.read(readValue);

        BOOST_CHECK_EQUAL(array[i], readValue);
        BOOST_CHECK_EQUAL(readSize - i - 1, (int) buffer.getReadSpace());
    }
    BOOST_CHECK_EQUAL(0, (int) buffer.getReadSpace());
}

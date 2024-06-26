#include <gtest/gtest.h>
#include "FFIFO.h"

TEST( testingFIFO, allAreZeroes) {
    FFIFO<int,4> fifo;
    ASSERT_EQ(fifo[0], 0);
    ASSERT_EQ(fifo[1], 0);
    ASSERT_EQ(fifo[2], 0);
    ASSERT_EQ(fifo[3], 0);
}

TEST( testingFIFO, pushBack) {
    FFIFO<int,4> fifo;
    fifo.push_back(1);
    fifo.push_back(99);
    ASSERT_EQ(fifo[0], 0);
    ASSERT_EQ(fifo[1], 0);
    ASSERT_EQ(fifo[2], 1);
    ASSERT_EQ(fifo[3], 99);
}


TEST( testingFIFO, pushBackFull) {
    FFIFO<int,4> fifo;
    fifo.push_back(1);
    fifo.push_back(2);
    fifo.push_back(3);
    fifo.push_back(4);
    ASSERT_EQ(fifo[0], 1);
    ASSERT_EQ(fifo[1], 2);
    ASSERT_EQ(fifo[2], 3);
    ASSERT_EQ(fifo[3], 4);
}

TEST( testingFIFO, pushBackOverFlow) {
    FFIFO<int,4> fifo;
    fifo.push_back(1);
    fifo.push_back(2);
    fifo.push_back(3);
    fifo.push_back(4);
    fifo.push_back(5);
    ASSERT_EQ(fifo[0], 2);
    ASSERT_EQ(fifo[1], 3);
    ASSERT_EQ(fifo[2], 4);
    ASSERT_EQ(fifo[3], 5);
    ASSERT_EQ(fifo.capacity(),4); // check that size was kept constant
    std::cout<< "Fifo size is: "<<fifo.capacity() <<std::endl;
}
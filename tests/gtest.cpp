#include <gtest/gtest.h>
extern "C" {
    #include "ringbuffer.h"
}

int testSize = 10;

TEST (RingBufferTest, InitTest) {
    ringbuffer_init(testSize);
    EXPECT_TRUE(ringbuffer_isempty());
    EXPECT_FALSE(ringbuffer_isfull());
}

TEST (RingBufferTest, AddTest) {
    for (int i = 0; i < testSize; i++) {
        EXPECT_EQ(ringbuffer_add(i), 0);
    }
    EXPECT_EQ(ringbuffer_size(), testSize);
    EXPECT_TRUE(ringbuffer_isfull());
    
    EXPECT_EQ(ringbuffer_add(100), -1);
}

TEST (RingBufferTest, RemoveTest) {
    for (int i = 0; i < testSize; i++) {
        ringbuffer_add(i);
    }
    int value = 0;
    for (int i = 0; i < testSize; i++) {
        EXPECT_EQ(ringbuffer_remove(&value), 0);
        EXPECT_EQ(value, i);
    }
    EXPECT_EQ(ringbuffer_size(), 0);
    EXPECT_TRUE(ringbuffer_isempty());
    
    EXPECT_EQ(ringbuffer_remove(&value), -1);
}

TEST (RingBufferTest, RingTest) {
    for (int i = 0; i < testSize; i++) {
        EXPECT_EQ(ringbuffer_add(i), 0);
    }
    int value = 0;
    for (int i = 0; i < testSize/2; i++) {
        EXPECT_EQ(ringbuffer_remove(&value), 0);
        EXPECT_EQ(value, i);
    }
    
    for (int i = testSize; i < testSize + testSize/2; i++) {
        EXPECT_EQ(ringbuffer_add(i), 0);
    }
    
    for (int i = testSize/2; i < testSize; i++) {
        EXPECT_EQ(ringbuffer_remove(&value), 0);
        EXPECT_EQ(value, i);
    }
    for (int i = testSize; i < testSize + testSize/2; i++) {
        EXPECT_EQ(ringbuffer_remove(&value), 0);
        EXPECT_EQ(value, i);
    }
    EXPECT_TRUE(ringbuffer_isempty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
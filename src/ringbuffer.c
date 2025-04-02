#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ringbuffer.h"

#define MAX_BUFFER 256

typedef struct {
    int buffer[MAX_BUFFER];
    unsigned short size;
    unsigned short head;
    unsigned short tail;
    unsigned short count;
} RingBuffer;

static RingBuffer rb;

void ringbuffer_init(unsigned short size) {
    if(size >= MAX_BUFFER) {
        return;
    }
    rb.size = size;
    memset(rb.buffer, 0, sizeof(int) * size);
    rb.head = 0;
    rb.tail = 0;
    rb.count = 0;
}

int ringbuffer_isfull() {
    return rb.count == rb.size;
}

int ringbuffer_isempty() {
    return rb.count == 0;
}

int ringbuffer_add(int value) {
    if (ringbuffer_isfull()) {
        return -1; 
    }
    rb.count++;
    rb.tail = (rb.head + rb.count - 1) % (rb.size -1);
    rb.buffer[rb.tail] = value;
    return 0;
}

int ringbuffer_remove(int *value) {
    if (ringbuffer_isempty()) {
        return -1;
    }
    rb.count--;
    *value = rb.buffer[rb.head];
    rb.head = (rb.head + 1) % (rb.size - 1);
    return 0;
}

int ringbuffer_size() {
    return rb.count;
}
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
    rb.buffer[rb.head] = value;
    rb.head = (rb.head + 1) % rb.size;
    rb.count++;
    return 0;
}

int ringbuffer_remove(int *value) {
    if (ringbuffer_isempty()) {
        return -1;
    }
    *value = rb.buffer[rb.tail];
    rb.tail = (rb.tail + 1) % rb.size;
    rb.count--;
    return 0;
}

int ringbuffer_size() {
    return rb.count;
}
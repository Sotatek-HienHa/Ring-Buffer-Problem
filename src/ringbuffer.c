#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "ringbuffer.h"

#define MAX_BUFFER 256

typedef struct {
    int buffer[MAX_BUFFER];
    unsigned short size;
    unsigned short head;
    unsigned short tail;
    unsigned short count;
    pthread_mutex_t lock;
} RingBuffer;

static RingBuffer rb;

void ringbuffer_init(unsigned short size) {
    rb.size = size;
    memset(rb.buffer, 0, sizeof(int) * size);
    rb.head = 0;
    rb.tail = 0;
    rb.count = 0;
    pthread_mutex_init(&rb.lock, NULL);
}

int ringbuffer_isfull() {
    return rb.count == rb.size;
}

int ringbuffer_isempty() {
    return rb.count == 0;
}

int ringbuffer_add(int value) {
    pthread_mutex_lock(&rb.lock);
    if (ringbuffer_isfull()) {
        pthread_mutex_unlock(&rb.lock);
        return -1; 
    }
    rb.buffer[rb.head] = value;
    rb.head = (rb.head + 1) % rb.size;
    rb.count++;
    pthread_mutex_unlock(&rb.lock);
    return 0;
}

int ringbuffer_remove(int *value) {
    pthread_mutex_lock(&rb.lock);
    if (ringbuffer_isempty()) {
        pthread_mutex_unlock(&rb.lock);
        return -1;
    }
    *value = rb.buffer[rb.tail];
    rb.tail = (rb.tail + 1) % rb.size;
    rb.count--;
    pthread_mutex_unlock(&rb.lock);
    return 0;
}

int ringbuffer_size() {
    pthread_mutex_lock(&rb.lock);
    int res = rb.count;
    pthread_mutex_ulock(&rb.lock);
    return res;
}
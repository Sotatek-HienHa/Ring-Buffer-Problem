#ifndef RINGBUFFER_H
#define RINGBUFFER_H

void ringbuffer_init(unsigned short size);
int ringbuffer_isfull();
int ringbuffer_isempty();
int ringbuffer_add(int value);
int ringbuffer_remove(int *value);
int ringbuffer_size();

#endif
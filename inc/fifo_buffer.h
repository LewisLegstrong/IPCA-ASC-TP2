#ifndef _FIFO_BUFFER_H_
#define _FIFO_BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE     15

typedef struct {
    float buffer[MAX_BUFFER_SIZE];
    int start;
    int end;
    int size;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int process_joined;
    int flag;
} fifo_buffer_t;

void add_to_buffer_tail ( fifo_buffer_t *buffer, float sensor_data );
void read_buffer ( fifo_buffer_t *buffer );

#endif // _FIFO_BUFFER_H_
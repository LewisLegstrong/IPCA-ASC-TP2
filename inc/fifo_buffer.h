#ifndef _FIFO_BUFFER_H_
#define _FIFO_BUFFER_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct fifo_s{
    float sensor_data;
    struct fifo_s *next;
} fifo_buffer_t;

void add_to_buffer_tail ( float *buffer, float sensor_data );
void free_list( float *buffer );
void remove_from_buffer_head ( float *buffer );

void read_buffer( float *buffer );
int get_list_size( float *buffer );

#endif // _FIFO_BUFFER_H_
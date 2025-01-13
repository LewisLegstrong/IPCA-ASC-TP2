#include "fifo_buffer.h"

void add_to_buffer_tail ( fifo_buffer_t *fifo, float sensor_data ) {
    pthread_mutex_lock(&fifo->mutex);

    if (fifo->size < MAX_BUFFER_SIZE) {
        fifo->buffer[fifo->end] = sensor_data;
        fifo->end = (fifo->end + 1) % MAX_BUFFER_SIZE;
        fifo->size++;
    } else {
        // Shift all elements one position forward
        for (int i = 1; i < MAX_BUFFER_SIZE; i++) {
            fifo->buffer[i - 1] = fifo->buffer[i];
        }
        // Add new element at the end
        fifo->buffer[MAX_BUFFER_SIZE - 1] = sensor_data;
    }

    read_buffer(fifo);
    fifo->flag = 1; // Indicate new data is ready
    pthread_cond_signal(&fifo->cond);
    pthread_mutex_unlock(&fifo->mutex);
}

void read_buffer ( fifo_buffer_t *fifo ) {
    for ( int i = 0; i < fifo->size; i++ ) {
        printf("Buffer[%d]: %.2f\n", i, fifo->buffer[i]);
    }
}


#include "sensor_thread.h"
#define DEBUG

/* ********************************* */
/*  ******  THREAD FUNCTIONS  ****** */
/* ********************************* */
void *read_sensor_data ( void *arg ) {
    sensor_info_t *sensor_info = (sensor_info_t *) arg;
    int reads = 0;

    for ( int i = 0; i < sensor_info->sensor_reads; i++ ) {
        int data_for_buffer = rand() % 101;
        add_to_buffer_tail( sensor_info->buffer, data_for_buffer );
        reads++;
        #ifdef DEBUG
            printf("*****       Added to Sensor %d: %d \n", sensor_info->sensor_name, data_for_buffer);
            read_buffer( sensor_info->buffer );
        #endif
        delay_seconds( sensor_info->sensor_timing );
    }

    printf("Sensor %d reads: %d\n", sensor_info->sensor_name, reads);
    pthread_exit(NULL);
}

void *read_buffer_data ( void *arg ) {
    int sum = 0;
    float average = 0.0;

    fifo_buffer_t *fifo = (fifo_buffer_t *) arg;
    
    while ( 1 ) {
        pthread_mutex_lock(&fifo->mutex);

        while ( fifo->size == 0 && !fifo->terminar ) {
            pthread_cond_wait(&fifo->cond, &fifo->mutex);
        }

        if ( fifo->size == 0 && fifo->terminar ) {
            pthread_mutex_unlock(&fifo->mutex);
            break;
        }

        sum = 0;
        average = 0.0;
        int reads = fifo->size < AVERAGE_MAX_READS ? fifo->size : AVERAGE_MAX_READS;
        for(int i = 0; i < reads; i++) {
            sum += fifo->buffer[fifo->end - i];
        }
        average = sum / reads;
        printf(" ** Average: %.2f\n\n", average);

        pthread_mutex_unlock(&fifo->mutex);

        if ( fifo->terminar ) {
            break;
        }
        pthread_cond_wait(&fifo->cond, &fifo->mutex);
    }
    pthread_exit(NULL);
}

/* ********************************* */
/*  ****  NON-THREAD FUNCTIONS  **** */
/* ********************************* */

void delay_seconds(int seconds) {
    struct timespec ts;
    ts.tv_sec = seconds;              // Segundos
    ts.tv_nsec = 0;                   // Nanosegundos
    nanosleep(&ts, NULL);             // Executa o atraso
}
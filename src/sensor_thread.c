#include "sensor_thread.h"
#define DEBUG

/* ********************************* */
/*  ******  THREAD FUNCTIONS  ****** */
/* ********************************* */
void *read_sensor_data ( void *arg ) {
    sensor_info_t *sensor_info = (sensor_info_t *) arg;
    int reads = 0;

    while ( reads < sensor_info->sensor_reads ) {
        write_to_buffer( sensor_info->buffer, rand() );
        reads++;
        #ifdef DEBUG
            printf(" Sensor reads: %d\n", reads);
            printf("** Buffer Size %d \n", get_list_size( sensor_info->buffer ) ); 
            read_buffer( sensor_info->buffer );       
        #endif
        
        delay_seconds( sensor_info->sensor_timing );
    }
    pthread_exit(NULL);
}

void *read_buffer_data ( void *arg ) {
   
}

/* ********************************* */
/*  ****  NON-THREAD FUNCTIONS  **** */
/* ********************************* */
void write_to_buffer ( float *buffer, float sensor_data ) {
    if ( MAX_BUFFER_SIZE == get_list_size( buffer ) ) {          // If buffer is not full
        printf("Buffer is full\n");
        remove_from_buffer_head( buffer );       // Remove the oldest entry
    }
    add_to_buffer_tail( buffer, sensor_data );          // Add sensor data to the buffer
}

void delay_seconds(int seconds) {
    struct timespec ts;
    ts.tv_sec = seconds;              // Segundos
    ts.tv_nsec = 0;                   // Nanosegundos
    nanosleep(&ts, NULL);             // Executa o atraso
}
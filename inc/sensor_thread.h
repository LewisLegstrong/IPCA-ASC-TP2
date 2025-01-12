#ifndef _SENSOR_THREAD_H
#define _SENSOR_THREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "fifo_buffer.h"

#define MAX_BUFFER_SIZE     15

#define MAX_TEMP_SENSOR1_READS 25
#define MAX_TEMP_SENSOR2_READS 30
#define TEMP_SENSOR1_TIMING 3
#define TEMP_SENSOR2_TIMING 5

#define MAX_HUMID_SENSOR1_READS 15
#define MAX_HUMID_SENSOR2_READS 25
#define HUMID_SENSORS_TIMING 8

typedef struct {
    int sensor_reads;
    int sensor_timing;
    float *buffer;
} sensor_info_t;

/// @brief Sensor functions to be included in threads
/// @param arg 
/// @return 
void *read_sensor_data ( void *arg );
void *read_buffer_data ( void *arg );

/// @brief Auxiliary funcitons to the thread functions

/// @brief 
/// @param seconds 
void delay_seconds( int seconds );

/// @brief 
/// @param head 
/// @param sensor_data 
void write_to_buffer ( float *buffer, float sensor_data  );

#endif // _SENSOR_THREAD_H
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

#include "fifo_buffer.h"
#include "sensor_thread.h"

#define MAX_THREAD_COUNT    3
#define DEBUG



int main(int argc, char *argv[]) {
	pthread_t temp_threads[MAX_THREAD_COUNT];
	pthread_t humid_threads[MAX_THREAD_COUNT];

	int temp_process;                                  // Identificador do processo filho
	int humidity_process;
	temp_process = fork();                             // Replicação do processo
	float temp_average = 0;
	float humid_average = 0;

	if( temp_process < 0 ) {                             // Se o fork() retornou erro
		perror("Error: ");
		return -1;
	}
	else if( temp_process > 0 ) {                        // Se é o processo pai
		humidity_process = fork();                       // Replicação do processo
		if( humidity_process < 0 ) {                     // Se o fork() retornou erro
			perror("Error: ");
			return -1;
		}
		else if( humidity_process > 0 ) {                // Se é o processo pai
			wait(0);                                	 // Aguarda até que o filho conclua a sua execução
		}
		else {                                  		// Se é o processo filho 2 [HUMIDADE]
			fifo_buffer_t humid_fifo ={
				.average = &humid_average,
				.start = 0,
				.end = 0,
				.size = 0,
				.mutex = PTHREAD_MUTEX_INITIALIZER,
				.cond = PTHREAD_COND_INITIALIZER,
				.process_joined = 0,
				.flag = 0
			};

			sensor_info_t sensor_count ={
				.sensor_name = 21,
				.sensor_reads = MAX_HUMID_SENSOR1_READS,
				.sensor_timing = HUMID_SENSORS_TIMING,
				.buffer = &humid_fifo
			};

			sensor_info_t sensor_count2 ={
				.sensor_name = 22,
				.sensor_reads = MAX_HUMID_SENSOR2_READS,
				.sensor_timing = HUMID_SENSORS_TIMING,
				.buffer = &humid_fifo
			};

	
			pthread_create(&humid_threads[1], NULL, read_sensor_data, (void *) &sensor_count);
			pthread_create(&humid_threads[2], NULL, read_sensor_data, (void *) &sensor_count2);
			pthread_create(&humid_threads[3], NULL, read_buffer_data, (void *) &humid_fifo);

			pthread_join( humid_threads[1], NULL );
			pthread_join( humid_threads[2], NULL );
			humid_fifo.process_joined = 1;
			pthread_cond_broadcast(&humid_fifo.cond);
			pthread_join( humid_threads[3], NULL );
		}
		wait(0);
		
	} else {                                        		// Se é o processo filho [TEMPERATURA]   
		fifo_buffer_t temp_fifo ={
			.average = &temp_average,
			.start = 0,
			.end = 0,
			.size = 0,
			.mutex = PTHREAD_MUTEX_INITIALIZER,
			.cond = PTHREAD_COND_INITIALIZER,
			.process_joined = 0,
			.flag = 0
		};

		sensor_info_t sensor_count ={
			.sensor_name = 11,
			.sensor_reads = MAX_TEMP_SENSOR1_READS,
			.sensor_timing = TEMP_SENSOR1_TIMING,
			.buffer = &temp_fifo
		};

		sensor_info_t sensor_count2 ={
			.sensor_name = 12,
			.sensor_reads = MAX_TEMP_SENSOR2_READS,
			.sensor_timing = TEMP_SENSOR2_TIMING,
			.buffer = &temp_fifo
		};


		pthread_create(&temp_threads[1], NULL, read_sensor_data, (void *) &sensor_count);
		pthread_create(&temp_threads[2], NULL, read_sensor_data, (void *) &sensor_count2);
		pthread_create(&temp_threads[3], NULL, read_buffer_data, (void *) &temp_fifo);

		pthread_join( temp_threads[1], NULL );
		pthread_join( temp_threads[2], NULL );
		temp_fifo.process_joined = 1;
		pthread_cond_broadcast(&temp_fifo.cond);
		pthread_join( temp_threads[3], NULL );
	}

	// Mensagem exibida pelo processo pai, no final da execução
	printf("Exit\n");
	return 0;
}
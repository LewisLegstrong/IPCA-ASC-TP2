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
			fifo_buffer_t temp_fifo ={
				.start = 0,
				.end = 0,
				.size = 0,
				.mutex = PTHREAD_MUTEX_INITIALIZER,
				.cond = PTHREAD_COND_INITIALIZER,
				.process_joined = 0,
				.flag = 0
			};

			sensor_info_t sensor_count ={
				.sensor_name = 1,
				.sensor_reads = 15,
				.sensor_timing = 1,
				.buffer = &temp_fifo
			};

			sensor_info_t sensor_count2 ={
				.sensor_name = 2,
				.sensor_reads = 20,
				.sensor_timing = 2,
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
		wait(0);
	}
	else {                                        		// Se é o processo filho [TEMPERATURA]   
		#ifdef DEBUG
			// fifo_buffer_t temp_fifo ={
			// 	.start = 0,
			// 	.end = 0,
			// 	.size = 0,
			// 	.mutex = PTHREAD_MUTEX_INITIALIZER,
			// 	.cond = PTHREAD_COND_INITIALIZER,
			// 	.process_joined = 0,
			// 	.flag = 0
			// };

			// sensor_info_t sensor_count ={
			// 	.sensor_name = 1,
			// 	.sensor_reads = 15,
			// 	.sensor_timing = 1,
			// 	.buffer = &temp_fifo
			// };

			// sensor_info_t sensor_count2 ={
			// 	.sensor_name = 2,
			// 	.sensor_reads = 20,
			// 	.sensor_timing = 2,
			// 	.buffer = &temp_fifo
			// };

	
			// pthread_create(&temp_threads[1], NULL, read_sensor_data, (void *) &sensor_count);
			// pthread_create(&temp_threads[2], NULL, read_sensor_data, (void *) &sensor_count2);
			// pthread_create(&temp_threads[3], NULL, read_buffer_data, (void *) &temp_fifo);

			// pthread_join( temp_threads[1], NULL );
			// pthread_join( temp_threads[2], NULL );
			// temp_fifo.process_joined = 1;
			// pthread_cond_broadcast(&temp_fifo.cond);
			// pthread_join( temp_threads[3], NULL );


		#else
			sensor_info_t sensor_count [2];
			sensor_count[0].sensor_reads = MAX_TEMP_SENSOR1_READS;
			sensor_count[0].sensor_timing = TEMP_SENSOR1_TIMING;
			sensor_count[0].buffer = &temp_buffer;

			sensor_count[1].sensor_reads = MAX_TEMP_SENSOR2_READS;
			sensor_count[1].sensor_timing = TEMP_SENSOR2_TIMING;
			sensor_count[1].buffer = &temp_buffer;

			for (int i = 0; i < MAX_THREAD_COUNT; i++) {
				if (i < 2) {
					pthread_create(&temp_threads[i], NULL, read_sensor_data, (void *) &sensor_count[i]);
				}
				else {
					pthread_create(&humid_threads[i], NULL, read_buffer_data, (void *) &temp_buffer);
				}     
			}
		#endif
	}

	// Mensagem exibida pelo processo pai, no final da execução
	printf("Exit\n");
	return 0;
}
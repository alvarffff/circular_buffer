#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 

#define SIZE 10

typedef struct circular_buffer{
    int array[SIZE];
    int write_idx;
    int read_idx;
    int num_of_elements;
    //int size;
} circular_buffer_t;

circular_buffer_t circular_buffer;

// A normal C function that is executed as a thread 
// when its name is specified in pthread_create() 
void *reader_thread(void *vargp) 
{ 
	sleep(1); 
	printf("Reader thread init succesfully \n"); 
    for(;;)
    {   
        int value_readed;
        if(circular_buffer.num_of_elements > 0)
        {
            value_readed =  circular_buffer.array[circular_buffer.read_idx];
            printf("Value readed %d in position %d \n", value_readed, circular_buffer.read_idx);
            circular_buffer.num_of_elements--;
            circular_buffer.read_idx = (circular_buffer.read_idx + 1) % SIZE;
        }
        sleep(2); 
    }
	return NULL; 
}

void *writer_thread(void *vargp)
{   
    sleep(1);
    int numero = 0;
	printf("Writer thread init succesfully\n");
    for(;;)
    {
        printf("Writing %d in position %d \n", numero, circular_buffer.write_idx);
        circular_buffer.array[circular_buffer.write_idx] = numero;
        circular_buffer.num_of_elements++;

        circular_buffer.write_idx = (circular_buffer.write_idx+1) % SIZE;

        if(numero >= 100) numero = 0;
        else numero++;

        sleep(1); 
    } 
	return NULL; 
}

int main() 
{ 
	pthread_t thread_id[2]; 
	printf("Before Thread\n"); 
	pthread_create(&thread_id[0], NULL, reader_thread, NULL); 
    pthread_create(&thread_id[1], NULL, writer_thread, NULL); 
	pthread_join(thread_id[0], NULL); 
	printf("After Thread\n"); 
	exit(0); 
}

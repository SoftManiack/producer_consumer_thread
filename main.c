#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 

#define BUFFER_SIZE 10

struct Task
{
    /* data */
    int time;
    int task_id;
    int creator_id;
};

struct Task tasks_buffer[10];
int count = 0; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;  
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER; 

int random_int(){
    return 1 + rand() % ( 3 - 1 + 1);
}

void* producer(void* arg){

    //size_t length = sizeof(tasks) / sizeof(task[0]);
    int thread_num = *(int *)arg;

    while (1)
    {
        struct Task new_task = { 
            random_int(), 
            count + 1, 
            thread_num 
        };

        while (count >= BUFFER_SIZE) {
            printf("Поток %d: буфер полон, жду...\n", thread_num);
            pthread_cond_wait(&buffer_not_full, &mutex);
        }

        pthread_mutex_lock(&mutex);

        tasks_buffer[count] = new_task;

        count++;

        // Будим потребителей, если буфер был пуст
        if (count == 1) {
            pthread_cond_signal(&buffer_not_empty);
        }

        pthread_mutex_unlock(&mutex);

        printf("Поток %d: добавил задачу номер %d !\n", thread_num, new_task.task_id);

        sleep(2);
    }

    return NULL;
}

void* consumer(void *arg){

    while(1){
        //pthread_mutex_lock(&mutex);

        //pthread_mutex_unlock(&mutex);
    }

}

int main(){
    srand(time(NULL));

    const int NUM_THREADS = 2;
    pthread_t threads_producer[NUM_THREADS];    // Массив идентификаторов потоков
    pthread_t threads_consumer[NUM_THREADS];

    int thread_producer_id_args[NUM_THREADS];  
    int thread_consumer_id_args[NUM_THREADS];  

    for(int i = 0; i < NUM_THREADS; i++){
        thread_producer_id_args[i] = i + 1;  
        pthread_create(&threads_producer[i], NULL, producer, &thread_producer_id_args[i]);
        pthread_create(&threads_consumer[i], NULL, consumer, &thread_consumer_id_args[i]);
    }
    
    //pthread_create(&prod_threads, NULL, producer, 2);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads_producer[i], NULL);
        pthread_join(threads_consumer[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 
#include <unistd.h>

#include "doubly_linked_list.h"

#define BUFFER_SIZE 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;  
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER; 

struct DoublyLinkedList* list;

int random_int(int max, int min){
    return min + rand() % ( max - min + 1);
}

void* producer(void* arg){

    int thread_num = *(int *)arg;

    while (1)
    {
        while (list->size >= BUFFER_SIZE) {
            printf("Producer %d: буфер полон, жду...\n", thread_num);
            pthread_cond_wait(&buffer_not_full, &mutex);
        }

        pthread_mutex_lock(&mutex);

        int task_id = random_int(10000,1);

        add_first(list, task_id, random_int(5,1), thread_num);

        // Будим потребителей, если буфер был пуст
        if (list->size == 1) {
            pthread_cond_broadcast(&buffer_not_empty);
        }

        pthread_mutex_unlock(&mutex);

        sleep(2);
        printf("Producer %d: добавил задачу номер %d , в списке %d задач!\n", thread_num, task_id, list->size);
    }

    return NULL;
}

void* consumer(void *arg){

    int thread_num = *(int *)arg;
    int delay = 0;

    printf("Consumer %d запущен\n", thread_num);
    
    while(1){
        pthread_mutex_lock(&mutex);

        while (list->size == 0) {
            printf("Consumer %d: буфер пуст, жду...\n", thread_num);
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }
        
        if(list->size > 0){

            int *values = remove_first(list);

            if (values != NULL) {
                delay = values[1];
                printf("Consumer %d взял задачу: %d, %d: секунд, в списке %d задач \n", thread_num, values[0], values[1], list->size);

                free(values);  // Не забываем освободить память!
            }

            if (list->size == BUFFER_SIZE - 1) {
                pthread_cond_broadcast(&buffer_not_full);
            }
        }

        pthread_mutex_unlock(&mutex);

        if (delay > 0) {
            printf("Consumer %d: обрабатываю задачу %d секунд...\n", thread_num, delay);
            sleep(delay);
        }
    }

    sleep(delay);

    return NULL;
}

int main(){
    printf("=== Запуск системы \n");
    srand(time(NULL));

    list = (struct DoublyLinkedList*)malloc(sizeof(struct DoublyLinkedList)); // инициализацтя списка
    
    if(list == NULL){
        printf("Memory allocation error !");
        return 1;
    }

    init_list(list);

    const int NUM_PRODUCER_THREADS = 2;
    const int NUM_CONSUMER_THREADS = 2;
    pthread_t threads_producer[NUM_PRODUCER_THREADS];    
    pthread_t threads_consumer[NUM_CONSUMER_THREADS];

    int thread_producer_id_args[NUM_PRODUCER_THREADS];  
    int thread_consumer_id_args[NUM_CONSUMER_THREADS];  

    for(int i = 0; i < NUM_PRODUCER_THREADS; i++){
        thread_producer_id_args[i] = i + 1;  
        pthread_create(&threads_producer[i], NULL, producer, &thread_producer_id_args[i]);
    }

    for(int i = 0; i < NUM_CONSUMER_THREADS; i++){
        thread_consumer_id_args[i] = i + 1;  
        pthread_create(&threads_consumer[i], NULL, consumer, &thread_consumer_id_args[i]);
    }

    for (int i = 0; i < NUM_PRODUCER_THREADS; i++) {
        pthread_join(threads_producer[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMER_THREADS; i++) {
        pthread_join(threads_consumer[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    //destroy_resources();
    
    return 0;
}
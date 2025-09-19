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
            printf("Поток %d: буфер полон, жду...\n", thread_num);
            pthread_cond_wait(&buffer_not_full, &mutex);
        }

        pthread_mutex_lock(&mutex);

        int task_id = random_int(10000,1);

        add_first(list, task_id, random_int(3,1), thread_num);

        // Будим потребителей, если буфер был пуст
        if (list->size == 1) {
            pthread_cond_signal(&buffer_not_empty);
        }

        pthread_mutex_unlock(&mutex);

        printf("Поток %d: добавил задачу номер %d !\n", thread_num, task_id);

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
    printf("=== Запуск системы \n");
    srand(time(NULL));

    list = (struct DoublyLinkedList*)malloc(sizeof(struct DoublyLinkedList));
    
    if(list == NULL){
        printf("Memory allocation error !");
        return 1;
    }

    init_list(list);

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

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads_producer[i], NULL);
        pthread_join(threads_consumer[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    //destroy_resources();
    
    return 0;
}
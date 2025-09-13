#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 

#define BUFFER_SIZE 10

struct Task
{
    /* data */
    int time;
    int taskId;
    int creatorId;
};

struct Task tasksBuffer[10];
int count = 0; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //  это специальный макрос, который компилятор заменяет на код, необходимый для инициализации мьютекса со значениями по умолчанию

int random_int(){
    return 1 + rand() % ( 3 - 1 + 1);
}

void* producer(void* arg){

    //size_t length = sizeof(tasks) / sizeof(task[0]);
    int thread_num = *(int *)arg;

    while (count < BUFFER_SIZE)
    {
        pthread_mutex_lock(&mutex);

        sleep(1);

        struct Task newTask = { 
            random_int(), 
            count + 1, 
            thread_num 
        };

        tasksBuffer[count] = newTask;

        count++;

        pthread_mutex_unlock(&mutex);

        printf("Поток %d: добавил задачу номер %d !\n", thread_num, newTask.taskId);
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

    pthread_t prod_thread, cons_thread;

    const int NUM_THREADS = 3;
    pthread_t threads[NUM_THREADS];    // Массив идентификаторов потоков
    int thread_id_args[NUM_THREADS];  

    for(int i = 0; i < NUM_THREADS; i++){
        thread_id_args[i] = i + 1;  
        pthread_create(&prod_thread, NULL, producer, &thread_id_args[i]);
    }
    
    pthread_create(&prod_thread, NULL, producer, 2);

    pthread_join(prod_thread, NULL);
    //pthread_join(cons_thread, NULL);
    
    return 0;
}
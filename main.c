#include <stdio.h>
#include <pthread.h>

struct Task
{
    /* data */
    int completed;
    int time;
    int taskId;
};

struct Task tasks[10];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //  это специальный макрос, который компилятор заменяет на код, необходимый для инициализации мьютекса со значениями по умолчанию

int random_int(){
    return 1 + rand() % ( 3 - 1 + 1);
}

void* producer(void* arg){

    //size_t length = sizeof(tasks) / sizeof(task[0]);
    
}

void *consumer(void *arg){

}

int main(){
    srand(time(NULL));

    pthread_t prod_thread, cons_thread;


}
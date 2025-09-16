#include "doubly_linked_list.h"

#define BUFFER_SIZE 10

// Создание нового узла
struct Task* create_node(int task_id, int time, int creator_id) {
    struct Task* new_task = (struct Task*)malloc(sizeof(struct Task));
    if (new_task == NULL) {
        printf("Memory error!\n");
        exit(1);
    }
    new_task->task_id = task_id;
    new_task->task_id;
    new_task->creator_id = creator_id;
    new_task->next = NULL;
    new_task->prev = NULL;
    return new_task;
}

void init_list(struct DoublyLinkedList* list){
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
};

int is_empty(struct DoublyLinkedList* list) {
    return list->head == NULL;
}

// Добавление в начало

void add_first(struct DoublyLinkedList* list, int task_id, int time, int creator_id){
    struct Task* new_node = create_node(task_id, time, creator_id);

    if(is_empty(list)){
        list->head  = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->size++;
}

// Добавление в конец

void add_last(struct DoublyLinkedList* list, int task_id, int time, int creator_id){
    struct Task* new_node = create_node(task_id, time, creator_id);

    if(is_empty(list)){
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

int remove_first(struct DoublyLinkedList* list) {
    if (is_empty(list)) {
        printf("List is empty!\n");
        return -1;
    }
    
    struct Task* temp = list->head;
    int id_task = temp->task_id;
    
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    
    free(temp);
    list->size--;
    return id_task;
}

int remove_last(struct DoublyLinkedList* list){
    if (is_empty(list)) {
        printf("List is empty!\n");
        return -1;
    }

    struct Task* temp = list->head;
    int id_task = temp->task_id;

    if (list->head == list->tail) { 
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    
    free(temp);
    list->size--;
    return id_task;
}

int remove_task_by_id(struct DoublyLinkedList* list, int task_id){
    if (is_empty(list)) {
        return 0; 
    }

    struct Task* current = list->head;

    while(current != NULL){
        if(current->task_id == task_id){
            if(current == list->head){
                remove_first(list);
            } else if(current == list->tail){
                remove_last(list);
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                list->size--;
            }
            return 1; // найдено и удалено
        } 

        current = current->next;
    }   

    return 0; // не найдено
}


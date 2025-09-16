#include <stdlib.h>
#include <stdio.h>

struct Task
{
    /* data */
    int time;
    int task_id;
    int creator_id;
    struct Task* next;
    struct Task* prev;
};

struct DoublyLinkedList {
    int size;
    struct Task* head; // первый узел
    struct Task* tail; // количество элементов
}; 

struct Task* create_node(int task_id, int time, int creator_id);

void init_list(struct DoublyLinkedList* list);
void add_first(struct DoublyLinkedList* list, int task_id, int time, int creator_id);
int is_empty(struct DoublyLinkedList* list);
void add_last(struct DoublyLinkedList* list, int task_id, int time, int creator_id);
int remove_first(struct DoublyLinkedList* list);
int remove_last(struct DoublyLinkedList* list);
int remove_task_by_id(struct DoublyLinkedList* list, int task_id);

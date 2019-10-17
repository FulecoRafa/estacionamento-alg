#include "carro.h"

#ifndef QUEUE_H
#define QUEUE_H

typedef struct _queue queue;

typedef struct _node node;
//Defines the structure for the queue
struct _queue{
    node* HEAD;
    node* TAIL;
    int SIZE;
    int FILL;
    int VERBOSE;
};


node *node_create(carro *c , int VERBOSE);
void node_erase(node* n);
carro *item_getter(node* n);
queue* create_queue(int max , int VERBOSE);
int empty_queue(queue *q);
int queue_size(queue *q);
int queue_filling(queue *q);
int full_queue(queue *q);
void erase_queue(queue *q);
node* queue_HEAD(queue *q);
int queue_insert(queue *q , carro *c);
carro *queue_next(queue *q);
void print_queue(queue *q);

#endif
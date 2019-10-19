#include "carro.h"

#ifndef QUEUE_H
#define QUEUE_H

typedef struct _queue queue;

typedef struct _q_node q_node;


q_node *q_node_create(carro *c , int VERBOSE);
void q_node_erase(q_node* n);
carro *q_item_getter(q_node* n);
queue* create_queue(int max , int VERBOSE);
int empty_queue(queue *q);
int queue_size(queue *q);
int queue_filling(queue *q);
int full_queue(queue *q);
void erase_queue(queue *q);
q_node* queue_HEAD(queue *q);
q_node* queue_TAIL(queue *q);
int queue_insert(queue *q , carro *c);
carro *queue_next(queue *q);
void print_queue(queue *q);
int queue_search(queue *q, carro *c);
q_node *travel_queue(queue *q , int index);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "carro.h"

#define ERROR -32000//defines an absurd number for error returns

// Estrutura do no
struct _node{
    carro *car;
    node* next;
    int VERBOSE;
};

//Function to create a node. 'num' is the item to be stored and 'VERBOSE' is to set if the process messages will be printed. Set it 1 for printing and 0 for non-printing
node *node_create(carro *c , int VERBOSE){
    node *n = (node*) malloc(sizeof(node));
    if(n != NULL){
        n->next = NULL;
        n->car = c;
        n->VERBOSE = VERBOSE;
        if(VERBOSE) printf("[:)] Node created [@ node_create()]\n");
        return n;
    }else{
        if(VERBOSE) printf("[!] Error creating node [@ node_create()]\n");
        return NULL;
    }
}

//Erases the node especified
void node_erase(node* n){
    n->next = NULL;
    int auxVERBOSE = n->VERBOSE;
    free(n);
    if(auxVERBOSE) printf("[:)] Node deleted [@ node_erase()]\n");
}


carro *item_getter(node* n){
    return (n->car);
}
//---------------------------------------------------------------------------------------------------------------------------------
//Defines the structure for the queue
struct _queue{
    node* HEAD;
    node* TAIL;
    int SIZE;
    int FILL;
    int VERBOSE;
};

//Creates the queue. 'max' defines the maximum number of items allowed to be stored and 'VERBOSE' defines if process messages will be shown (just like in the nodes).
queue* create_queue(int max , int VERBOSE){
    queue* new_queue = (queue*) malloc (sizeof(queue));
    if(new_queue == NULL){
        if(VERBOSE) printf("[!] Error creating queue [@ queue *create_queue()]\n");
        return NULL;
    }
    new_queue->HEAD = NULL;
    new_queue->TAIL = NULL;
    new_queue->SIZE = max;
    new_queue->FILL = 0;
    new_queue->VERBOSE = VERBOSE;
    if(VERBOSE) printf("[:)] queue created [@ create_queue()]\n");
    return new_queue;
}

//Checks if the queue is empty. Returns 1 for empty, 0 if filled and 'ERROR' if NULL.
int empty_queue(queue *q){
    if(q == NULL){
        if(q->VERBOSE) printf("[!] Unable to identify emptyness :: queue is NULL [@ empty_queue()]\n");
        return ERROR;
    }
    else if(q->FILL == 0) return 1;
    else return 0;
}

//Returns the maximum number of items allowed in this queue
int queue_size(queue *q){
    return((q != NULL)? q->SIZE : ERROR);
}

//Returns the number of items already in the queue
int queue_filling(queue *q){
    return((q != NULL)? q->FILL : ERROR);
}

//Returns 1 if queue is full and 0 if not
int full_queue(queue *q){
    return((q->SIZE == q->FILL)? 1:0);
}

//Completely erases the queue and it's items
void erase_queue(queue *q){
    node *it;
    int auxVERBOSE=q->VERBOSE;
    if(q != NULL && q->FILL !=0){        
        while(q->HEAD){
            it = q->HEAD;
            q->HEAD = q->HEAD->next;
            node_erase(it);
        }
    }
    free(q);
    if(auxVERBOSE) printf("[:)] queue erased [@ erase_queue()]\n");
}

//Returns the next HEAD item in the queue
node* queue_HEAD(queue *q){
    if(q != NULL){
        return q->HEAD;
    }
    if(q->VERBOSE) printf("[!] Unable to retrive item :: queue is NULL [@ queue_HEAD()]\n");
    return NULL;
}

node* queue_TAIL(queue *q){
    if(q != NULL){
        return q->TAIL;
    }
    if(q->VERBOSE) printf("[!] Unable to retrive item :: queue is NULL [@ queue_HEAD()]\n");
    return NULL;
}

//Adds items to the queue. 'num' is the item to be added. Returns 1 if operation is successfull and 0 if not.
int queue_insert(queue *q , carro *c){
    if(full_queue(q)){
        if(q->VERBOSE) printf("[!] Can't pile item :: queue already full [@ queue_pile()]\n");
        return 0;
    }else{
        node *new_node = (node*) malloc(sizeof(node));
        new_node = node_create(c , q->VERBOSE);
        q->TAIL->next = new_node;
        q->TAIL = new_node;
        q->FILL++;
        if(q->VERBOSE) printf("[:)] Item piled on queue [@ queue_pile]\n");
        return 1;
    }
}

//Removes the next item on the queue. It returns this item.
carro *queue_next(queue *q){
    if(q == NULL){
        if(q->VERBOSE) printf("[!] Unable to retrive item :: queue is NULL [@ queue_unpile()]\n");
    }else if(empty_queue(q)){
        if(q->VERBOSE) printf("[!] Unable to retrieve item :: queue is empty [@ queue_unpile()]\n");
    }else{
        carro *c = q->HEAD->car;
        node* point = q->HEAD;
        q->HEAD = q->HEAD->next;
        point->next = NULL; free(point); point = NULL;
        q->FILL--;
        return c;
    }
}

void print_queue(queue *q){
    node* it = q->HEAD;
    while(it){
        printf("#-----#\n");
        printf("#--Placa: %d--#\n" , placaGetter(it->car));
        printf("#--Chegada: %02d-#\n" , chegadaGetter(it->car));
        printf("#--Saída: %02d-#\n" , saidaGetter(it->car));
        printf("#--Desconto: %.2f-#\n" , descontoGetter(it->car));
        it=it->next;
    }
    printf("#-----#\n");

}

// Search for a car in the queue, return 1 if true and 0 if false
int queue_search(queue *q, carro *c) {
    node *it = q->HEAD;
    while(it) {
        if(it == placaGetter(c)) {
            return 1;
        }
        it = it->next;
    }
    return 0;
}
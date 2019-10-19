#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "carro.h"

#define ERROR -32000//defines an absurd number for error returns

// Estrutura do no
struct _q_node{
    carro *car;
    q_node* next;
    int VERBOSE;
};

//Function to create a q_node. 'num' is the item to be stored and 'VERBOSE' is to set if the process messages will be printed. Set it 1 for printing and 0 for non-printing
q_node *q_node_create(carro *c , int VERBOSE){
    q_node *n = (q_node*) malloc(sizeof(q_node));
    if(n != NULL){
        n->next = NULL;
        n->car = c;
        n->VERBOSE = VERBOSE;
        if(VERBOSE) printf("[:)] q_Node created [@ q_node_create()]\n");
        return n;
    }else{
        if(VERBOSE) printf("[!] Error creating q_node [@ q_node_create()]\n");
        return NULL;
    }
}

//Erases the q_node especified
void q_node_erase(q_node* n){
    n->next = NULL;
    int auxVERBOSE = n->VERBOSE;
    free(n);
    if(auxVERBOSE) printf("[:)] q_Node deleted [@ q_node_erase()]\n");
}


carro *q_item_getter(q_node* n){
    return (n->car);
}
//---------------------------------------------------------------------------------------------------------------------------------
//Defines the structure for the queue
struct _queue{
    q_node* HEAD;
    q_node* TAIL;
    int SIZE;
    int FILL;
    int VERBOSE;
};

//Creates the queue. 'max' defines the maximum number of items allowed to be stored and 'VERBOSE' defines if process messages will be shown (just like in the q_nodes).
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
    q_node *it;
    int auxVERBOSE=q->VERBOSE;
    if(q != NULL && q->FILL !=0){        
        while(q->HEAD){
            it = q->HEAD;
            q->HEAD = q->HEAD->next;
            q_node_erase(it);
        }
    }
    free(q);
    if(auxVERBOSE) printf("[:)] queue erased [@ erase_queue()]\n");
}

//Returns the next HEAD item in the queue
q_node* queue_HEAD(queue *q){
    if(q != NULL){
        return q->HEAD;
    }
    if(q->VERBOSE) printf("[!] Unable to retrive item :: queue is NULL [@ queue_HEAD()]\n");
    return NULL;
}

q_node* queue_TAIL(queue *q){
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
    }if(empty_queue(q)){
        q_node *new_q_node = (q_node*) malloc(sizeof(q_node));
        new_q_node = q_node_create(c , q->VERBOSE);
        q->HEAD = new_q_node;
        q->TAIL = new_q_node;
        q->FILL++;
        if(q->VERBOSE) printf("[:)] Item piled on queue [@ queue_pile]\n");
        return 1;
    }else{
        q_node *new_q_node = (q_node*) malloc(sizeof(q_node));
        new_q_node = q_node_create(c , q->VERBOSE);
        q->TAIL->next = new_q_node;
        q->TAIL = new_q_node;
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
        q_node* point = q->HEAD;
        q->HEAD = q->HEAD->next;
        point->next = NULL; free(point); point = NULL;
        q->FILL--;
        return c;
    }
}

void print_queue(queue *q){
    q_node* it = q->HEAD;
    while(it){
        printf("#-----#\n");
        printf("#--Placa: %d--#\n" , placaGetter(it->car));
        printf("#--Chegada: %02d-#\n" , chegadaGetter(it->car));
        printf("#--Saída: %02d-#\n" , saidaGetter(it->car));
        printf("#--Valor a pagar: R$%d.00-#\n" , precoGetter(it->car));
        printf("#--Desconto: %.2f-#\n" , descontoGetter(it->car));
        printf("#--Valor: %.2f-#\n" , ((float)(precoGetter(it->car))) - descontoGetter(it->car));
        it=it->next;
    }
    printf("#-----#\n");

}

// Search for a car in the queue, return 1 if true and 0 if false
int queue_search(queue *q, carro *c) {
    q_node *it = q->HEAD;
    while(it) {
        if(placaGetter(it->car) == placaGetter(c)) {
            return 1;
        }
        it = it->next;
    }
    return 0;
}

q_node *travel_queue(queue *q , int index){
    q_node *it;
    it = q->HEAD;
    for(int i = 1 ; i <= index ; i++){
        it = it->next;
    }
    return it;
}
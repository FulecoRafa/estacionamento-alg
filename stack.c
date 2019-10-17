#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
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
//-------------------------------------------------------------------------------------------------------------------------------


//Creates the stack. 'max' defines the maximum number of items allowed to be stored and 'VERBOSE' defines if process messages will be shown (just like in the nodes).
stack* create_stack(int max , int VERBOSE){
    stack* new_stack = (stack*) malloc (sizeof(stack));
    if(new_stack == NULL){
        if(VERBOSE) printf("[!] Error creating stack [@ stack *create_stack()]\n");
        return NULL;
    }
    new_stack->TOP = NULL;
    new_stack->SIZE = max;
    new_stack->FILL = 0;
    new_stack->VERBOSE = VERBOSE;
    if(VERBOSE) printf("[:)] Stack created [@ create_stack()]\n");
    return new_stack;
}

//Checks if the stack is empty. Returns 1 for empty, 0 if filled and 'ERROR' if NULL.
int empty_stack(stack *s){
    if(s == NULL){
        if(s->VERBOSE) printf("[!] Unable to identify emptyness :: Stack is NULL [@ empty_stack()]\n");
        return ERROR;
    }
    else if(s->FILL == 0) return 1;
    else return 0;
}

//Returns the maximum number of items allowed in this stack
int stack_size(stack *s){
    return((s != NULL)? s->SIZE : ERROR);
}

//Returns the number of items already in the stack
int stack_filling(stack *s){
    return((s != NULL)? s->FILL : ERROR);
}

//Returns 1 if stack is full and 0 if not
int full_stack(stack *s){
    return((s->SIZE == s->FILL)? 1:0);
}

//Completely erases the stack and it's items
void erase_stack(stack *s){
    node *it;
    int auxVERBOSE=s->VERBOSE;
    if(s != NULL && s->FILL !=0){        
        while(s->TOP){
            it = s->TOP;
            s->TOP = s->TOP->next;
            node_erase(it);
        }
    }
    free(s);
    if(s->VERBOSE) printf("[:)] Stack erased [@ erase_stack()]\n");
}

//Returns the next top item in the stack
node* stack_top(stack *s){
    if(s != NULL){
        return s->TOP;
    }
    if(s->VERBOSE) printf("[!] Unable to retrive item :: Stack is NULL [@ stack_top()]\n");
    return NULL;
}

//Adds items to the stack. 'num' is the item to be added. Returns 1 if operation is successfull and 0 if not.
int stack_pile(stack *s , carro *c){
    if(full_stack(s)){
        if(s->VERBOSE) printf("[!] Can't pile item :: Stack already full [@ stack_pile()]\n");
        return 0;
    }else{
        node *new_node = (node*) malloc(sizeof(node));
        new_node = node_create(c , s->VERBOSE);
        new_node->next = s->TOP;
        s->TOP = new_node;
        s->FILL++;
        if(s->VERBOSE) printf("[:)] Item piled on stack [@ stack_pile]\n");
        return 1;
    }
}

//Removes the next item on the stack. It returns this item.
carro *stack_unpile(stack *s){
    if(s == NULL){
        if(s->VERBOSE) printf("[!] Unable to retrive item :: Stack is NULL [@ stack_unpile()]\n");
    }else if(empty_stack(s)){
        if(s->VERBOSE) printf("[!] Unable to retrieve item :: Stack is empty [@ stack_unpile()]\n");
    }else{
        carro *c = s->TOP->car;
        node* point = s->TOP;
        s->TOP = s->TOP->next;
        point->next = NULL; free(point); point = NULL;
        s->FILL--;
        return c;
    }
}

void print_stack(stack *s){
    node* it = s->TOP;
    while(it){
        printf("#-----#\n");
        printf("#--Placa: %d--#\n" , placaGetter(it->car));
        printf("#--Chegada: %02d-#\n" , chegadaGetter(it->car));
        printf("#--Saída: %02d-#\n" , saidaGetter(it->car));
        printf("#--Desconto: %.2f-#\n" , descontoGetter(it->car));
        it=it->next;
    }
    printf("#######\n");

}

// Search for a car in the stack, return 1 if true and 0 if false
int stack_search(stack *s, carro *c) {
    node *it = s->TOP;
    while(it) {
        if(it == placaGetter(c)) {
            return 1;
        }
        it = it->next;
    }
    return 0;
}
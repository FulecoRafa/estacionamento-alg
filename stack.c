#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "carro.h"

#define ERROR -32000//defines an absurd number for error returns

// Estrutura do no
struct _s_node{
    carro *car;
    s_node* next;
    int VERBOSE;
};

//Function to create a s_node. 'num' is the item to be stored and 'VERBOSE' is to set if the process messages will be printed. Set it 1 for printing and 0 for non-printing
s_node *s_node_create(carro *c , int VERBOSE){
    s_node *n = (s_node*) malloc(sizeof(s_node));
    if(n != NULL){
        n->next = NULL;
        n->car = c;
        n->VERBOSE = VERBOSE;
        if(VERBOSE) printf("[:)] s_Node created [@ s_node_create()]\n");
        return n;
    }else{
        if(VERBOSE) printf("[!] Error creating s_node [@ s_node_create()]\n");
        return NULL;
    }
}

//Erases the s_node especified
void s_node_erase(s_node* n){
    n->next = NULL;
    int auxVERBOSE = n->VERBOSE;
    free(n);
    if(auxVERBOSE) printf("[:)] s_Node deleted [@ s_node_erase()]\n");
}

carro *s_item_getter(s_node* n){
    return (n->car);
}
//-------------------------------------------------------------------------------------------------------------------------------

//Defines the stack's structure
struct _stack{
    s_node* TOP;
    int SIZE;
    int FILL;
    int VERBOSE;
};

//Creates the stack. 'max' defines the maximum number of items allowed to be stored and 'VERBOSE' defines if process messages will be shown (just like in the s_nodes).
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
    s_node *it;
    int auxVERBOSE=s->VERBOSE;
    if(s != NULL && s->FILL !=0){        
        while(s->TOP){
            it = s->TOP;
            s->TOP = s->TOP->next;
            s_node_erase(it);
        }
    }
    free(s);
    if(s->VERBOSE) printf("[:)] Stack erased [@ erase_stack()]\n");
}

//Returns the next top item in the stack
s_node* stack_top(stack *s){
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
        s_node *new_s_node = (s_node*) malloc(sizeof(s_node));
        new_s_node = s_node_create(c , s->VERBOSE);
        new_s_node->next = s->TOP;
        s->TOP = new_s_node;
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
        s_node* point = s->TOP;
        s->TOP = s->TOP->next;
        point->next = NULL; free(point); point = NULL;
        s->FILL--;
        return c;
    }
}

void print_stack(stack *s){
    s_node* it = s->TOP;
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
    printf("#######\n");

}

// Search for a car in the stack, return 1 if true and 0 if false
int stack_search(stack *s, carro *c) {
    s_node *it = s->TOP;
    while(it) {
        if(placaGetter(it->car) == placaGetter(c)) {
            return 1;
        }
        it = it->next;
    }
    return 0;
}

s_node *travel_stack(stack *s , int index){
    s_node *it;
    it = s->TOP;
    for(int i = 1 ; i <= index ; i++){
        it = it->next;
    }
    return it;
}
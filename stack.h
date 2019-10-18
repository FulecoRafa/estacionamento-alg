#include "carro.h"

#ifndef STACK_H
#define STACK_H

typedef struct _stack stack;

typedef struct _node node;


stack* create_stack(int max , int verbose);

node *node_create(carro *c , int VERBOSE);

void node_erase(node* n);

int empty_stack(stack *s);

int stack_size(stack *s);

int full_stack(stack *s);

void erase_stack(stack *s);

node* stack_top(stack *s);

int stack_pile(stack *s , carro *c);

carro *stack_unpile(stack *s);

int stack_filling(stack *s);

void print_stack(stack *s);

carro *item_getter(node* n);

int stack_search(stack *s, carro *c);


node *travel_stack(stack *s , int index);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "carro.h"

#ifndef STACK_H
#define STACK_H

typedef struct _stack stack;

typedef struct _s_node s_node;


stack* create_stack(int max , int verbose);

s_node *s_node_create(carro *c , int VERBOSE);

void s_node_erase(s_node* n);

int empty_stack(stack *s);

int stack_size(stack *s);

int full_stack(stack *s);

void erase_stack(stack *s);

s_node* stack_top(stack *s);

int stack_pile(stack *s , carro *c);

carro *stack_unpile(stack *s);

int stack_filling(stack *s);

void print_stack(stack *s);

carro *s_item_getter(s_node* n);

int stack_search(stack *s, carro *c);


s_node *travel_stack(stack *s , int index);

#endif
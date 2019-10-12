#include "stack.h"
#include "queue.h"

#ifndef FUNCOES_CARRO_H
#define FUNCOES_CARRO_H

int carro_checkout(carro c, queue *q, stack *s);
int carro_disponibilidade(carro c, queue *q, stack *s);
int carro_rejeicao(carro c, queue *q, stack *s);

#endif
#include <stdio.h>
#include <stdlib.h>

#ifndef CARRO_H
#define CARRO_H

typedef struct _carro carro;

int placaGetter(carro *c);
int saidaGetter(carro *c);
int chegadaGetter(carro *c);
float descontoGetter(carro *c);
int precoGetter(carro *c);
void applyDiscount(carro *c , float discount);
void carro_imprime(carro *c);
carro *carro_cria(int placa, int chegada, int saida, int preco, float desconto);

#endif
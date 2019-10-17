#ifndef CARRO_H
#define CARRO_H

typedef struct _carro carro;

int placaGetter(carro *c);
int saidaGetter(carro *c);
int chegadaGetter(carro *c);
float descontoGetter(carro *c);
void carro_imprime(carro *c);

#endif
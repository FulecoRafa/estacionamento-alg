#include "carro.h"

// Estrutura do carro
struct _carro {
    int placa;
    int chegada;
    int saida;
    float desconto;
};

// Estrutura do no
struct _node{
    carro car;
    node* next;
    int VERBOSE;
};
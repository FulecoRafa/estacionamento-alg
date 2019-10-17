#include "carro.h"

// Estrutura do carro
struct _carro {
    int placa;
    int chegada;
    int saida;
    float desconto;
};

int placaGetter(carro *c) {
    return c->placa;
}

int chegadaGetter(carro *c) {
    return c->chegada;
}

int saidaGetter(carro *c) {
    return c->saida;
}

float descontoGetter(carro *c) {
    return c->desconto;
}

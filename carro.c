#include "carro.h"

// Estrutura do carro
struct _carro {
    int placa;
    int chegada;
    int saida;
    float desconto;
};

carro *carro_cria(int placa, int chegada, int saida, float desconto) {
    carro *c = (carro*) malloc(sizeof(carro));
    c->placa = placa;
    c->chegada = chegada;
    c->saida = saida;
    c->desconto = desconto;
    return c;
}

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

void carro_imprime(carro *c) {
    printf("###############\n");
    printf("PLACA-> %d\nCHEGADA-> %d\nSAIDA-> %d\nDESCONTO-> %.2f\n", placaGetter(c), chegadaGetter(c), saidaGetter(c), descontoGetter(c));
    printf("###############\n");
}

#include "carro.h"

// Estrutura do carro
struct _carro {
    int placa;
    int chegada;
    int saida;
    int preco;
    float desconto;
};

carro *carro_cria(int placa, int chegada, int saida, int preco, float desconto) {
    carro *c = (carro*) malloc(sizeof(carro));
    c->placa = placa;
    c->chegada = chegada;
    c->saida = saida;
    c->preco = preco;
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

int precoGetter(carro *c){
    return c->preco;
}

float descontoGetter(carro *c) {
    return c->desconto;
}

void applyDiscount(carro *c , float discount){
    c->desconto = discount;
}

void carro_imprime(carro *c){
    printf("#--Placa: %d--#\n" , placaGetter(c));
    printf("#--Chegada: %02d-#\n" , chegadaGetter(c));
    printf("#--Saída: %02d-#\n" , saidaGetter(c));
    printf("#--Valor a pagar: R$%d,00-#\n" , precoGetter(c));
    printf("#--Desconto: %.2f-#\n" , descontoGetter(c));
    printf("#--Valor: %.2f-#\n" , ((float)(precoGetter(c))) - descontoGetter(c));
}
#include "carro.h"

// Estrutura do carro
struct _carro {
    int placa;
    int chegada;
    int saida;
    int preco;
    float desconto;
};

//Cria um carro
carro *carro_cria(int placa, int chegada, int saida, int preco, float desconto) {
    carro *c = (carro*) malloc(sizeof(carro));
    c->placa = placa;
    c->chegada = chegada;
    c->saida = saida;
    c->preco = preco;
    c->desconto = desconto;
    return c;
}

//Retorna a placa do carro
int placaGetter(carro *c) {
    return c->placa;
}

//Retorna o horário de chegada do carro
int chegadaGetter(carro *c) {
    return c->chegada;
}

//Retorna o horário de saída do carro
int saidaGetter(carro *c) {
    return c->saida;
}

//Retorna o valor a ser pago do carro
int precoGetter(carro *c){
    return c->preco;
}

//Retorna o valor do desconto que o carro tem
float descontoGetter(carro *c) {
    return c->desconto;
}

//Aplicao desconto no carro
void applyDiscount(carro *c , float discount){
    c->desconto = discount;
}

//Imprime o carro
void carro_imprime(carro *c){
    printf("#--Placa: %d--#\n" , placaGetter(c));
    printf("#--Chegada: %02d-#\n" , chegadaGetter(c));
    printf("#--Saída: %02d-#\n" , saidaGetter(c));
    printf("#--Valor a pagar: R$%d,00-#\n" , precoGetter(c));
    printf("#--Desconto: %.2f-#\n" , descontoGetter(c));
    printf("#--Valor: %.2f-#\n" , ((float)(precoGetter(c))) - descontoGetter(c));
}
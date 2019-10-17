#include "stack.h"
#include "queue.h"

// Define o carro e insere, se possível, no estacionamento
int carro_checkin(queue *q, stack *s) {
    int placa, chegada, saida;
    printf("Placa: \n");
    scanf("%d", &placa);
    printf("Chegada: \n");
    scanf("%d", &chegada);
    printf("Horas: \n");
    scanf("%d", &saida);
    saida += chegada;

    carro *c = carro_cria();
    //rejeicao
    if(carro_disponibilidade(c, q, s) == 1) {
        stack_pile(s, c);
        return 1;
    }
    else {
        queue_insert(q, c);
        return 1;
    }

    return 0;

}

// Imprime os dados e remove os carros expirados em relacao ao novo carro
int carro_checkout(carro *c, queue *q, stack *s) {
    while(1) {
        if(getterSaida(queue_HEAD(q)) <= getterSaida(c)) {
            carro_imprime(queue_next(q));
        } else break;
    }

    while(1) {
        if(getterSaida(stack_top(s)) <= getterSaida(c)) {
            carro_imprime(stack_top(s));
        } else break;
    }
}

// Retorna em qual patio o carro deve parar, se possivel,
// 0-> nao foi possivel inserir, 1 -> insere na stack, 2 -> insere na queue
int carro_disponibilidade(carro *c, queue *q, stack *s) {
    if (empty_queue(q) == 1 && empty_stack(s) == 1) return 1;

    if (empty_queue(q) == 0 && empty_stack(s) == 1) return 2;

    if (empty_queue(q) == 1 && empty_stack(s) == 0) return 1;

    if ((empty_queue(q) == 0 && empty_stack(s) == 0) &&
        (full_queue(q) == 0 || full_stack(s) == 0)) {
            
            if(saidaGetter(c) <= saidaGetter(item_getter(stack_top(s)))) return 1;

            if(saidaGetter(c) >= saidaGetter(item_getter(queue_TAIL(s)))) return 2;
    }

    return 0;
}

// Retorna 0 se o carro for rejeitado, caso contrario, retorna o pátio a ser colocado.
int carro_rejeicao(carro *c, queue *q, stack *s) {
    int disp = carro_disponibilidade(c , q , s);
    if (chegadaGetter(c) < 8){
        printf("[!]Carro com horário de chegada fora do horário de funcionamento.\n");
        return 0;
    }else if(saidaGetter(c) > 22){
        printf("[!]Carro com horário de saída fora do horário de funcionamento.\n");
        return 0;
    }else if(full_queue(q) && full_stack(s)){
        printf("[!]Estacionamento lotado!\n");
        return 0;
    }else if(search_placa(c)){
        printf("[!]Carro já está no estacionamento\n");
        return 0;
    }else if(disp == 0){
        printf("[!]Carro inválido: horário de saída não compatível com carros já estacionados\n");
        return 0;
    }else{
        return (disp);
    }
}




int main() {

    return 0;
}
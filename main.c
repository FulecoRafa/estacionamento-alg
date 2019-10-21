#include "stack.h"
#include "queue.h"
#include "carro.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Retorna em qual patio o carro deve parar, se possivel,
// 0-> nao foi possivel inserir, 1 -> insere na stack, 2 -> insere na queue
int carro_disponibilidade(carro *c, queue *q, stack *s) {
    if (empty_queue(q) == 1 && empty_stack(s) == 1) return 1;

    if (empty_queue(q) == 0 && empty_stack(s) == 1) return 1;

    if (empty_queue(q) == 1 && empty_stack(s) == 0) return 2;

    if ((empty_queue(q) == 0 && empty_stack(s) == 0) &&
        (full_queue(q) == 0 || full_stack(s) == 0)) {
            
            if(saidaGetter(c) <= saidaGetter(s_item_getter(stack_top(s)))) return 1;

            if(saidaGetter(c) >= saidaGetter(q_item_getter(queue_TAIL(q)))) return 2;
    }

    return 0;
}

// Retorna 0 se o carro for rejeitado, caso contrario, retorna o pátio a ser colocado.
int carro_rejeicao(carro *c, queue *q, stack *s , int verbose) {
    int disp = carro_disponibilidade(c , q , s);
    if (chegadaGetter(c) < 8){
        if(verbose) printf("[!]Carro com horário de chegada fora do horário de funcionamento.\n");
        return 0;
    }else if(saidaGetter(c) > 22){
        if(verbose) printf("[!]Carro com horário de saída fora do horário de funcionamento.\n");
        return 0;
    }else if(full_queue(q) && full_stack(s)){
        if(verbose) printf("[!]Estacionamento lotado!\n");
        return 0;
    }else if(queue_search( q , c ) || stack_search( s , c )){
        if(verbose) printf("[!]Carro já está no estacionamento\n");
        return 0;
    }else if(disp == 0){
        if(verbose) printf("[!]Carro inválido: horário de saída não compatível com carros já estacionados\n");
        return 0;
    }else{
        return (disp);
    }
}

// Imprime os dados e remove os carros expirados em relacao ao novo carro
int carro_checkout(carro *c, queue *q, stack *s) {
    while(!empty_queue(q)) {
        if(saidaGetter(q_item_getter(queue_HEAD(q))) <= chegadaGetter(c)) {
            carro_imprime(queue_next(q));
        } else break;
        
    }
    while(!empty_stack(s)){
        if(saidaGetter(s_item_getter(stack_top(s))) <= chegadaGetter(c)) {
            carro_imprime(stack_unpile(s));
        } else break;
        
    }
}

//Sorteia um carro quando já se têm 4 carros no estacionamento (25% de 15 = 3.75) e aplica um desconto a ele
//Considere o estacionamento como um array no qual a stack vem antes
void sorteio(stack *s , queue *q){
    int max = (queue_filling(q) + stack_filling(s));
    if(max > 3){
        srand(time(NULL));
        int sort = rand() % 50;
        int i = 0;
        for(int j = 0 ; j < sort ; j++){
            i++;
            if(i >= max){
                i = 0;
            }
        }
        if(i >= stack_filling(s)){
            carro *c =  q_item_getter(travel_queue(q , (i - stack_filling(s))));
            if(descontoGetter(c) == 0) applyDiscount(c , 0.1 * (precoGetter(c)));
        }else{
            carro *c =  s_item_getter(travel_stack(s , i));
            if(descontoGetter(c) == 0) applyDiscount(c , 0.1 * (precoGetter(c)));
        }
    }
}

// Define o carro e insere, se possível, no estacionamento
int carro_checkin(queue *q, stack *s , int verbose) {
    int placa, chegada, saida, preco;
    printf("Placa: \n");
    scanf("%d", &placa);
    printf("Chegada: \n");
    scanf("%d", &chegada);
    printf("Horas: \n");
    scanf(" %d", &saida);
    preco = 3*saida;
    saida += chegada;
    carro *c = carro_cria(placa, chegada, saida, preco, 0);
    if(stack_search(s, c) || queue_search(q, c)) {
        printf("Carro já estacionado!\n");
        return 0;
    }

    carro_checkout(c , q , s);
    sorteio(s , q);
    int rejeicao = carro_rejeicao(c , q , s , verbose);
    if(rejeicao == 1) {
        stack_pile(s, c);
        return 1;
    }else if(rejeicao == 2){
        queue_insert(q, c);
        return 1;
    }
    printf("Carro rejeitado!\n");
    return 0;

}

//Imprime todos os carros no estacionamento, imprimindo primeiro o pátio 1 (stack)
void print_estacionamento(stack *s , queue *q){
    printf("Pátio 1:\n");
    print_stack(s);
    printf("Pátio 2:\n");
    print_queue(q);
}


//Menu para o usuário interagir
int main() {
    printf("Opçoes de verbose?\n[1/0]");
    int verbose;
    scanf("%d", &verbose);
    int option;
    stack *e1 = create_stack(5, verbose);
    queue *e2 = create_queue(10, verbose);
    char exit , lixo;
    while (1){
        option = 0;
        printf("+-------------------------------------+\n");
        printf("|     Cadastro do estacionamento      |\n");
        printf("|                                     |\n");
        printf("| Selecione uma opção:                |\n");
        printf("| 1 -> Cadastrar um novo carro        |\n");
        printf("| 2 -> Ver carros já estacionados     |\n");
        printf("| 3 -> Fechar programa                |\n");
        printf("|                                     |\n");
        printf("+-------------------------------------+\n");
        scanf("%d" , &option);
        switch(option){
            case 1:
                carro_checkin(e2 , e1 , verbose);
                break;
            case 2:
                print_estacionamento(e1 , e2);
                break;
            case 3:
                printf("Deseja realmente sair do programa? [y/n]\n");
                fflush(stdin);
                scanf(" %c" , &exit);
                if(exit == 'y'){
                    erase_queue(e2);
                    erase_stack(e1);
                    return (0);
                }
                break;
            default:
            printf("Opção inválida!\n");
        }
        printf("Pressione enter para continuar\n");
        lixo = getchar();
        lixo = getchar();
    }
    

    return 0;
}
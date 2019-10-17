#include "stack.h"
#include "queue.h"


#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x));

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

    carro *c = carro_cria(placa, chegada, saida, 0);
    if(stack_search(s, c) || queue_search(q, c)) {
        printf("Carro já estacionado!\n");
        return 0;
    }

    carro_checkout(c , q , s);
    int rejeicao = carro_rejeicao(c , q , s);
    if(rejeicao == 1) {
        stack_pile(s, c);
        return 1;
    }else if(rejeicao == 2){
        queue_insert(q, c);
        return 1;
    }

    return 0;

}

// Imprime os dados e remove os carros expirados em relacao ao novo carro
int carro_checkout(carro *c, queue *q, stack *s) {
    while(1) {
        if(getterSaida(queue_HEAD(q)) <= getterChegada(c)) {
            carro_imprime(queue_next(q));
        } else break;
    }

    while(1) {
        if(getterSaida(stack_top(s)) <= getterChegada(c)) {
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

//--------------------------------------------------------------------------------------------------------------------------------------------
void print_estacionamento(stack *s , queue *q){
    printf("Pátio 1:\n");
    print_stack(s);
    printf("Pátio 2:\n");
    print_queue(q);
}



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
        printf("| Opção:                              |\n");
        printf("+-------------------------------------+\n");
        gotoxy(2,9);
        scanf("%d" , &option);
        clear();
        switch(option){
            case 1:
                carro_checkin(e2 , e1);
                break;
            case 2:
                print_estacionamento(e1 , e2);
                break;
            case 3:
                printf("Deseja realmente sair do programa? [y/n]\n");
                scanf("%c" , &exit);
                if(exit == 'y'){
                    erase_queue(e2);
                    erase_stack(e1);
                    return 0;
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
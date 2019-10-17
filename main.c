#include "stack.h"
#include "queue.h"

// Imprime os dados e remove os carros expirados em relacao ao novo carro
int carro_checkout(carro *c, queue *q, stack *s) {
    
}

// Retorna em qual patio o carro deve parar, se possivel
int carro_disponibilidade(carro *c, queue *q, stack *s) {
    if (empty_queue(q) == 1 && empty_stack(s) == 1) return 1;

    if (empty_queue(q) == 0 && empty_stack(s) == 1) return 2;

    if (empty_queue(q) == 1 && empty_stack(s) == 0) return 1;

    if ((empty_queue(q) == 0 && empty_stack(s) == 0) &&
        (full_queue(q) == 0 || full_stack(s) == 0)) {
            
            if(saidaGetter(c) >= saidaGetter(item_getter(stack_top(s)))) return 1;

            if(saidaGetter(c) >= saidaGetter(item_getter(queue_HEAD(s)))) return 2;
    }
}

// Retorna 1 se o carro for rejeitado, caso contrario, retorna 0
int carro_rejeicao(carro *c, queue *q, stack *s) {
    if ((chegadaGetter(c) < 8 || saidaGetter(c) > 22) || (full_queue(q) || full_stack(s)))
        return 1;
    return 0;
}




int main() {

    return 0;
}
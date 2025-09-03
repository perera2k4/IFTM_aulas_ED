#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAX 5

int pilha[MAX], topo = -1;

void imprimirEstadoPilha() {
    printf("Estado da pilha: [");
    if (topo != -1) {
    	int i;
        for (i = topo; i >= 0; i--) {
            printf("%d", pilha[i]);
            if (i > 0) {
                printf(", ");
            }
        }
    }
    printf("]\n");
    printf("Topo: %d\n\n", topo);
}

void push(int x) {
    printf("-> Chamando push(%d)\n", x);
    if (topo == MAX - 1) {
        printf("Pilha cheia! Nao foi possivel inserir %d.\n", x);
    } else {
        topo++;
        pilha[topo] = x;
        printf("Elemento %d inserido com sucesso.\n", x);
    }
    imprimirEstadoPilha();
}

int pop() {
    printf("-> Chamando pop()\n");
    if (topo == -1) {
        printf("Pilha vazia! Nao ha elementos para remover.\n");
        imprimirEstadoPilha();
        return -1;
    } else {
        int valor = pilha[topo--];
        printf("Elemento %d removido com sucesso.\n", valor);
        imprimirEstadoPilha();
        return valor;
    }
}

int top() {
    printf("-> Chamando top()\n");
    if (topo != -1) {
        printf("Elemento no topo da pilha: %d\n", pilha[topo]);
        return pilha[topo];
    } else {
        printf("Pilha vazia!\n");
        return -1;
    }
}

int isEmpty() {
	printf("-> Chamando isEmpty()\n\n");
	return topo == -1;
}

int main(int argc, char *argv[]) {
    printf("Iniciando a execucao do programa (Pilha)...\n\n");
    
    push(5);
    push(7);
    push(3);
    
    isEmpty();
    
    pop();
    
    top();
    
    push(2);
    push(5);
    push(1);
    push(9);
    
    pop();
    pop();
    
    top();
    
    return 0;
}

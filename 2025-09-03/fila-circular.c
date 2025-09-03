#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAX 5

int fila[MAX], frente = -1, final = -1;

void imprimirEstadoFila() {
    printf("Estado da fila: [");
    if (frente != -1) {
        int i = frente;
        while (1) {
            printf("%d", fila[i]);
            if (i == final) {
                break;
            }
            i = (i + 1) % MAX;
            printf(", ");
        }
    }
    printf("]\n");
    printf("Frente: %d, Final: %d\n\n", frente, final);
}

void enqueue(int x) {
    printf("-> Chamando enqueue(%d)\n", x);
    if ((final + 1) % MAX == frente) {
        printf("Fila cheia! Não é possível inserir %d.\n", x);
    } else {
        if (frente == -1) frente = 0;
        final = (final + 1) % MAX;
        fila[final] = x;
        printf("Elemento %d inserido com sucesso.\n", x);
    }
    imprimirEstadoFila();
}

int dequeue() {
    printf("-> Chamando dequeue()\n");
    if (frente == -1) {
        printf("Fila vazia!\n");
        imprimirEstadoFila();
        return -1;
    } else {
        int valor = fila[frente];
        if (frente == final) {
            frente = -1;
            final = -1;
        } else {
            frente = (frente + 1) % MAX;
        }
        printf("Elemento %d removido com sucesso.\n", valor);
    }
    imprimirEstadoFila();
}

int front() {
    printf("-> Chamando front()\n");
    if (frente != -1) {
        int valor = fila[frente];
        printf("Elemento na frente da fila: %d\n", valor);
        return valor;
    } else {
        printf("Fila vazia!\n");
        return -1;
    }
}

int isEmpty() {
    printf("-> Chamando isEmpty()\n");
    if (frente == -1) {
        printf("Fila está vazia.\n");
        return 1;
    } else {
        printf("Fila não está vazia.\n");
        return 0;
    }
}

int main(int argc, char *argv[]) {
    printf("Iniciando a execução do programa (Fila Circular)...\n\n");
    
    enqueue(5);
    enqueue(7);
    enqueue(3);
    
    isEmpty();
    
    dequeue();
    
    front();
    
    enqueue(2);
    enqueue(5);
    enqueue(4);
    
    front();
    
    enqueue(9);
    
    dequeue();
    
    front();
    
    enqueue(13);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAX 5

int fila[MAX], frente = -1, final = -1;

void imprimirEstadoFila() {
    printf("Estado da fila: [");
    if (frente != -1) {
        int i;
        for (i = frente; i <= final; i++) {
            printf("%d", fila[i]);
            if (i < final) {
                printf(", ");
            }
        }
    }
    printf("]\n");
    printf("Frente: %d, Final: %d\n\n", frente, final);
}


void enqueue(int x) {
    printf("-> Chamando enqueue(%d)\n", x);
    if (final == MAX - 1) {
        printf("Fila cheia! Não é possível inserir %d.\n", x);
    } else {
        if (frente == -1) frente = 0;
        fila[++final] = x;
        printf("Elemento %d inserido com sucesso.\n", x);
    }
    imprimirEstadoFila();
}

int dequeue() {
    printf("-> Chamando dequeue()\n");
    if (frente == -1 || frente > final) {
        printf("Fila vazia!\n");
        imprimirEstadoFila();
        return -1;
    } else {
        int valorRemovido = fila[frente++];
        printf("Elemento %d removido com sucesso.\n", valorRemovido);
        imprimirEstadoFila();
        return valorRemovido;
    }
}

int front() {
    printf("-> Chamando front()\n");
    if (frente == -1 || frente > final) {
        printf("Fila vazia!\n");
        return -1;
    }
    int valorFrente = fila[frente];
    printf("Elemento na frente da fila: %d\n", valorFrente);
    return valorFrente;
}

int isEmpty() {
    printf("-> Chamando isEmpty()\n");
    if (frente == -1 || frente > final) {
        printf("Fila está vazia.\n");
        return 1;
    } else {
        printf("Fila não está vazia.\n");
        return 0;
    }
}

int main(int argc, char *argv[]) {   
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

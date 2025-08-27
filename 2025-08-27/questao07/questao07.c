#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int somaNaturais(int n) {
    // Caso Base: Se n for 0 ou 1, a soma é o próprio n.
    if (n <= 1) {
        return n;
    }

    // Passo Recursivo:
    // A soma de n é n mais a soma de todos os números antes dele (n-1).
    return n + somaNaturais(n - 1);
}

int main(int argc, char *argv[]) {
    int numero;

    printf("Digite um numero natural (n >= 0): ");
    scanf("%d", &numero);

    if (numero < 0) {
        printf("Erro: O numero deve ser positivo.\n");
    } else {
        int resultado = somaNaturais(numero);
        printf("A soma dos primeiros %d numeros naturais e: %d\n", numero, resultado);
    }

    return 0;
}
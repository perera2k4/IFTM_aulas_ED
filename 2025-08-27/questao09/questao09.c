#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int quadradoSoma(int n) {
    // Caso Base: O quadrado de 0 é 0 e o de 1 é 1.
    if (n <= 1) {
        return n;
    }

    // Passo Recursivo: Aplica a fórmula: quadrado(n) = quadrado(n-1) + (n-1) + n
    return quadradoSoma(n - 1) + (n - 1) + n;
}

int main(int argc, char *argv[]) {
    int numero;

    printf("Digite um numero inteiro positivo (n): ");
    scanf("%d", &numero);

    if (numero < 0) {
        printf("Erro: O numero deve ser positivo.\n");
    } else {
        int resultado = quadradoSoma(numero);
        printf("O valor de %d ao quadrado e: %d\n", numero, resultado);
    }

    return 0;
}
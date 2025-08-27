#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int encontrarMaior(int vetor[], int tamanho) {
	// Caso Base: Se o vetor tem apenas um elemento, ele é o maior.
    if (tamanho == 1) { 
        return vetor[0];
    }

    // Passo Recursivo:
    // Encontra o maior elemento no "resto" do vetor (todos exceto o último).
    int maiorDoResto = encontrarMaior(vetor, tamanho - 1);

    // Compara o maior do resto com o último elemento do vetor atual.
    int ultimoElemento = vetor[tamanho - 1];

    if (ultimoElemento > maiorDoResto) {
        return ultimoElemento;
    } else {
        return maiorDoResto;
    }
}

int main(int argc, char *argv[]) {
    int meusNumeros[] = {7, 35, 1, -5, 18};
    int n = sizeof(meusNumeros) / sizeof(meusNumeros[0]);

    if (n > 0) {
        int maiorElemento = encontrarMaior(meusNumeros, n);
        printf("O maior elemento do vetor e: %d\n", maiorElemento);
    } else {
        printf("O vetor esta vazio.\n");
    }

    return 0;
}
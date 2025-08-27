#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void inverterVetor(int vetor[], int tamanho) {
	// Caso Base: Se o tamanho for 0, a recursão para.
    if (tamanho == 0) {
        return;
    }
    
    // Passo Recursivo:
    // Imprime o último elemento do trecho atual do vetor.
    printf("%d ", vetor[tamanho - 1]);
    
    // 2. Chama a função para o resto do vetor.
    inverterVetor(vetor, tamanho - 1);
}

int main(int argc, char *argv[]) {
    int meusNumeros[] = {7, 35, 1, -5, 18};
    int n = sizeof(meusNumeros) / sizeof(meusNumeros[0]);

    printf("Vetor inverso: ");
    inverterVetor(meusNumeros, n);
    printf("\n");

    return 0;
}

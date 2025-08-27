#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int serie_s(int n) {
    // Casos Base: são as condições de parada da recursão.
    if (n == 0) {
        return 3;
    } 
    if (n == 1) {
        return 5;
    }

    // s(n) = s(n -1) * 2, para n = 2 e n = 8; 
    if (n >= 2 && n <= 8) {
        return serie_s(n - 1) * 2;
    } 
    
    // s(n) = s(n -1) *3, para n = 9. 
    return serie_s(n - 1) * 3;
}

int main(int argc, char *argv[]) {
    int termo;

    printf("Digite o numero do termo (n) que deseja calcular (n >= 0): ");
    scanf("%d", &termo);

    if (termo < 0) {
        printf("O numero do termo deve ser positivo.\n");
    } else {
        int resultado = serie_s(termo);
        printf("O valor de s(%d) e: %lld\n", termo, resultado);
    }

    return 0;
}
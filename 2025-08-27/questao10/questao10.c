#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

unsigned int contador_movimentos = 0;

void hanoi(int n, char primeira, char terceira, char segunda) {
    if (n <= 0) return; // nada a mover

    if (n == 1) {
        printf("Mova o disco 1 da torre %c para a torre %c\n", primeira, terceira);
        contador_movimentos++;
        return;
    }

    // Passo 1: mover n-1 discos da primeira para a auxiliar
    hanoi(n - 1, primeira, segunda, terceira);

    // Passo 2: mover o disco n
    printf("Mova o disco %d da torre %c para a torre %c\n", n, primeira, terceira);
    contador_movimentos++;

    // Passo 3: mover n-1 discos da auxiliar para a terceira
    hanoi(n - 1, segunda, terceira, primeira);
}

int main(int argc, char *argv[]) {
	int num_discos;
	
	printf("Quantidade de discos: ");
	scanf("%d", &num_discos);
	printf("\n");
    
    char primeiraTorre = 'A';
    char segundaTorre  = 'B';
    char terceiraTorre = 'C';

    hanoi(num_discos, primeiraTorre, terceiraTorre, segundaTorre);
    printf("\nTotal de movimentos: %d\n", contador_movimentos);

    return 0;
}

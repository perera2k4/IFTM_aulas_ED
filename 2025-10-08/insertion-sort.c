#include <stdio.h>
#include <stdlib.h>

// Determina uma chave
typedef int ChaveTipo;

// Cria um tipo Item referenciando a chave
typedef struct {
	ChaveTipo Chave;
} Item;

// Insertion-sort
void Insercao (Item v[], int n ) {
	int i,j;
	Item aux;
	for (i = 1; i < n; i++) {
		aux = v[i]; // 'aux' armazena o valor a ser inserido
		j = i - 1; // 'j' indica a ultima carta ordenada
		while (( j >= 0 ) && (v[j].Chave > aux.Chave)) {
			v[j + 1] = v[j]; // movimentando os elementos
			j--;
		}
		v[j + 1] = aux;
	}
}

int main(int argc, char *argv[]) {
    
    return 0;
}


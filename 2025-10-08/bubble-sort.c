#include <stdio.h>
#include <stdlib.h>

// Determina uma chave
typedef int ChaveTipo;

// Cria um tipo Item referenciando a chave
typedef struct {
	ChaveTipo Chave;
} Item;

// Bubble-sort
void Bolha (Item v[], int n ) {
    int i, j;
    Item aux;
    for( i = 0 ; i < n-1 ; i++ ) {
        for( j = 0; j < n - i-1 ; j++ ) {
            if (v[j].Chave > v[j + 1].Chave) {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
	}
}

int main(int argc, char *argv[]) {

    return 0;
}

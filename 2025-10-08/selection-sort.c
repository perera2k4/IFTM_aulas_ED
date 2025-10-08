#include <stdio.h>
#include <stdlib.h>

// Determina uma chave
typedef int ChaveTipo;

// Cria um tipo Item referenciando a chave
typedef struct {
	ChaveTipo Chave;
} Item;

// Selection-sort
void Selecao (Item v[], int n) { 
    int i, j, Min; 
    Item aux;
    for (i = 0; i < n - 1; i++) { 
    	Min = i; // 'Min' da a posicao do menor elemento
        for (j = i + 1 ; j < n; j++) { 
            if (v[j].Chave < v[Min].Chave) {
                Min = j;
                aux = v[Min];
                v[Min] = v[i];
                v[i] = aux;
        	}
    	}
    }
}

int main(int argc, char *argv[]) {
    
    return 0;
}


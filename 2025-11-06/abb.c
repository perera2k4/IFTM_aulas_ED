#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;  //chave de busca
    //outros campos de informa��o
    struct No* esquerda;
    struct No* direita;
} No;

// Fun��o para criar um novo n� da ABB, retorna um ponteiro para o mesmo
No* criaNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->chave = valor;
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

// Fun��o para inserir um n� na ABB, retorna um ponteiro para a raiz
No* insere(No* raiz, int valor) {
    if (raiz == NULL)
        return criaNo(valor);
    if (valor < raiz->chave) {
	    raiz->esquerda = insere(raiz->esquerda, valor);
	    return raiz;
    }
    else 
	    if (valor > raiz->chave) {
		    raiz->direita = insere(raiz->direita, valor);
		    return raiz;
	    }
	    else // o valor j� existe na ABB, somente retornar a raiz
	        return raiz; // Retorna a raiz para manter a �rvore conectada
}

// Fun��o para busca pela chave valor na ABB
No* busca(No* raiz, int valor) {
    if (raiz == NULL || raiz->chave == valor)
        return raiz; // Retorna o n� se encontrado ou NULL se n�o existir
    if (valor < raiz->chave)
        return busca(raiz->esquerda, valor);
    else
        return busca(raiz->direita, valor);
}

// Fun��o auxiliar para encontrar o menor valor em uma sub�rvore
No* menorValor(No* raiz) {
    No* atual = raiz;
    //Enquanto o n� atual n�o for NULL e 
    //possuir um filho a esquerda
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Fun��o para remover um n� da ABB cuja chave � valor e 
// retorna a raiz da ABB atualizada ap�s a remo��o
No* removeNo(No* raiz, int valor) {
    if (raiz == NULL) // Caso base: �rvore vazia ou n� a ser
        return raiz;  // removido n�o foi encontrado.

    // Busca o n� a ser removido
    if (valor < raiz->chave) //Buscar na sub�rvore esquerda
        raiz->esquerda = removeNo(raiz->esquerda, valor);
    else if (valor > raiz->chave) //Buscar na sub�rvore direita
        raiz->direita = removeNo(raiz->direita, valor);
    else { // N� foi encontrado
        // Caso 1: N� sem filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: N� com apenas um filho
        else if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // Caso 3: N� com dois filhos
        No* temp = menorValor(raiz->direita); // Encontra o menor valor da sub�rvore direita
        raiz->chave = temp->chave; // Substitui o valor do n� pelo sucessor
        raiz->direita = removeNo(raiz->direita, temp->chave); // Remove o sucessor
    }
    return raiz;
}

// Fun��o para imprimir a �rvore em ordem
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        emOrdem(raiz->direita);
    }
}

int main() {
    No* raiz = NULL;

    // Inser��o de valores na �rvore
    raiz = insere(raiz, 50);
    raiz = insere(raiz, 30);
    raiz = insere(raiz, 20);
    raiz = insere(raiz, 40);
    raiz = insere(raiz, 70);
    raiz = insere(raiz, 60);
    raiz = insere(raiz, 80);

    printf("Arvore Em-Ordem antes da remocao: ");
    emOrdem(raiz);
    printf("\n");

    // Busca de um valor
    int chaveBusca = 40;
    No* resultadoBusca = busca(raiz, chaveBusca);
    if (resultadoBusca != NULL)
        printf("Chave %d encontrada na arvore.\n", chaveBusca);
    else
        printf("Chave %d nao encontrada na arvore.\n", chaveBusca);

    // Remo��o de valores
    raiz = removeNo(raiz, 20); // Removendo um n� folha
    raiz = removeNo(raiz, 50); // Removendo a raiz com dois filhos
    raiz = removeNo(raiz, 30); // Removendo um n� com um filho
   
    printf("Arvore Em-Ordem apos remocoes: ");
    emOrdem(raiz);
    printf("\n");

    return 0;
}

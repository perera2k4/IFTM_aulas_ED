#include <stdio.h>
#include <stdlib.h>

// Estrutura do no da lista duplamente ligada
typedef struct No {
    int dado;
    struct No* anterior;
    struct No* proximo;
} No;

// Estrutura da lista duplamente ligada
typedef struct {
    No* cabeca;
    No* cauda;
} ListaDuplamenteLigada;

// Funcao para inicializar a lista
void inicializarLista(ListaDuplamenteLigada* lista) {
    lista->cabeca = NULL;
    lista->cauda = NULL;
}

// Funcao para criar um novo no
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro de alocacao de memoria!\n");
        return NULL;
    }
    novoNo->dado = dado;
    novoNo->anterior = NULL;
    novoNo->proximo = NULL;
    return novoNo;
}

// Funcao para inserir um no no inicio da lista
void inserirNoInicio(ListaDuplamenteLigada* lista, int dado) {
    No* novoNo = criarNo(dado);
    if (lista->cabeca == NULL) {  // Se a lista estiver vazia
        lista->cabeca = lista->cauda = novoNo;
    } else {
        novoNo->proximo = lista->cabeca;
        lista->cabeca->anterior = novoNo;
        lista->cabeca = novoNo;
    }
}

// Funcao para inserir um no no final da lista
void inserirNoFim(ListaDuplamenteLigada* lista, int dado) {
    No* novoNo = criarNo(dado);
    if (lista->cauda == NULL) {  // Se a lista estiver vazia
        lista->cabeca = lista->cauda = novoNo;
    } else {
        novoNo->anterior = lista->cauda;
        lista->cauda->proximo = novoNo;
        lista->cauda = novoNo;
    }
}

// Funcao para remover o primeiro no da lista
void removerDoInicio(ListaDuplamenteLigada* lista) {
    if (lista->cabeca == NULL) {
        printf("Erro: Lista esta vazia!\n");
        return;
    }
    No* temporario = lista->cabeca;
    if (lista->cabeca == lista->cauda) {  // Se houver apenas um elemento
        lista->cabeca = lista->cauda = NULL;
    } else {
        lista->cabeca = lista->cabeca->proximo;
        lista->cabeca->anterior = NULL;
    }
    free(temporario);
}

// Funcao para remover o ultimo no da lista
void removerDoFim(ListaDuplamenteLigada* lista) {
    if (lista->cauda == NULL) {
        printf("Erro: Lista esta vazia\n");
        return;
    }
    No* temporario = lista->cauda;
    if (lista->cabeca == lista->cauda) {  // Se houver apenas um elemento
        lista->cabeca = lista->cauda = NULL;
    } else {
        lista->cauda = lista->cauda->anterior;
        lista->cauda->proximo = NULL;
    }
    free(temporario);
}

// Funcao para buscar um valor na lista
No* buscar(ListaDuplamenteLigada* lista, int valor) {
    No* temporario = lista->cabeca;
    while (temporario != NULL) {
        if (temporario->dado == valor) {
            return temporario;  // Valor encontrado
        }
        temporario = temporario->proximo;
    }
    return NULL;  // Valor nao encontrado
}

// Funcao para exibir a lista do inicio ao fim
void exibirParaFrente(ListaDuplamenteLigada* lista) {
    No* temporario = lista->cabeca;
    printf("Lista (cabeca para cauda): ");
    while (temporario != NULL) {
        printf("%d ", temporario->dado);
        temporario = temporario->proximo;
    }
    printf("\n");
}

// Funcao para exibir a lista do fim ao inicio
void exibirParaTras(ListaDuplamenteLigada* lista) {
    No* temporario = lista->cauda;
    printf("Lista (cauda para cabeca): ");
    while (temporario != NULL) {
        printf("%d ", temporario->dado);
        temporario = temporario->anterior;
    }
    printf("\n");
}

// Operacao adicional: insere um no em uma posicao especifica
void inserirNaPosicao(ListaDuplamenteLigada* lista, int dado, int posicao) {
    if (posicao < 0) {
        printf("Posicao invalida.\n");
        return;
    }
    if (posicao == 0) {
        inserirNoInicio(lista, dado);
        return;
    }
    No* novoNo = criarNo(dado);
    No* atual = lista->cabeca;
    int i = 0;
    while (atual != NULL && i < posicao) {
        atual = atual->proximo;
        i++;
    }
    if (atual == NULL && i == posicao) { // Inserir no final
        inserirNoFim(lista, dado);
    } else if (atual != NULL) {
        novoNo->proximo = atual;
        novoNo->anterior = atual->anterior;
        atual->anterior->proximo = novoNo;
        atual->anterior = novoNo;
    } else {
        printf("Posicao fora dos limites da lista.\n");
        free(novoNo);
    }
}

// Programa principal
int main() {
    ListaDuplamenteLigada lista;
    inicializarLista(&lista);

    inserirNoFim(&lista, 10);
    inserirNoFim(&lista, 20);
    inserirNoFim(&lista, 30);
    exibirParaFrente(&lista);

    // Inserindo um no na posicao 1 (depois do 10, antes do 20)
    inserirNaPosicao(&lista, 15, 1);
    exibirParaFrente(&lista);

    // Inserindo um no na posicao 0
    inserirNaPosicao(&lista, 5, 0);
    exibirParaFrente(&lista);

    // Inserindo um no no final da lista
    inserirNaPosicao(&lista, 40, 5);
    exibirParaFrente(&lista);

    return 0;
}

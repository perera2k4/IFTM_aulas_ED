#include <stdio.h>
#include <stdlib.h>

// Estrutura do no da lista circular
typedef struct No {
    int dado;
    struct No* proximo;
} No;

// Estrutura da lista circular
typedef struct {
    No* cabeca;
} ListaCircularLigada;

// Função para inicializar a lista
void inicializarLista(ListaCircularLigada* lista) {
    lista->cabeca = NULL;
}

// Função para criar um novo nó
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro de alocacao de memoria\n");
        return NULL;
    }
    novoNo->dado = dado;
    novoNo->proximo = novoNo;  // O nó aponta para si mesmo
    return novoNo;
}

// Função para inserir um nó no início da lista
void inserirNoInicio(ListaCircularLigada* lista, int dado) {
    No* novoNo = criarNo(dado);
    if (lista->cabeca == NULL) {  // Se a lista estiver vazia
        lista->cabeca = novoNo;
    } else {
        No* temporario = lista->cabeca;
        while (temporario->proximo != lista->cabeca) {
            temporario = temporario->proximo;
        }
        temporario->proximo = novoNo;
        novoNo->proximo = lista->cabeca;
        lista->cabeca = novoNo;
    }
}

// Função para inserir um nó no final da lista
void inserirNoFim(ListaCircularLigada* lista, int dado) {
    No* novoNo = criarNo(dado);
    if (lista->cabeca == NULL) {  // Se a lista estiver vazia
        lista->cabeca = novoNo;
    } else {
        No* temporario = lista->cabeca;
        while (temporario->proximo != lista->cabeca) {
            temporario = temporario->proximo;
        }
        temporario->proximo = novoNo;
        novoNo->proximo = lista->cabeca;
    }
}

// Função para remover um nó do início da lista
void removerDoInicio(ListaCircularLigada* lista) {
    if (lista->cabeca == NULL) {
        printf("Erro: Lista esta vazia!\n");
        return;
    }
    No* temporario = lista->cabeca;
    if (temporario->proximo == lista->cabeca) {  // Se houver apenas um nó
        free(temporario);
        lista->cabeca = NULL;
    } else {
        No* ultimo = lista->cabeca;
        while (ultimo->proximo != lista->cabeca) {
            ultimo = ultimo->proximo;
        }
        lista->cabeca = lista->cabeca->proximo;
        ultimo->proximo = lista->cabeca;
        free(temporario);
    }
}

// Função para remover um nó do final da lista
void removerDoFim(ListaCircularLigada* lista) {
    if (lista->cabeca == NULL) {
        printf("Erro: Lista esta vazia!\n");
        return;
    }
    No* temporario = lista->cabeca;
    if (temporario->proximo == lista->cabeca) {  // Se houver apenas um nó
        free(temporario);
        lista->cabeca = NULL;
    } else {
        No* anterior = NULL;
        while (temporario->proximo != lista->cabeca) {
            anterior = temporario;
            temporario = temporario->proximo;
        }
        anterior->proximo = lista->cabeca;
        free(temporario);
    }
}

// Função para buscar um valor na lista circular
No* buscar(ListaCircularLigada* lista, int valor) {
    if (lista->cabeca == NULL) {
        return NULL;
    }
    No* temporario = lista->cabeca;
    do {
        if (temporario->dado == valor) {
            return temporario;  // Valor encontrado
        }
        temporario = temporario->proximo;
    } while (temporario != lista->cabeca);
    return NULL;  // Valor nao encontrado
}

// Função para exibir a lista circular
void exibirLista(ListaCircularLigada* lista) {
    if (lista->cabeca == NULL) {
        printf("Lista esta vazia.\n");
        return;
    }
    No* temporario = lista->cabeca;
    printf("Lista Circular: ");
    do {
        printf("%d ", temporario->dado);
        temporario = temporario->proximo;
    } while (temporario != lista->cabeca);
    printf("\n");
}

// Operacao adicional: conta o numero de nos na lista circular
int contarNos(ListaCircularLigada* lista) {
    if (lista->cabeca == NULL) {
        return 0;
    }
    int contador = 0;
    No* temporario = lista->cabeca;
    do {
        contador++;
        temporario = temporario->proximo;
    } while (temporario != lista->cabeca);
    return contador;
}

// Programa principal
int main() {
    ListaCircularLigada lista;
    inicializarLista(&lista);

    inserirNoFim(&lista, 10);
    inserirNoFim(&lista, 20);
    inserirNoFim(&lista, 30);
    exibirLista(&lista);

    // Contando os nos da lista
    printf("Numero de nos na lista: %d\n", contarNos(&lista));

    inserirNoInicio(&lista, 5);
    exibirLista(&lista);
    printf("Numero de nos na lista: %d\n", contarNos(&lista));

    removerDoInicio(&lista);
    exibirLista(&lista);
    printf("Numero de nos na lista: %d\n", contarNos(&lista));

    removerDoFim(&lista);
    exibirLista(&lista);
    printf("Numero de nos na lista: %d\n", contarNos(&lista));

    return 0;
}

// Implementacao de Lista Simplesmente Ligada Dinamica

#include <stdio.h>
#include <stdlib.h>

// Definicao da estrutura de um no
typedef struct No {
    int dado;           // Dado
    struct No* proximo;  // Ponteiro para o proximo no
} No;

// Funcao para inicializar a lista (ponteiro para a cabeca da lista)
void inicializarLista(No** cabeca) {
    *cabeca = NULL;
}

// Funcao para criar um novo no
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    return 
}

// Funcao para inserir um no no inicio da lista
void inserirNoInicio(No** cabeca, int dado) {
    No* novoNo = criarNo(dado);
    novoNo->proximo = *cabeca;
    *cabeca = novoNo;
}

// Funcao para inserir um no no final da lista
void inserirNoFim(No** cabeca, int dado) {
    No* novoNo = criarNo(dado);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        No* temporario = *cabeca;
        while (temporario->proximo != NULL) {
            temporario = temporario->proximo;
        }
        temporario->proximo = novoNo;
    }
}

// Funcao para remover um no no inicio da lista
void removerDoInicio(No** cabeca) {
    if (*cabeca == NULL) {
        printf("Erro: Lista esta vazia!\n");
        return;
    }
    No* temporario = *cabeca;
    *cabeca = (*cabeca)->proximo;
    free(temporario);
}

// Funcao para remover um no no final da lista
void removerDoFim(No** cabeca) {
    if (*cabeca == NULL) {
        printf("Erro: Lista esta vazia!\n");
        return;
    }
    if ((*cabeca)->proximo == NULL) {
        free(*cabeca);
        *cabeca = NULL;
    } else {
        No* temporario = *cabeca;
        while (temporario->proximo->proximo != NULL) {
            temporario = temporario->proximo;
        }
        free(temporario->proximo);
        temporario->proximo = NULL;
    }
}

// Funcao para exibir os elementos da lista
void exibirLista(No* cabeca) {
    if (cabeca == NULL) {
        printf("Lista esta vazia.\n");
        return;
    }
    No* temporario = cabeca;
    while (temporario != NULL) {
        printf("%d -> ", temporario->dado);
        temporario = temporario->proximo;
    }
    printf("NULL\n");
}

// Funcao para buscar um valor na lista
No* buscar(No* cabeca, int chave) {
    No* temporario = cabeca;
    while (temporario != NULL) {
        if (temporario->dado == chave) {
            return temporario;  // Elemento encontrado
        }
        temporario = temporario->proximo;
    }
    return NULL;  // Elemento nao encontrado
}

// Operacao adicional: remove o primeiro no que contem o valor especificado
void removerPorValor(No** cabeca, int valor) {
    if (*cabeca == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }
    No* atual = *cabeca;
    No* anterior = NULL;
    // Percorre a lista para encontrar o no com o valor
    while (atual != NULL && atual->dado != valor) {
        anterior = atual;
        atual = atual->proximo;
    }
    // Se o valor nao foi encontrado
    if (atual == NULL) {
        printf("Valor %d nao encontrado na lista.\n", valor);
        return;
    }
    // Se o no a ser removido e a cabeca da lista
    if (anterior == NULL) {
        *cabeca = atual->proximo;
    } else {
        // Remove o no da lista
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Valor %d removido da lista.\n", valor);
}

// Funcao principal para testar as operacoes
int main() {
    No* cabeca;

    // Inicializando a lista
    inicializarLista(&cabeca);

    // Inserindo valores na lista
    inserirNoInicio(&cabeca, 10);
    inserirNoInicio(&cabeca, 20);
    inserirNoFim(&cabeca, 30);
    inserirNoFim(&cabeca, 40);

    printf("Lista Simplesmente Ligada! \n\n");
    printf("Lista apos insercoes: ");
    exibirLista(cabeca);

    // Removendo um valor especifico
    removerPorValor(&cabeca, 20);
    printf("Lista apos remover o valor 20: ");
    exibirLista(cabeca);

    removerPorValor(&cabeca, 40);
    printf("Lista apos remover o valor 40: ");
    exibirLista(cabeca);

    // Tentando remover um valor que nao existe
    removerPorValor(&cabeca, 99);

    return 0;
}

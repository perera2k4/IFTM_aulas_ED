#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#define TABLE_SIZE 10
#define A_CONSTANT 0.618033

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE]; // a tabela hash e um array de ponteiros para nos (listas encadeadas)

int hashFunction(int key) { // metodo da multiplicacao
    double temp;
    double fractionalPart;
    int hashIndex;

    // formula: hashIndex = floor(TamanhoTabela * (chave * A mod 1))
    temp = (double)key * A_CONSTANT; // 1. Multiplica a chave pela constante A
    fractionalPart = fmod(temp, 1.0); // extrai a parte decimal: fmod(x, 1.0) retorna a parte fracionaria
    temp = fractionalPart * TABLE_SIZE; // multiplica a parte decimal pelo Tamanho da Tabela
    hashIndex = (int)floor(temp); // aproxima o valor para obter o indice inteiro

    return hashIndex;
}

void insert(int key, int value) { // insercao na tabela hash (insere sempre no inicio da lista encadeada)
    int hashIndex = hashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[hashIndex]; // o novo no aponta para a cabeca atual da lista
    hashTable[hashIndex] = newNode; // a cabeca da lista e atualizada para o novo no
}

int search(int key) { // busca na tabela hash
    int hashIndex = hashFunction(key);
    Node* current = hashTable[hashIndex];
    
    while (current) { // percorre a lista encadeada no indice hash
        if (current->key == key) {
            return current->value; // chave encontrada
        }
        current = current->next;
    }
    return -1; // nao encontrado
}

int removeNode(int key) { // remocao na tabela hash
    int hashIndex = hashFunction(key);
    Node* current = hashTable[hashIndex];
    Node* prev = NULL;

    while (current != NULL) { // percorre a lista para encontrar a chave
        if (current->key == key) {
            if (prev == NULL) { // e o primeiro no da lista
                hashTable[hashIndex] = current->next; // a cabeca da lista e atualizada para o proximo no
            } else {
                prev->next = current->next; // o no anterior aponta para o proximo do no atual
            }
            free(current); // libera a memoria
            return 1; // sucesso na remocao
        }
        prev = current;
        current = current->next;
    }
    return 0; // chave nao encontrada
}


void displayTable() { // print da tabela hash
    int i;
    printf("\nIndice | Elementos\n");
    printf("------|-------------------------------------------------\n");
	for (i = 0; i < TABLE_SIZE; i++) {
        printf("[%2d]  | ", i);
        Node* current = hashTable[i];
        while (current) {
            printf("(Key: %d, Value: %d)", current->key, current->value);
            if (current->next != NULL) {
                printf(" -> ");
            }
            current = current->next;
        }
        printf(" -> NULL\n");
    }
    printf("-------------------------------------------------\n");
}

void freeTable() { // funcao para liberar toda a memoria alocada
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        Node *current = hashTable[i];
        Node *next;
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
        hashTable[i] = NULL;
    }
}

int main() {
    int i; 
    
	for (i = 0; i < TABLE_SIZE; i++) { // inicializando todos os elementos da tabela hash com NULL
        hashTable[i] = NULL;
    }
    printf("--- Tabela Hash: Metodo da Multiplicacao ---\n");
    printf("Inserindo elementos (TABLE_SIZE=10):\n");
    
    // insercoes que colidiam no Metodo da Divisao (1, 11, 21)
	insert(1, 10);
    insert(11, 20);
    insert(21, 30);
    insert(2, 15);
    insert(32, 45); 
    insert(42, 55); 

    displayTable();

    int key_search_success = 11; // teste de Busca
    int value = search(key_search_success);
    if (value != -1) {
        printf("Busca: Valor encontrado para a chave %d: %d\n", key_search_success, value);
    } else {
        printf("Busca: Chave %d nao encontrada.\n", key_search_success);
    }

    int key_search_fail = 99;
    value = search(key_search_fail);
    if (value != -1) {
        printf("Busca: Valor encontrado para a chave %d: %d\n", key_search_fail, value);
    } else {
        printf("Busca: Chave %d nao encontrada.\n", key_search_fail);
    }

    int key_to_remove = 1; // teste de remocao
    if (removeNode(key_to_remove)) {
        printf("\nRemocao: Chave %d removida com sucesso.\n", key_to_remove);
    } else {
        printf("\nRemocao: Chave %d nao encontrada para remocao.\n", key_to_remove);
    }
    
    int key_to_remove_fail = 99; // remocao de uma chave que nao existe
    if (removeNode(key_to_remove_fail)) {
        printf("Remocao: Chave %d removida com sucesso.\n", key_to_remove_fail);
    } else {
        printf("Remocao: Chave %d nao encontrada para remocao.\n", key_to_remove_fail);
    }

    printf("\nTabela Hash Apos Remocao da Chave %d:\n", key_to_remove);
    displayTable();

    
    freeTable(); // zerar da memoria
    return 0;
}
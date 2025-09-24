// Implementação de um sistema de gerenciamento de playlists de música - VERSÃO 1 (50%)
// Trabalho 1 - Estrutura de Dados, Professor: Alencar
// Alunos: Bruno Carvalho e Pedro Romão

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 50
#define MAX_ARTIST_LENGTH 50

// --- Módulo Musica.h ---
// Definição da estrutura de um item (Música)
typedef struct Musica {
    int id;
    char titulo[MAX_TITLE_LENGTH];
    char artista[MAX_ARTIST_LENGTH];
    int duracao;
    struct Musica* next;
    struct Musica* prev;
} Musica;

// --- Módulo ListaDuplamenteLigada.c ---
// Estrutura da lista duplamente ligada para a biblioteca
typedef struct {
    Musica* head;
    Musica* tail;
} DoublyLinkedList;

// Função para inicializar a lista
void initializeList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Função para criar um novo nó de música
Musica* createMusicNode(int id, const char* titulo, const char* artista, int duracao) {
    Musica* newNode = (Musica*)malloc(sizeof(Musica));
    if (!newNode) {
        printf("Erro de alocacao de memoria!\n");
        return NULL;
    }
    newNode->id = id;
    strncpy(newNode->titulo, titulo, MAX_TITLE_LENGTH);
    strncpy(newNode->artista, artista, MAX_ARTIST_LENGTH);
    newNode->duracao = duracao;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um nó no final da lista
void insertAtEnd(DoublyLinkedList* list, Musica* newMusic) {
    if (list->tail == NULL) {
        list->head = list->tail = newMusic;
    } else {
        newMusic->prev = list->tail;
        list->tail->next = newMusic;
        list->tail = newMusic;
    }
}

// Função para remover um nó da lista por ID
void removeMusicById(DoublyLinkedList* list, int id) {
    Musica* current = list->head;
    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Musica com ID %d nao encontrada.\n", id);
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;
    }

    free(current);
    printf("Musica com ID %d removida com sucesso.\n", id);
}

// Função para buscar um valor na lista por ID
Musica* searchById(DoublyLinkedList* list, int id) {
    Musica* temp = list->head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Função para exibir a lista do início ao fim
void displayLibrary(DoublyLinkedList* list) {
    Musica* temp = list->head;
    if (temp == NULL) {
        printf("Biblioteca de musicas esta vazia.\n");
        return;
    }
    printf("--- Biblioteca de Musicas ---\n");
    while (temp != NULL) {
        printf("ID: %d, Titulo: %s, Artista: %s, Duracao: %d s\n",
               temp->id, temp->titulo, temp->artista, temp->duracao);
        temp = temp->next;
    }
    printf("------------------------------\n");
}

// --- Módulo Principal ---
int main() {
    DoublyLinkedList library;
    int nextId = 1;

    initializeList(&library);

    int choice, id, duration;
    char title[MAX_TITLE_LENGTH];
    char artist[MAX_ARTIST_LENGTH];
    Musica* foundMusic;

    do {
        printf("\n--- Menu do Reprodutor de Musica (Versao 1) ---\n");
        printf("1. Adicionar nova musica\n");
        printf("2. Remover musica por ID\n");
        printf("3. Exibir todas as musicas\n");
        printf("4. Buscar musica por ID\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("ID: %d\n", nextId);
                printf("Titulo: ");
                getchar(); // Limpar o buffer
                fgets(title, MAX_TITLE_LENGTH, stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Artista: ");
                fgets(artist, MAX_ARTIST_LENGTH, stdin);
                artist[strcspn(artist, "\n")] = 0;
                printf("Duracao (segundos): ");
                scanf("%d", &duration);
                Musica* newMusic = createMusicNode(nextId++, title, artist, duration);
                if (newMusic) {
                    insertAtEnd(&library, newMusic);
                    printf("Musica adicionada com sucesso!\n");
                }
                break;
            case 2:
                printf("Digite o ID da musica a ser removida: ");
                scanf("%d", &id);
                removeMusicById(&library, id);
                break;
            case 3:
                displayLibrary(&library);
                break;
            case 4:
                printf("Digite o ID da musica: ");
                scanf("%d", &id);
                foundMusic = searchById(&library, id);
                if (foundMusic) {
                    printf("Musica encontrada: ID: %d, Titulo: %s, Artista: %s\n", 
                           foundMusic->id, foundMusic->titulo, foundMusic->artista);
                } else {
                    printf("Musica nao encontrada.\n");
                }
                break;
            case 5:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (choice != 5);

    return 0;
}
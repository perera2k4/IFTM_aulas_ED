// Implementacao de um sistema de gerenciamento de playlists de musica
// Trabalho 1 - Estrutura de Dados, Professor: Alencar
// Alunos: Bruno Carvalho e Pedro Romao

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TITLE_LENGTH 50
#define MAX_ARTIST_LENGTH 50
#define FILENAME "musicas.txt"

// Definicao da estrutura do tipo Musica
typedef struct Musica {
    int id;
    char titulo[MAX_TITLE_LENGTH];
    char artista[MAX_ARTIST_LENGTH];
    int duracao;
    int prioridade;
    struct Musica* next;
    struct Musica* prev; // Apenas para a lista duplamente ligada
} Musica;

// Estrutura para a pilha de historico
typedef struct Stack {
    Musica* top;
} Stack;

// Funcao para inicializar a pilha
void initializeStack(Stack* stack) {
    stack->top = NULL;
}

// Funcao para verificar se a pilha esta vazia
int isStackEmpty(Stack* stack) {
    return (stack->top == NULL);
}

// Funcao para empilhar (inserir no topo)
void push(Stack* stack, Musica* musica) {
    Musica* newNode = (Musica*)malloc(sizeof(Musica));
    if (!newNode) {
        printf("Erro de alocacao de memoria na pilha!\n");
        return;
    }
    *newNode = *musica;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Funcao para desempilhar (remover do topo)
Musica* pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Erro: Pilha esta vazia!\n");
        return NULL;
    }
    Musica* temp = stack->top;
    stack->top = stack->top->next;
    temp->next = NULL;
    return temp;
}

// Funcao para retornar o valor do topo sem remove-lo
Musica* topValue(Stack* stack) {
    if (isStackEmpty(stack)) {
        return NULL;
    }
    return stack->top;
}

// Funcao adicional para inverter a pilha (complemento)
void reverseStack(Stack* stack) {
    Stack tempStack;
    initializeStack(&tempStack);
    while (!isStackEmpty(stack)) {
        push(&tempStack, pop(stack));
    }
    stack->top = tempStack.top;
}

// Estrutura para a fila de playlist
typedef struct Queue {
    Musica* front;
    Musica* rear;
} Queue;

// Funcao para inicializar a fila
void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Funcao para verificar se a fila esta vazia
int isQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// Funcao para enfileirar (inserir no final)
void enqueue(Queue* queue, Musica* musica) {
    Musica* newNode = (Musica*)malloc(sizeof(Musica));
    if (!newNode) {
        printf("Erro de alocacao de memoria na fila!\n");
        return;
    }
    *newNode = *musica;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Funcao para desenfileirar (remover do inicio)
Musica* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    Musica* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    temp->next = NULL;
    return temp;
}

// Funcao para retornar o valor do inicio sem remove-lo
Musica* frontValue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    return queue->front;
}

// Funcao adicional para contar musicas com duracao superior a X
int countLongSongs(Queue* queue, int minDuration) {
    int count = 0;
    Musica* temp = queue->front;
    while (temp != NULL) {
        if (temp->duracao > minDuration) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

// Estrutura da lista duplamente ligada para a biblioteca
typedef struct {
    Musica* head;
    Musica* tail;
} DoublyLinkedList;

// Funcao para inicializar a lista duplamente ligada
void initializeList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Funcao para criar um novo no de musica
Musica* createMusicNode(int id, const char* titulo, const char* artista, int duracao, int prioridade) {
    Musica* newNode = (Musica*)malloc(sizeof(Musica));
    if (!newNode) {
        printf("Erro de alocacao de memoria!\n");
        return NULL;
    }
    newNode->id = id;
    strncpy(newNode->titulo, titulo, MAX_TITLE_LENGTH);
    strncpy(newNode->artista, artista, MAX_ARTIST_LENGTH);
    newNode->duracao = duracao;
    newNode->prioridade = prioridade;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Funcao para inserir um no no final da lista
void insertAtEnd(DoublyLinkedList* list, Musica* newMusic) {
    if (list->tail == NULL) {
        list->head = list->tail = newMusic;
    } else {
        newMusic->prev = list->tail;
        list->tail->next = newMusic;
        list->tail = newMusic;
    }
}

// Funcao para remover um no da lista por ID
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

// Funcao para buscar um valor na lista por ID
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

// Funcao para buscar por substring no titulo ou artista
Musica* searchBySubstring(DoublyLinkedList* list, const char* substring) {
    Musica* temp = list->head;
    while (temp != NULL) {
        if (strstr(temp->titulo, substring) || strstr(temp->artista, substring)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Funcao adicional para remover duplicatas
void removeDuplicates(DoublyLinkedList* list) {
    Musica* current = list->head;
    while (current != NULL) {
        Musica* runner = current->next;
        while (runner != NULL) {
            if (strcmp(current->titulo, runner->titulo) == 0 && strcmp(current->artista, runner->artista) == 0) {
                Musica* temp = runner;
                if (runner->next != NULL) {
                    runner->next->prev = runner->prev;
                }
                runner->prev->next = runner->next;
                runner = runner->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
    printf("Duplicatas removidas.\n");
}

// Funcao para exibir a lista do inicio ao fim
void displayLibrary(DoublyLinkedList* list) {
    Musica* temp = list->head;
    if (temp == NULL) {
        printf("Biblioteca de musicas esta vazia.\n");
        return;
    }
    printf("--- Biblioteca de Musicas ---\n");
    while (temp != NULL) {
        printf("ID: %d, Titulo: %s, Artista: %s, Duracao: %d s, Prioridade: %d\n",
               temp->id, temp->titulo, temp->artista, temp->duracao, temp->prioridade);
        temp = temp->next;
    }
    printf("------------------------------\n");
}

// Funcoes de Salvar e Carregar
void saveLibraryToFile(DoublyLinkedList* list) {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    Musica* current = list->head;
    while (current != NULL) {
        fprintf(file, "%d;%s;%s;%d;%d\n",
                current->id, current->titulo, current->artista, current->duracao, current->prioridade);
        current = current->next;
    }

    fclose(file);
    printf("Biblioteca de musicas salva com sucesso em '%s'.\n", FILENAME);
}

void loadLibraryFromFile(DoublyLinkedList* list) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Arquivo de dados nao encontrado. Criando nova biblioteca.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int id, duracao, prioridade;
        char titulo[MAX_TITLE_LENGTH], artista[MAX_ARTIST_LENGTH];

        if (sscanf(line, "%d;%49[^;];%49[^;];%d;%d", &id, titulo, artista, &duracao, &prioridade) == 5) {
            Musica* newMusic = createMusicNode(id, titulo, artista, duracao, prioridade);
            insertAtEnd(list, newMusic);
        }
    }
    fclose(file);
    printf("Biblioteca de musicas carregada com sucesso de '%s'.\n", FILENAME);
}

// --- Modulo Principal ---
int main() {
    DoublyLinkedList library;
    Queue playlist;
    Stack history;
    int nextId = 1;

    initializeList(&library);
    initializeQueue(&playlist);
    initializeStack(&history);
    srand(time(0));

    loadLibraryFromFile(&library);
    if (library.head != NULL) {
        Musica* temp = library.head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        nextId = temp->id + 1;
    }


    int choice, id, duration, priority, minDuration;
    char title[MAX_TITLE_LENGTH];
    char artist[MAX_ARTIST_LENGTH];
    char substring[MAX_TITLE_LENGTH];
    Musica* foundMusic;
    Musica* currentPlaying = NULL;

    do {
        printf("\n--- Menu do Reprodutor de Musica ---\n");
        printf("1. Gerenciar Biblioteca de Musicas\n");
        printf("2. Gerenciar Playlist de Reproducao\n");
        printf("3. Controles de Reproducao\n");
        printf("4. Salvar Biblioteca e Sair\n");
        printf("5. Carregar Biblioteca\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Gerenciar Biblioteca ---\n");
                printf("1. Adicionar nova musica\n");
                printf("2. Remover musica por ID\n");
                printf("3. Exibir todas as musicas\n");
                printf("4. Buscar musica por substring\n");
                printf("5. Remover duplicatas\n");
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
                        printf("Prioridade: ");
                        scanf("%d", &priority);
                        Musica* newMusic = createMusicNode(nextId++, title, artist, duration, priority);
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
                        printf("Digite uma substring para buscar no titulo ou artista: ");
                        getchar();
                        fgets(substring, MAX_TITLE_LENGTH, stdin);
                        substring[strcspn(substring, "\n")] = 0;
                        foundMusic = searchBySubstring(&library, substring);
                        if (foundMusic) {
                            printf("Musica encontrada: ID: %d, Titulo: %s, Artista: %s\n", foundMusic->id, foundMusic->titulo, foundMusic->artista);
                        } else {
                            printf("Nenhuma musica encontrada com essa substring.\n");
                        }
                        break;
                    case 5:
                        removeDuplicates(&library);
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }
                break;
            case 2:
                printf("\n--- Gerenciar Playlist ---\n");
                printf("1. Adicionar musica da biblioteca a playlist\n");
                printf("2. Remover musica da playlist (dequeue)\n");
                printf("3. Exibir playlist\n");
                printf("4. Contar musicas com duracao > X\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        printf("Digite o ID da musica para adicionar a playlist: ");
                        scanf("%d", &id);
                        foundMusic = searchById(&library, id);
                        if (foundMusic) {
                            enqueue(&playlist, foundMusic);
                            printf("Musica '%s' adicionada a playlist.\n", foundMusic->titulo);
                        } else {
                            printf("Musica nao encontrada na biblioteca.\n");
                        }
                        break;
                    case 2:
                        foundMusic = dequeue(&playlist);
                        if (foundMusic) {
                            printf("Musica '%s' removida da playlist.\n", foundMusic->titulo);
                        }
                        break;
                    case 3:
                        if (isQueueEmpty(&playlist)) {
                            printf("A playlist esta vazia.\n");
                        } else {
                            printf("--- Playlist de Reproducao ---\n");
                            Musica* temp = playlist.front;
                            int count = 1;
                            while(temp != NULL) {
                                printf("%d. Titulo: %s, Artista: %s\n", count++, temp->titulo, temp->artista);
                                temp = temp->next;
                            }
                            printf("------------------------------\n");
                        }
                        break;
                    case 4:
                        printf("Digite a duracao minima em segundos: ");
                        scanf("%d", &minDuration);
                        int count = countLongSongs(&playlist, minDuration);
                        printf("Ha %d musica(s) com duracao superior a %d segundos na playlist.\n", count, minDuration);
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }
                break;
            case 3:
                printf("\n--- Controles de Reproducao ---\n");
                printf("1. Tocar a proxima musica\n");
                printf("2. Voltar para a musica anterior\n");
                printf("3. Inverter historico de navegacao\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        if (currentPlaying) {
                            push(&history, currentPlaying);
                            currentPlaying = NULL;
                        }
                        currentPlaying = dequeue(&playlist);
                        if (currentPlaying) {
                            printf("Tocando agora: %s - %s\n", currentPlaying->titulo, currentPlaying->artista);
                        } else {
                            printf("A playlist esta vazia. Nenhuma musica para tocar.\n");
                        }
                        break;
                    case 2:
                        if (currentPlaying) {
                             if (!isStackEmpty(&history)) {
                                enqueue(&playlist, currentPlaying); // Move a musica atual para o final da fila
                                Musica* previous = pop(&history);
                                currentPlaying = previous;
                                printf("Voltando para: %s - %s\n", currentPlaying->titulo, currentPlaying->artista);
                            } else {
                                printf("Nao ha musicas anteriores no historico.\n");
                            }
                        } else {
                            printf("Nao ha musica tocando no momento.\n");
                        }
                        break;
                    case 3:
                        reverseStack(&history);
                        printf("Historico de navegacao invertido.\n");
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }
                break;
            case 4:
                saveLibraryToFile(&library);
                printf("Encerrando o programa.\n");
                break;
            case 5:
                loadLibraryFromFile(&library);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (choice != 4);

    return 0;
}

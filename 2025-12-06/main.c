#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/*
 * Definição da estrutura de dados do Produto.
 * Domínio: Loja de Informática (TechBit Informática)
 */
typedef struct {
    int codigo;             // Identificador único
    char descricao[50];     // Ex: Mouse Gamer
    int quantidade;         // Estoque
    float preco;            // Valor unitário
    char marca[30];         // Campo opcional 1
    char categoria[30];     // Campo opcional 2
} Produto;

/*
 * Estrutura do Nó da Árvore Binária de Busca
 */
typedef struct No {
    Produto produto;
    struct No* esquerda;
    struct No* direita;
} No;

/*
 * Função: ler_texto
 * Descrição: Função auxiliar para ler strings e remover o \n do final.
 * Parâmetros:
 * buffer - onde a string será salva.
 * tamanho - tamanho máximo da string.
 */
void ler_texto(char* buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

/*
 * Função: criaNo
 * Descrição: Aloca memória e inicializa um novo nó com os dados do produto.
 * Parâmetros:
 * p - estrutura contendo os dados do produto.
 * Retorna:
 * Ponteiro para o novo nó criado.
 */
No* criaNo(Produto p) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->produto = p;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

/*
 * Função: busca
 * Descrição: Pesquisa um produto na árvore pelo código.
 * Parâmetros:
 * raiz - ponteiro para a raiz da árvore/subárvore.
 * codigo - inteiro representando o código a ser buscado.
 * Retorna:
 * Ponteiro para o nó encontrado ou NULL se não existir.
 */
No* busca(No* raiz, int codigo) {
    if (raiz == NULL || raiz->produto.codigo == codigo)
        return raiz;
    
    if (codigo < raiz->produto.codigo)
        return busca(raiz->esquerda, codigo);
    else
        return busca(raiz->direita, codigo);
}

/*
 * Função: insere
 * Descrição: Insere um novo produto na ABB mantendo a ordenação pelo código.
 * Parâmetros:
 * raiz - ponteiro para a raiz da árvore.
 * p - estrutura contendo os dados do produto.
 * Retorna:
 * Ponteiro atualizado para a raiz da árvore.
 */
No* insere(No* raiz, Produto p) {
    if (raiz == NULL)
        return criaNo(p);
    
    if (p.codigo < raiz->produto.codigo) {
        raiz->esquerda = insere(raiz->esquerda, p);
    } else if (p.codigo > raiz->produto.codigo) {
        raiz->direita = insere(raiz->direita, p);
    } else {
        printf("\n[ERRO] Codigo %d ja existe no sistema!\n", p.codigo);
    }
    return raiz;
}

/*
 * Função: menorValor
 * Descrição: Encontra o nó com o menor código em uma subárvore (mais à esquerda).
 * Parâmetros:
 * raiz - ponteiro para a subárvore.
 * Retorna:
 * Ponteiro para o nó com menor valor.
 */
No* menorValor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

/*
 * Função: removeNo
 * Descrição: Remove um produto da árvore pelo código, mantendo as propriedades da ABB.
 * Parâmetros:
 * raiz - ponteiro para a raiz da árvore.
 * codigo - código do produto a ser removido.
 * Retorna:
 * Ponteiro atualizado para a raiz da árvore.
 */
No* removeNo(No* raiz, int codigo) {
    if (raiz == NULL) {
        printf("\nProduto nao encontrado para remocao.\n");
        return raiz;
    }

    if (codigo < raiz->produto.codigo) {
        raiz->esquerda = removeNo(raiz->esquerda, codigo);
    } else if (codigo > raiz->produto.codigo) {
        raiz->direita = removeNo(raiz->direita, codigo);
    } else {
        // Nó encontrado
        // Caso 1: Sem filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Apenas um filho
        else if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // Caso 3: Dois filhos
        No* temp = menorValor(raiz->direita);
        raiz->produto = temp->produto; // Copia TODOS os dados do produto sucessor
        raiz->direita = removeNo(raiz->direita, temp->produto.codigo);
    }
    return raiz;
}

/*
 * Função: imprimir_produto
 * Descrição: Exibe os detalhes formatados de um único produto.
 * Parâmetros:
 * p - estrutura do produto.
 */
void imprimir_produto(Produto p) {
    printf("-------------------------------------------------\n");
    printf("Codigo: %d | Marca: %s\n", p.codigo, p.marca);
    printf("Descricao: %s\n", p.descricao);
    printf("Categoria: %s\n", p.categoria);
    printf("Estoque: %d | Preco: R$ %.2f\n", p.quantidade, p.preco);
}

/*
 * Função: emOrdem
 * Descrição: Percorre a árvore em ordem (crescente de código).
 * Parâmetros:
 * raiz - ponteiro para a raiz.
 */
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        imprimir_produto(raiz->produto);
        emOrdem(raiz->direita);
    }
}

/*
 * Função: preOrdem
 * Descrição: Percorre a árvore em pré-ordem (Raiz, Esquerda, Direita).
 * Parâmetros:
 * raiz - ponteiro para a raiz.
 */
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimir_produto(raiz->produto);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

/*
 * Função: posOrdem
 * Descrição: Percorre a árvore em pós-ordem (Esquerda, Direita, Raiz).
 * Parâmetros:
 * raiz - ponteiro para a raiz.
 */
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        imprimir_produto(raiz->produto);
    }
}

// =============================================================
// COMPLEMENTOS (Funcionalidades Extras)
// =============================================================

/*
 * Função: contar_produtos (Complemento 1)
 * Descrição: Conta o número total de nós na árvore.
 * Parâmetros:
 * raiz - ponteiro para a raiz.
 * Retorna:
 * Inteiro com o total de produtos.
 */
int contar_produtos(No* raiz) {
    if (raiz == NULL)
        return 0;
    return 1 + contar_produtos(raiz->esquerda) + contar_produtos(raiz->direita);
}

/*
 * Função: altura_arvore (Complemento 2)
 * Descrição: Calcula a altura da árvore (maior caminho da raiz até uma folha).
 * Parâmetros:
 * raiz - ponteiro para a raiz.
 * Retorna:
 * Inteiro representando a altura (-1 se vazia).
 */
int altura_arvore(No* raiz) {
    if (raiz == NULL)
        return -1;
    
    int esq = altura_arvore(raiz->esquerda);
    int dir = altura_arvore(raiz->direita);
    
    if (esq > dir)
        return 1 + esq;
    else
        return 1 + dir;
}

/*
 * Função: estoque_critico (Complemento 3)
 * Descrição: Lista produtos com quantidade abaixo de um limite informado.
 * Parâmetros:
 * raiz - ponteiro para a raiz.
 * limite - valor inteiro limite para considerar crítico.
 */
void estoque_critico(No* raiz, int limite) {
    if (raiz != NULL) {
        estoque_critico(raiz->esquerda, limite);
        if (raiz->produto.quantidade < limite) {
            printf(">> ALERTA DE ESTOQUE BAIXO (%d un.)\n", raiz->produto.quantidade);
            imprimir_produto(raiz->produto);
        }
        estoque_critico(raiz->direita, limite);
    }
}

// =============================================================
// MENU E INTERFACE
// =============================================================

void cadastrar_produto(No** raiz) {
    Produto p;
    printf("\n--- Novo Cadastro ---\n");
    
    printf("Digite o Codigo (Inteiro): ");
    scanf("%d", &p.codigo);
    while (getchar() != '\n'); // Limpar buffer

    // Validar duplicidade antes de pedir outros dados
    if (busca(*raiz, p.codigo) != NULL) {
        printf("\n[ERRO] Produto com codigo %d ja existe!\n", p.codigo);
        return;
    }

    printf("Descricao: ");
    ler_texto(p.descricao, 50);

    printf("Marca: ");
    ler_texto(p.marca, 30);

    printf("Categoria: ");
    ler_texto(p.categoria, 30);

    do {
        printf("Quantidade: ");
        scanf("%d", &p.quantidade);
        if (p.quantidade < 0) printf("Quantidade nao pode ser negativa.\n");
    } while (p.quantidade < 0);

    do {
        printf("Preco: ");
        scanf("%f", &p.preco);
        if (p.preco <= 0) printf("Preco deve ser maior que zero.\n");
    } while (p.preco <= 0);

    *raiz = insere(*raiz, p);
    printf("\nProduto cadastrado com sucesso!\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    No* raiz = NULL;
    int opcao, codigoAux, limite;

    do {
        printf("\n==========================================\n");
        printf("      TECHBIT INFORMATICA - GESTAO        \n");
        printf("==========================================\n");
        printf("1. Inserir Produto\n");
        printf("2. Consultar Produto\n");
        printf("3. Remover Produto\n");
        printf("4. Listar Produtos (Em-Ordem)\n");
        printf("5. Listar Produtos (Pre-Ordem)\n");
        printf("6. Listar Produtos (Pos-Ordem)\n");
        printf("------------------------------------------\n");
        printf("       FUNCIONALIDADES EXTRAS\n");
        printf("------------------------------------------\n");
        printf("7. Total de Produtos Cadastrados\n");
        printf("8. Altura da Arvore\n");
        printf("9. Relatorio de Estoque Critico\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpar buffer

        switch (opcao) {
            case 1:
                cadastrar_produto(&raiz);
                break;
            case 2:
                printf("Digite o codigo para busca: ");
                scanf("%d", &codigoAux);
                No* res = busca(raiz, codigoAux);
                if (res) {
                    printf("\n--- Produto Encontrado ---\n");
                    imprimir_produto(res->produto);
                } else {
                    printf("\n[!] Produto nao encontrado.\n");
                }
                break;
            case 3:
                printf("Digite o codigo para remocao: ");
                scanf("%d", &codigoAux);
                if (busca(raiz, codigoAux) != NULL) {
                    raiz = removeNo(raiz, codigoAux);
                    printf("\nProduto removido com sucesso (se existia).\n");
                } else {
                    printf("\n[!] Produto nao existe na base.\n");
                }
                break;
            case 4:
                printf("\n--- Listagem Em-Ordem ---\n");
                if (raiz == NULL) printf("Arvore vazia.\n");
                emOrdem(raiz);
                break;
            case 5:
                printf("\n--- Listagem Pre-Ordem ---\n");
                if (raiz == NULL) printf("Arvore vazia.\n");
                preOrdem(raiz);
                break;
            case 6:
                printf("\n--- Listagem Pos-Ordem ---\n");
                if (raiz == NULL) printf("Arvore vazia.\n");
                posOrdem(raiz);
                break;
            case 7:
                printf("\nTotal de produtos: %d\n", contar_produtos(raiz));
                break;
            case 8:
                printf("\nAltura da Arvore: %d\n", altura_arvore(raiz));
                break;
            case 9:
                printf("Defina o limite de estoque critico (ex: 5): ");
                scanf("%d", &limite);
                printf("\n--- Produtos com Estoque Crítico (< %d) ---\n", limite);
                estoque_critico(raiz, limite);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Pausa para leitura
        }

    } while (opcao != 0);

    return 0;
}

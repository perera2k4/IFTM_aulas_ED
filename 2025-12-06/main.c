#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define FILENAME "produtos.txt"

/*
 * Definicao da estrutura de dados do Produto.
 * Dominio: Loja de Informatica
 */
typedef struct {
    int codigo;             // Identificador unico
    char descricao[50];     // Ex: Mouse Gamer
    int quantidade;         // Estoque
    float preco;            // Valor unitario
    char marca[30];         // Campo opcional 1
    char categoria[30];     // Campo opcional 2
} Produto;

/*
 * Estrutura do No da Arvore Binaria de Busca
 */
typedef struct No {
    Produto produto;
    struct No* esquerda;
    struct No* direita;
} No;

/*
 * Funcao: ler_texto
 * Descricao: Funcao auxiliar para ler strings e remover o \n do final.
 * Parametros:
 * buffer - onde a string sera salva.
 * tamanho - tamanho maximo da string.
 */
void ler_texto(char* buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

/*
 * Funcao: criaNo
 * Descricao: Aloca memoria e inicializa um novo no com os dados do produto.
 * Parametros:
 * p - estrutura contendo os dados do produto.
 * Retorna:
 * Ponteiro para o novo no criado.
 */
No* criaNo(Produto p) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->produto = p;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

/*
 * Funcao: busca
 * Descricao: Pesquisa um produto na arvore pelo codigo.
 * Parametros:
 * raiz - ponteiro para a raiz da arvore/subarvore.
 * codigo - inteiro representando o codigo a ser buscado.
 * Retorna:
 * Ponteiro para o no encontrado ou NULL se nao existir.
 */
No* busca(No* raiz, int codigo) {
    if (raiz == NULL || raiz->produto.codigo == codigo) {
        return raiz;
    }
    
    if (codigo < raiz->produto.codigo) {
        return busca(raiz->esquerda, codigo);
    } else {
        return busca(raiz->direita, codigo);
    }
}

/*
 * Funcao: insere
 * Descricao: Insere um novo produto na ABB mantendo a ordenacao pelo codigo.
 * Parametros:
 * raiz - ponteiro para a raiz da arvore.
 * p - estrutura contendo os dados do produto.
 * Retorna:
 * Ponteiro atualizado para a raiz da arvore.
 */
No* insere(No* raiz, Produto p) {
    if (raiz == NULL) {
        return criaNo(p);
    }
    
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
 * Funcao: menorValor
 * Descricao: Encontra o no com o menor codigo em uma subarvore (mais a esquerda).
 * Parametros:
 * raiz - ponteiro para a subarvore.
 * Retorna:
 * Ponteiro para o no com menor valor.
 */
No* menorValor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

/*
 * Funcao: removeNo
 * Descricao: Remove um produto da arvore pelo codigo, mantendo as propriedades da ABB.
 * Parametros:
 * raiz - ponteiro para a raiz da arvore.
 * codigo - codigo do produto a ser removido.
 * Retorna:
 * Ponteiro atualizado para a raiz da arvore.
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
        // No encontrado
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
 * Funcao: imprimir_produto
 * Descricao: Exibe os detalhes formatados de um unico produto.
 * Parametros:
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
 * Funcao: emOrdem
 * Descricao: Percorre a arvore em ordem (crescente de codigo).
 * Parametros:
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
 * Funcao: preOrdem
 * Descricao: Percorre a arvore em pre-ordem (Raiz, Esquerda, Direita).
 * Parametros:
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
 * Funcao: posOrdem
 * Descricao: Percorre a arvore em pos-ordem (Esquerda, Direita, Raiz).
 * Parametros:
 * raiz - ponteiro para a raiz.
 */
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        imprimir_produto(raiz->produto);
    }
}

// Funcionalidades Extras)

/*
 * Funcao: contar_produtos (Complemento 1)
 * Descricao: Conta o numero total de nos na arvore.
 * Parametros:
 * raiz - ponteiro para a raiz.
 * Retorna:
 * Inteiro com o total de produtos.
 */
int contar_produtos(No* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contar_produtos(raiz->esquerda) + contar_produtos(raiz->direita);
}

/*
 * Funcao: altura_arvore (Complemento 2)
 * Descricao: Calcula a altura da arvore (maior caminho da raiz ate uma folha).
 * Parametros:
 * raiz - ponteiro para a raiz.
 * Retorna:
 * Inteiro representando a altura (-1 se vazia).
 */
int altura_arvore(No* raiz) {
    if (raiz == NULL) {
        return -1;
    }
    
    int esq = altura_arvore(raiz->esquerda);
    int dir = altura_arvore(raiz->direita);
    
    if (esq > dir) {
        return 1 + esq;
    } else {
        return 1 + dir;
    }
}

/*
 * Funcao: estoque_critico (Complemento 3)
 * Descricao: Lista produtos com quantidade abaixo de um limite informado.
 * Parametros:
 * raiz - ponteiro para a raiz.
 * limite - valor inteiro limite para considerar critico.
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

// Salvar/Carregar

/*
 * Funcao: salvar_em_ordem_aux
 * Descricao: Funcao auxiliar recursiva para salvar produtos em ordem no arquivo.
 * Parametros:
 * raiz - ponteiro para a raiz da arvore.
 * arquivo - ponteiro para o arquivo aberto.
 */
void salvar_em_ordem_aux(No* raiz, FILE* arquivo) {
    if (raiz != NULL) {
        salvar_em_ordem_aux(raiz->esquerda, arquivo);
        fprintf(arquivo, "%d;%s;%s;%s;%d;%.2f\n",
                raiz->produto.codigo,
                raiz->produto.descricao,
                raiz->produto.marca,
                raiz->produto.categoria,
                raiz->produto.quantidade,
                raiz->produto.preco);
        salvar_em_ordem_aux(raiz->direita, arquivo);
    }
}

/*
 * Funcao: salvar_produtos
 * Descricao: Salva todos os produtos da arvore em um arquivo .txt.
 * Parametros:
 * raiz - ponteiro para a raiz da arvore.
 */
void salvar_produtos(No* raiz) {
    FILE* arquivo = fopen(FILENAME, "w");
    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo para salvar.\n");
        return;
    }

    salvar_em_ordem_aux(raiz, arquivo);
    fclose(arquivo);
    printf("\nProdutos salvos com sucesso em '%s'.\n", FILENAME);
}

/*
 * Funcao: carregar_produtos
 * Descricao: Carrega produtos de um arquivo .txt e reconstroi a arvore.
 * Parametros:
 * raiz - ponteiro duplo para a raiz da arvore.
 */
void carregar_produtos(No** raiz) {
    FILE* arquivo = fopen(FILENAME, "r");
    if (arquivo == NULL) {
        printf("\nArquivo de dados nao encontrado. Iniciando com arvore vazia.\n");
        return;
    }

    char linha[256];
    int produtos_carregados = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        Produto p;
        if (sscanf(linha, "%d;%49[^;];%29[^;];%29[^;];%d;%f",
                   &p.codigo, p.descricao, p.marca, p.categoria,
                   &p.quantidade, &p.preco) == 6) {
            *raiz = insere(*raiz, p);
            produtos_carregados++;
        }
    }

    fclose(arquivo);
    printf("\n%d produto(s) carregado(s) com sucesso de '%s'.\n", produtos_carregados, FILENAME);
}

// Menu e interface

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
        if (p.quantidade < 0) {
            printf("Quantidade nao pode ser negativa.\n");
        }
    } while (p.quantidade < 0);

    do {
        printf("Preco: ");
        scanf("%f", &p.preco);
        if (p.preco <= 0) {
            printf("Preco deve ser maior que zero.\n");
        }
    } while (p.preco <= 0);

    *raiz = insere(*raiz, p);
    printf("\nProduto cadastrado com sucesso!\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    No* raiz = NULL;
    int opcao, codigoAux, limite;

    // Carregar produtos do arquivo ao iniciar
    carregar_produtos(&raiz);

    do {
        printf("\n------------------------------------------\n");
        printf("      GESTAO DE ESTOQUE DE PRODUTOS        \n");
        printf("------------------------------------------\n");
        printf("1. Inserir Produto\n");
        printf("2. Consultar Produto\n");
        printf("3. Remover Produto\n");
        printf("4. Listar Produtos (Em-Ordem)\n");
        printf("5. Listar Produtos (Pre-Ordem)\n");
        printf("6. Listar Produtos (Pos-Ordem)\n");
        printf("\n------------------------------------------\n");
        printf("       FUNCIONALIDADES EXTRAS\n");
        printf("------------------------------------------\n");
        printf("7. Total de Produtos Cadastrados\n");
        printf("8. Altura da Arvore\n");
        printf("9. Relatorio de Estoque Critico\n");
        printf("10. Salvar Produtos em Arquivo\n");
        printf("11. Carregar Produtos de Arquivo\n");
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
                if (raiz == NULL) {
                    printf("Arvore vazia.\n");
                }
                emOrdem(raiz);
                break;
            case 5:
                printf("\n--- Listagem Pre-Ordem ---\n");
                if (raiz == NULL) {
                    printf("Arvore vazia.\n");
                }
                preOrdem(raiz);
                break;
            case 6:
                printf("\n--- Listagem Pos-Ordem ---\n");
                if (raiz == NULL) {
                    printf("Arvore vazia.\n");
                }
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
                printf("\n--- Produtos com Estoque Critico (< %d) ---\n", limite);
                estoque_critico(raiz, limite);
                break;
            case 10:
                salvar_produtos(raiz);
                break;
            case 11:
                carregar_produtos(&raiz);
                break;
            case 0:
                salvar_produtos(raiz);
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

/* Este programa tem como objetivo servir de base para a revisão dos principais
aspectos da Linguagem C para estudantes de graduação. O programa prioriza a 
clareza e o didatismo */

#include <stdio.h>
#include <string.h>

// Definindo uma constante para o número máximo de alunos 
#define MAX_ALUNOS 5

// Estrutura para armazenar os dados de um aluno
struct Aluno {
    char nome[50];
    int idade;
    union {
        float notaFinal;  // Usando uma união para armazenar a nota
        char conceito;    // Alternativamente, pode ser um conceito (A, B, C...)
    } desempenho;
    int usaNota;  // Indica se está usando nota numérica (1) ou conceito (0)
};

// Protótipos de funções
// Desnecessário se todas as funções estão em um mesmo arquivo e a função main() é a última
void inserirAlunos(struct Aluno alunos[], int quantidade);
void exibirAlunos(struct Aluno alunos[], int quantidade);
float calcularMediaNotas(struct Aluno alunos[], int quantidade);

int main() {
    // Vetor de estruturas para armazenar os alunos
    struct Aluno alunos[MAX_ALUNOS];

    int opcao;
    int totalAlunos = 0;
    
    // Menu principal, usando estrutura de repetição 'while'
    while (1) {
        printf("\nGerenciamento de Alunos\n");
        printf("1. Inserir Alunos\n");
        printf("2. Exibir Alunos\n");
        printf("3. Calcular Media das Notas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Estrutura de seleção 'switch' para escolher a opção do menu
        switch (opcao) {
            case 1:
                if (totalAlunos < MAX_ALUNOS) {
                    inserirAlunos(alunos, totalAlunos);
                    totalAlunos++;
                } else {
                    printf("Número maximo de alunos atingido.\n");
                }
                break;
            case 2:
                if (totalAlunos > 0) {
                    exibirAlunos(alunos, totalAlunos);
                } else {
                    printf("Nenhum aluno inserido ainda.\n");
                }
                break;
            case 3:
                if (totalAlunos > 0) {
                    float media = calcularMediaNotas(alunos, totalAlunos);
                    printf("Media das notas dos alunos: %.2f\n", media);
                } else {
                    printf("Nenhum aluno inserido ainda.\n");
                }
                break;
            case 0:
                // Saindo do programa
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
    return 0;
}

// Função para inserir dados dos alunos em um vetor de estruturas
void inserirAlunos(struct Aluno alunos[], int indice) {
    printf("\nInserindo Aluno %d\n", indice + 1);
    
    printf("Nome: ");
    scanf("%s", alunos[indice].nome); 

    printf("Idade: ");
    scanf("%d", &alunos[indice].idade);

    printf("Deseja inserir a nota numerica ou o conceito (1 para nota, 0 para conceito)? ");
    scanf("%d", &alunos[indice].usaNota);

    if (alunos[indice].usaNota == 1) {
        // Insere a nota final se o aluno usar nota numérica
        printf("Nota Final: ");
        scanf("%f", &alunos[indice].desempenho.notaFinal);
    } else {
        // Insere o conceito (A, B, C...) se o aluno usar conceito
        printf("Conceito (A, B, C, D ou F): ");
        scanf(" %c", &alunos[indice].desempenho.conceito);  // Espaço antes de %c para ignorar caracteres de nova linha
    }
}

// Função para exibir os dados dos alunos armazenados
void exibirAlunos(struct Aluno alunos[], int quantidade) {
    int i;
    
	printf("\nLista de Alunos:\n");
    
    // Estrutura de repetição 'for' para percorrer o vetor de alunos
    for (i = 0; i < quantidade; i++) {
        printf("Aluno %d\n", i + 1);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Idade: %d\n", alunos[i].idade);

        // Verifica se deve exibir a nota numérica ou o conceito
        if (alunos[i].usaNota == 1) {
            printf("Nota Final: %.2f\n", alunos[i].desempenho.notaFinal);
        } else {
            printf("Conceito: %c\n", alunos[i].desempenho.conceito);
        }
        printf("------------------------\n");
    }
}

// Função para calcular a média das notas dos alunos
// Alunos que utilizam conceito são ignorados no cálculo
float calcularMediaNotas(struct Aluno alunos[], int quantidade) {
    float soma = 0.0;
    int contador = 0, i;
    
    // Percorre todos os alunos
    for (i = 0; i < quantidade; i++) {
        // Apenas considera os alunos que usam nota numérica
        if (alunos[i].usaNota == 1) {
            soma += alunos[i].desempenho.notaFinal;
        }
        // Utiliza uma média para os alunos registrados como conceito
        else if (alunos[i].usaNota == 0) {
        	switch (alunos[i].desempenho.conceito) {
	    		case 'A': soma += 9.0; break;
	    		case 'B': soma += 7.0; break;
	    		case 'C': soma += 5.0; break;
	    		case 'D': soma += 3.0; break;
	    		case 'F': soma += 1.0; break;
	    		default: printf("O conceito registrado para algum(ns) alunos não foi A, B, C, D ou F\n"); break;
			}
		}
		contador++;
    }

    // Se houver alunos com notas numéricas, calcula a média
    if (contador > 0) {
        return soma / contador;
    } else {
        return 0.0;  // Caso nenhum aluno tenha nota numérica, retorna 0
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Struct que representa um componente da torre de resgate
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 (alta) a 10 (baixa)
} Componente;

// Variáveis globais
Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;
int comparacoes = 0;

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para inserir novo componente
void inserirComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido.\n");
        return;
    }

    Componente novo;
    printf("Nome do componente: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do componente: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    do {
        printf("Prioridade (1 a 10): ");
        scanf("%d", &novo.prioridade);
        limparBuffer();
    } while (novo.prioridade < 1 || novo.prioridade > 10);

    torre[totalComponentes++] = novo;
    printf("Componente adicionado com sucesso!\n");
}

// Função para exibir todos os componentes
void mostrarComponentes(Componente arr[], int n) {
    printf("\n--- Componentes da Torre ---\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. Nome: %-25s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("------------------------------\n");
}

// BUBBLE SORT (por nome)
void bubbleSortNome(Componente arr[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                Componente temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// INSERTION SORT (por tipo)
void insertionSortTipo(Componente arr[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            arr[j + 1] = arr[j];
            j--;
        }
        if (j >= 0) comparacoes++; // conta a última comparação falsa
        arr[j + 1] = chave;
    }
}

// SELECTION SORT (por prioridade)
void selectionSortPrioridade(Componente arr[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (arr[j].prioridade < arr[menor].prioridade) {
                menor = j;
            }
        }
        if (menor != i) {
            Componente temp = arr[i];
            arr[i] = arr[menor];
            arr[menor] = temp;
        }
    }
}

// BUSCA BINÁRIA (por nome) – funciona após ordenação por nome
int buscaBinariaPorNome(Componente arr[], int n, char nomeBuscado[30], int* comp) {
    int inicio = 0, fim = n - 1;
    *comp = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comp)++;
        int cmp = strcmp(arr[meio].nome, nomeBuscado);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// Função para medir tempo de execução de algoritmos
void medirTempo(void (*sortFunc)(Componente[], int), Componente arr[], int n) {
    clock_t inicio = clock();
    sortFunc(arr, n);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %.6f segundos\n", tempo);
    printf("Comparações realizadas: %d\n", comparacoes);
}

// Função principal do menu
void menuPrincipal() {
    int op;
    do {
        printf("\n=== MENU - TORRE DE RESGATE ===\n");
        printf("1. Inserir componente\n");
        printf("2. Ordenar por NOME (Bubble Sort)\n");
        printf("3. Ordenar por TIPO (Insertion Sort)\n");
        printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5. Buscar componente-chave (após ordenação por nome)\n");
        printf("6. Mostrar componentes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        limparBuffer();

        char chave[30];
        int resultado, comparacoesBusca;

        switch (op) {
            case 1:
                inserirComponente();
                break;

            case 2:
                medirTempo(bubbleSortNome, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                break;

            case 3:
                medirTempo(insertionSortTipo, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                break;

            case 4:
                medirTempo(selectionSortPrioridade, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                break;

            case 5:
                if (totalComponentes == 0) {
                    printf("Nenhum componente cadastrado!\n");
                    break;
                }
                printf("Digite o nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';

                resultado = buscaBinariaPorNome(torre, totalComponentes, chave, &comparacoesBusca);
                if (resultado != -1) {
                    printf("Componente encontrado: Nome: %s | Tipo: %s | Prioridade: %d\n",
                           torre[resultado].nome, torre[resultado].tipo, torre[resultado].prioridade);
                } else {
                    printf("Componente NÃO encontrado.\n");
                }
                printf("Comparações na busca binária: %d\n", comparacoesBusca);
                break;

            case 6:
                mostrarComponentes(torre, totalComponentes);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (op != 0);
}

// Função principal
int main() {
    menuPrincipal();
    return 0;
}

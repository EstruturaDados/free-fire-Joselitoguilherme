// nível aventureiro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== DEFINIÇÕES COMUNS =====
#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ===== VARIÁVEIS GLOBAIS =====
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

No* inicioLista = NULL;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ======== FUNÇÕES PARA VETOR ========

void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("Mochila (vetor) cheia.\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalItensVetor++] = novo;
    printf("Item inserido no vetor com sucesso!\n");
}

void listarItensVetor() {
    printf("\n--- Mochila (Vetor) ---\n");
    if (totalItensVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < totalItensVetor; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("Mochila está vazia.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}

void buscarSequencialVetor() {
    char nome[30];
    printf("Digite o nome do item para buscar: ");
    scanf(" %[^\n]", nome);
    comparacoesSequencial = 0;

    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Item encontrado! Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações feitas: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("Item não encontrado.\nComparações feitas: %d\n", comparacoesSequencial);
}

void ordenarVetor() {
    // Bubble Sort
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Mochila ordenada por nome.\n");
}

void buscarBinariaVetor() {
    char nome[30];
    printf("Digite o nome do item para busca binária: ");
    scanf(" %[^\n]", nome);
    comparacoesBinaria = 0;

    int inicio = 0, fim = totalItensVetor - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) {
            printf("Item encontrado! Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[meio].nome,
                   mochilaVetor[meio].tipo,
                   mochilaVetor[meio].quantidade);
            printf("Comparações feitas: %d\n", comparacoesBinaria);
            return;
        } else if (cmp > 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("Item não encontrado.\nComparações feitas: %d\n", comparacoesBinaria);
}

// ======== FUNÇÕES PARA LISTA ENCADEADA ========

void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocação.\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicioLista;
    inicioLista = novo;

    printf("Item inserido na lista com sucesso!\n");
}

void listarItensLista() {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    No* atual = inicioLista;

    if (!atual) {
        printf("Mochila vazia.\n");
        return;
    }

    while (atual) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void removerItemLista() {
    char nome[30];
    printf("Digite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                inicioLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido da lista.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado.\n");
}

void buscarSequencialLista() {
    char nome[30];
    printf("Digite o nome do item para buscar: ");
    scanf(" %[^\n]", nome);
    comparacoesSequencial = 0;

    No* atual = inicioLista;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado! Nome: %s | Tipo: %s | Quantidade: %d\n",
                   atual->dados.nome,
                   atual->dados.tipo,
                   atual->dados.quantidade);
            printf("Comparações feitas: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }

    printf("Item não encontrado.\nComparações feitas: %d\n", comparacoesSequencial);
}

// ======== MENU PRINCIPAL ========

void menuVetor() {
    int op;
    do {
        printf("\n=== Mochila com Vetor ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar sequencial\n");
        printf("5. Ordenar\n");
        printf("6. Buscar binária\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
        }
    } while (op != 0);
}

void menuLista() {
    int op;
    do {
        printf("\n=== Mochila com Lista Encadeada ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar sequencial\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
        }
    } while (op != 0);
}

int main() {
    int escolha;
    do {
        printf("\n======= SISTEMA DE MOCHILA =======\n");
        printf("1. Usar mochila com vetor\n");
        printf("2. Usar mochila com lista encadeada\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (escolha != 0);

    return 0;
}

//nivel novato

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct que representa um item
struct Item {
    char nome[30];    // Nome do item
    char tipo[20];    // Tipo do item (arma, munição, cura, etc.)
    int quantidade;   // Quantidade do item
};

#define MAX_ITENS 10

// Vetor que armazena os itens da mochila
struct Item mochila[MAX_ITENS];
int totalItens = 0; // Controla quantos itens já foram adicionados

// Função para inserir um item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("A mochila está cheia. Não é possível adicionar mais itens.\n");
        return;
    }

    struct Item novoItem;

    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novoItem.nome);  // Lê string com espaços

    printf("Digite o tipo do item (arma, municao, cura, etc.): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("Item adicionado com sucesso!\n");
    listarItens();
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("A mochila está vazia. Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Move todos os itens após o encontrado para uma posição anterior
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }

    listarItens();
}

// Função para listar todos os itens da mochila
void listarItens() {
    printf("\n--- Itens na Mochila ---\n");
    if (totalItens == 0) {
        printf("Nenhum item cadastrado.\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("Item %d:\n", i + 1);
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("----------------------\n");
        }
    }
}

// Função para buscar um item pelo nome
void buscarItem() {
    if (totalItens == 0) {
        printf("A mochila está vazia. Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
}

// Função principal (menu)
int main() {
    int opcao;

    do {
        printf("\n=== MENU DO INVENTÁRIO ===\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

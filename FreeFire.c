#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define MAX_NOME 50
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int ativo;
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;

void inicializarMochila() {
    for (int i = 0; i < MAX_ITENS; i++) {
        mochila[i].ativo = 0;
        mochila[i].quantidade = 0;
    }
}

void adicionarItem() {
    int i;
    int posicaoLivre = -1;

    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo == 0) {
            posicaoLivre = i;
            break;
        }
    }

    if (posicaoLivre == -1) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item (máx. %d caracteres): ", MAX_NOME - 1);
    while (getchar() != '\n');
    fgets(mochila[posicaoLivre].nome, MAX_NOME, stdin);
    mochila[posicaoLivre].nome[strcspn(mochila[posicaoLivre].nome, "\n")] = 0;

    printf("Tipo do item (máx. %d caracteres): ", MAX_TIPO - 1);
    fgets(mochila[posicaoLivre].tipo, MAX_TIPO, stdin);
    mochila[posicaoLivre].tipo[strcspn(mochila[posicaoLivre].tipo, "\n")] = 0;

    printf("Quantidade: ");
    if (scanf("%d", &mochila[posicaoLivre].quantidade) != 1 || mochila[posicaoLivre].quantidade <= 0) {
        printf("\n❌ Quantidade inválida. Item não adicionado.\n");
        mochila[posicaoLivre].ativo = 0;
        while (getchar() != '\n');
        return;
    }
    
    mochila[posicaoLivre].ativo = 1;
    totalItens++;

    printf("\n✅ Sucesso! Item '%s' adicionado na posição %d.\n", mochila[posicaoLivre].nome, posicaoLivre + 1);
}

void removerItem() {
    char nomeBusca[MAX_NOME];
    int i, encontrado = 0;

    if (totalItens == 0) {
        printf("\n⚠️ Inventário vazio. Não há itens para remover.\n");
        return;
    }

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    while (getchar() != '\n');
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo == 1 && strcmp(mochila[i].nome, nomeBusca) == 0) {
            mochila[i].ativo = 0;
            mochila[i].quantidade = 0;
            totalItens--;
            encontrado = 1;
            printf("\n🗑️ Sucesso! Item '%s' removido.\n", nomeBusca);
            break; 
        }
    }

    if (!encontrado) {
        printf("\n❓ Aviso: Item '%s' não encontrado no inventário.\n", nomeBusca);
    }
}

void listarItens() {
    int i;
    
    printf("\n--- Inventário Atual (Mochila) ---\n");

    if (totalItens == 0) {
        printf("\n🎒 Mochila Vazia. Não há itens cadastrados.\n");
        printf("Capacidade total: %d itens.\n", MAX_ITENS);
        return;
    }

    printf("Total de itens ativos: %d / %d\n", totalItens, MAX_ITENS);
    
    printf("+--------------------------------------------------+----------------------+-------------+\n");
    printf("| NOME | TIPO | QUANT. |\n");
    printf("+--------------------------------------------------+----------------------+-------------+\n");

    for (i = 0; i < MAX_ITENS; i++) {
        if (mochila[i].ativo == 1) {
            printf("| %-48s | %-20s | %-11d |\n", 
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    
    printf("+--------------------------------------------------+----------------------+-------------+\n");
}

void exibirMenu() {
    printf("\n============================\n");
    printf("🎮 INVENTÁRIO BÁSICO (C)\n");
    printf("============================\n");
    printf("1. Adicionar Item\n");
    printf("2. Listar Itens\n");
    printf("3. Remover Item (pelo Nome)\n");
    printf("4. Sair\n");
    printf("----------------------------\n");
    printf("Escolha uma opção (1-4): ");
}

int main() {
    int opcao;
    
    inicializarMochila();

    do {
        exibirMenu();
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n❌ Entrada inválida. Digite apenas o número da opção.\n");
            opcao = 0;
            while (getchar() != '\n');
        }

        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                listarItens();
                break;
            case 3:
                removerItem();
                break;
            case 4:
                printf("\n👋 Saindo do programa.\n");
                break;
            default:
                if (opcao != 0) {
                    printf("\n❓ Opção inválida. Tente novamente.\n");
                }
                break;
        }
        
    } while (opcao != 4);

    return 0;
}
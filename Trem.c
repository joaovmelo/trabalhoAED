#include <stdlib.h>
#include <stdio.h>
#include "Trem.h"
#include "Vagao.h"

Trem* criarTrem() {
    Trem *trem = (Trem*)calloc(1, sizeof(Trem));
    if (trem == NULL) return NULL;
    trem->prox = NULL;
    trem->vagaoInicio = NULL;
    trem->vagaoFinal = NULL;
    trem->sizeTrem = 0;
    return trem;
}

void destruirTrem(Trem *trem) {
    if (trem == NULL) return;
    limparVagoes(trem);
    free(trem);
}

void adicionarTrem(Trem **listaTrens) {
    Trem *novoTrem = criarTrem();
    if (novoTrem == NULL) return;

    if (*listaTrens == NULL) {
        *listaTrens = novoTrem;
    } else {
        Trem *atual = *listaTrens;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoTrem;
    }
}

void removerTrem(Trem **listaTrens) {
    if (*listaTrens == NULL) {
        printf("Nenhum trem para remover.\n");
        return;
    }
    int count = 0;
    Trem *atual = *listaTrens;
    while (atual != NULL) {
        printf("%d - Trem com %d vagoes\n", count, atual->sizeTrem);
        atual = atual->prox;
        count++;
    }
    int escolha;
    printf("Escolha o numero do trem para remover: ");
    if (scanf("%d", &escolha) != 1) {
        printf("Entrada invalida!\n");
        while (getchar() != '\n');
        return;
    }
    if (escolha < 0 || escolha >= count) {
        printf("Trem inexistente!\n");
        return;
    }
    Trem *anterior = NULL;
    atual = *listaTrens;
    for (int i = 0; i < escolha; i++) {
        anterior = atual;
        atual = atual->prox;
    }
    limparVagoes(atual);
    if (anterior == NULL) {
        *listaTrens = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    printf("Trem removido com sucesso!\n");
}

void listarTrens(Trem *listaTrens) {
    if (listaTrens == NULL) {
        printf("Nenhum trem cadastrado.\n");
        return;
    }
    int count = 0;
    Trem *atual = listaTrens;
    while (atual != NULL) {
        printf("Trem %d - %d vagoes\n", count, atual->sizeTrem);
        atual = atual->prox;
        count++;
    }
}

int contarTrens(Trem *listaTrens) {
    int count = 0;
    while (listaTrens != NULL) {
        count++;
        listaTrens = listaTrens->prox;
    }
    return count;
}

Trem* selecionarTrem(Trem *listaTrens) {
    int opcao;
    int i = 0;
    // Primeiro, listamos os trens disponíveis
    printf("\n=== SELECIONAR UM TREM ===\n");
    
    if (listaTrens == NULL) {
        printf("Nenhum trem disponivel.\n");
        return NULL;
    }
    // Exibe a lista de trens para o usuário escolher
    Trem *tremAtual = listaTrens;
    int cout = 0;
    while (tremAtual != NULL) {
        printf("%d. Trem %d (com %d vagoes)\n", i + 1, cout, tremAtual->sizeTrem);
        tremAtual = tremAtual->prox;
        i++;
        cout++;
    }
    printf("Escolha um trem (1 a %d): ", i);
    scanf("%d", &opcao);
    // Verifica se a opção está dentro do intervalo válido
    if (opcao < 1 || opcao > i) {
        printf("Opção invalida!\n");
        return NULL;
    }
    // Reseta a variável para acessar o trem selecionado
    tremAtual = listaTrens;
    for (int j = 1; j < opcao; j++) {
        tremAtual = tremAtual->prox;
    }
    return tremAtual;  // Retorna o trem selecionado
}

void destruirTodosTrens(Trem *listaTrens) {
    while (listaTrens != NULL) {
        Trem *proximoTrem = listaTrens->prox;

        // Libera todos os vagões deste trem
        Vagao *vagaoAtual = listaTrens->vagaoInicio;
        while (vagaoAtual != NULL) {
            Vagao *vagaoTemp = vagaoAtual;
            vagaoAtual = vagaoAtual->prox;
            free(vagaoTemp);
        }
        free(listaTrens);
        listaTrens = proximoTrem;
    }
    printf("Sistema limpo!");
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Vagao.h"
#include "Trem.h"

Vagao* criarVagao(double capacidade, const char *tipoCarga) {
    Vagao *vagao = (Vagao*)calloc(1, sizeof(Vagao));
    if (vagao == NULL) {
        printf("Erro ao alocar memoria para vagao.\n");
        return NULL;
    }
    vagao->ant = NULL;
    vagao->prox = NULL;
    vagao->capacidadeTotal = capacidade;
    strncpy(vagao->tipoCarga, tipoCarga, 99);
    vagao->tipoCarga[99] = '\0';
    return vagao;
}

void atualizarPosicoes(Trem *trem) {
    if (trem == NULL) return;
    
    Vagao *vagaoAtual = trem->vagaoInicio;
    int posicao = 0;
    while (vagaoAtual != NULL) {
        vagaoAtual->posicao = posicao;
        posicao++;
        vagaoAtual = vagaoAtual->prox;
    }
}

void inserirVagaoInicio(Trem *trem, double capacidade, const char *tipoCarga) {
    if (trem == NULL) return;
    
    Vagao *vagao = criarVagao(capacidade, tipoCarga);
    if (vagao == NULL) return;
    
    if (trem->vagaoInicio == NULL) {
        trem->vagaoInicio = vagao;
        trem->vagaoFinal = vagao;
    } else {
        vagao->prox = trem->vagaoInicio;
        trem->vagaoInicio->ant = vagao;
        trem->vagaoInicio = vagao;
    }
    trem->sizeTrem++;
    atualizarPosicoes(trem);
}

void inserirVagaoPosicao(Trem *trem, double capacidade, const char *tipoCarga, int posicao) {
    if (trem == NULL) return;
    
    if (posicao <= 0) {
        inserirVagaoInicio(trem, capacidade, tipoCarga);
        return;
    }
    if (posicao >= trem->sizeTrem) {
        inserirVagaoFim(trem, capacidade, tipoCarga);
        return;
    }
    
    Vagao *vagao = criarVagao(capacidade, tipoCarga);
    if (vagao == NULL) return;
    
    Vagao *atual = trem->vagaoInicio;
    while (atual != NULL && atual->posicao < posicao) {
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        inserirVagaoFim(trem, capacidade, tipoCarga);
        return;
    }
    
    vagao->prox = atual;
    vagao->ant = atual->ant;
    atual->ant->prox = vagao;
    atual->ant = vagao;
    
    trem->sizeTrem++;
    atualizarPosicoes(trem);
}

void inserirVagaoFim(Trem *trem, double capacidade, const char *tipoCarga) {
    if (trem == NULL) return;
    
    Vagao *vagao = criarVagao(capacidade, tipoCarga);
    if (vagao == NULL) return;
    
    if (trem->vagaoInicio == NULL) {
        trem->vagaoInicio = vagao;
        trem->vagaoFinal = vagao;
    } else {
        trem->vagaoFinal->prox = vagao;
        vagao->ant = trem->vagaoFinal;
        trem->vagaoFinal = vagao;
    }
    trem->sizeTrem++;
    atualizarPosicoes(trem);
}

void removerVagaoPosicao(Trem *trem, int posicao) {
    if (trem == NULL || trem->vagaoInicio == NULL) {
        printf("Trem vazio ou inexistente.\n");
        return;
    }
    
    if (posicao < 0) posicao = 0;
    if (posicao >= trem->sizeTrem) posicao = trem->sizeTrem - 1;
    
    Vagao *atual = trem->vagaoInicio;
    while (atual != NULL && atual->posicao != posicao) {
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Vagao nao encontrado.\n");
        return;
    }
    
    if (atual->ant == NULL) { 
        trem->vagaoInicio = atual->prox;
        if (trem->vagaoInicio != NULL) {
            trem->vagaoInicio->ant = NULL;
        } else {
            trem->vagaoFinal = NULL;
        }
    } else if (atual->prox == NULL) { 
        trem->vagaoFinal = atual->ant;
        trem->vagaoFinal->prox = NULL;
    } else { // Meio da lista
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }
    
    free(atual);
    trem->sizeTrem--;
    atualizarPosicoes(trem);
    printf("Vagao removido com sucesso.\n");
}

void limparVagoes(Trem *trem) {
    if (trem == NULL) return;
    
    Vagao *atual = trem->vagaoInicio;
    while (atual != NULL) {
        Vagao *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    
    trem->vagaoInicio = NULL;
    trem->vagaoFinal = NULL;
    trem->sizeTrem = 0;
}

void listarVagoes(Trem *trem) {
    if (trem == NULL || trem->vagaoInicio == NULL) {
        printf("Trem vazio ou inexistente.\n");
        return;
    }
    
    Vagao *vagaoAtual = trem->vagaoInicio;
    printf("Lista de Vagoes:\n");
    printf("Pos | Capacidade | Tipo de Carga\n");
    printf("----|------------|--------------\n");
    
    while (vagaoAtual != NULL) {
        printf("%3d | %10.2f | %s\n", 
               vagaoAtual->posicao, 
               vagaoAtual->capacidadeTotal, 
               vagaoAtual->tipoCarga);
        vagaoAtual = vagaoAtual->prox;
    }
}

void maiorCapacidade(Trem *trem) {
    if (trem == NULL || trem->vagaoInicio == NULL) {
        printf("Trem vazio ou inexistente.\n");
        return;
    }
    
    Vagao *maior = trem->vagaoInicio;
    Vagao *atual = trem->vagaoInicio->prox;
    
    while (atual != NULL) {
        if (atual->capacidadeTotal > maior->capacidadeTotal) {
            maior = atual;
        }
        atual = atual->prox;
    }
    
    printf("Vagao com maior capacidade:\n");
    printf("Posicao: %d\n", maior->posicao);
    printf("Capacidade: %.2f\n", maior->capacidadeTotal);
    printf("Tipo de Carga: %s\n", maior->tipoCarga);
}

void ordenarPorTipoCarga(Trem *trem) {
    if (trem == NULL || trem->sizeTrem < 2) {
        return;
    }
    
    int trocou;
    do {
        trocou = 0;
        Vagao *atual = trem->vagaoInicio;
        Vagao *proximo = atual->prox;
        
        while (proximo != NULL) {
            if (strcmp(atual->tipoCarga, proximo->tipoCarga) > 0) {
                double tempCap = atual->capacidadeTotal;
                char tempCarga[100];
                strcpy(tempCarga, atual->tipoCarga);
                
                atual->capacidadeTotal = proximo->capacidadeTotal;
                strcpy(atual->tipoCarga, proximo->tipoCarga);
                
                proximo->capacidadeTotal = tempCap;
                strcpy(proximo->tipoCarga, tempCarga);
                
                trocou = 1;
            }
            atual = proximo;
            proximo = proximo->prox;
        }
    } while (trocou);
    
    atualizarPosicoes(trem);
    printf("Vagoes reordenados por tipo de carga.\n");
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Trem.h"

Trem *createTrem(){
    Trem *trem = (Trem*)calloc(1, sizeof(Trem));
    if(trem == NULL){
        return;
    }
    trem->prox = NULL;
    trem->vagaoInicio = NULL;
    trem->vagaoFinal = NULL;
    trem->sizeTrem = 0;
    return trem;
}
Vagao *createVagao(double capacidade, char const *tipoCarga){
    Vagao *vagao = (Vagao*)calloc(1, sizeof(Vagao));
    vagao->ant = NULL;
    vagao->prox = NULL;
    vagao->capacidadeTotal = capacidade;
    strcpy(vagao->tipoCarga, tipoCarga);
    return vagao;
}
void atualizaPosicoes(Trem *trem) {
    if (trem == NULL){
        return;
    }
    Vagao *vagaoAtual = trem->vagaoInicio;
    int posicao = 0;
    while (vagaoAtual != NULL) {
        vagaoAtual->posicao = posicao;
        posicao++;
        vagaoAtual = vagaoAtual->prox;
    }
}

void insereVagaoInicio(Trem *trem, double capacidade, char const *tipoCarga){
    if(trem == NULL){
        return;
    }
    Vagao *vagao = createVagao(capacidade, tipoCarga);
    if(vagao == NULL){
        return;
    }
    if(trem->vagaoInicio == NULL){
        trem->vagaoInicio = vagao;
        trem->vagaoFinal = vagao;
        trem->sizeTrem++;
        atualizaPosicoes(trem);
    }else{
        vagao->prox = trem->vagaoInicio;
        trem->vagaoInicio->ant = vagao;
        trem->vagaoInicio = vagao;
        trem->sizeTrem++;
        atualizaPosicoes(trem);
    }
}
void insereVagaoMeio(Trem *trem, double capacidade, char const *tipoCarga){ //verificar se esta correto
    if(trem == NULL){
        return;
    }
    Vagao *vagao = createVagao(capacidade, tipoCarga);
    if(vagao == NULL){
        return;
    }
    if(trem->vagaoInicio == NULL){
        trem->vagaoInicio = vagao;
        trem->vagaoFinal = vagao;
        trem->sizeTrem++;
        atualizaPosicoes(trem);
    }else{
        int posicao;
        printf("Em qual posição deseja inserir o vagão? (0 até %i)", trem->sizeTrem);
        scanf("%i", &posicao);
        while(posicao < 0 || posicao > trem->sizeTrem) { //verificar depois
            printf("Erro! Posição inválida\n");
            printf("Digite uma posição válida (0 até %d): ", trem->sizeTrem);
            scanf("%d", &posicao);
        }
        int i = 0;
        Vagao *vagaoAtual = trem->vagaoInicio;
        if(posicao <= 0){
            vagao->prox = trem->vagaoInicio;
            trem->vagaoInicio->ant = vagao;
            trem->vagaoInicio = vagao;
        }else if(posicao >= trem->sizeTrem){
            trem->vagaoFinal->prox = vagao;
            vagao->ant = trem->vagaoFinal;
            trem->vagaoFinal = vagao;
        }else{
            while (vagaoAtual != NULL && vagaoAtual->posicao < posicao){
                vagaoAtual = vagaoAtual->prox;
            }
            vagao->prox = vagaoAtual;
            vagao->ant = vagaoAtual->ant;
            if(vagaoAtual->ant != NULL){
                vagaoAtual->ant->prox = vagao;
            }
            vagaoAtual->ant = vagao;
            if(vagaoAtual == trem->vagaoInicio){
                trem->vagaoInicio = vagao;
            }
        }
    }
    trem->sizeTrem++;
    atualizaPosicoes(trem);
}
void insereVagaoFim(Trem *trem, double capacidade, char const *tipoCarga){
    if(trem == NULL){
        return;
    }
    Vagao *vagao = createVagao(capacidade, tipoCarga);
    if(vagao == NULL){
        return;
    }
    if(trem->vagaoInicio == NULL){
        trem->vagaoInicio = vagao;
        trem->vagaoFinal = vagao;
        trem->sizeTrem++;
        atualizaPosicoes(trem);
    }else{
        trem->vagaoFinal->prox = vagao;
        vagao->ant = trem->vagaoFinal;
        trem->vagaoFinal = vagao;
        trem->sizeTrem++;
        atualizaPosicoes(trem);
    }
}

void removeUmVagao(Trem *trem){
    if (trem == NULL || trem->vagaoInicio == NULL) {
        printf("Trem vazio ou inexistente.\n");
        return;
    }
    int posicao = 0;
    printf("Qual vagão deseja remover? (0 até %i)", trem->sizeTrem);
    scanf("%d", &posicao);
    while(posicao < 0 || posicao > trem->sizeTrem - 1) {
        printf("Erro! Posição inválida\n");
        printf("Digite uma posição válida (0 até %d): ", trem->sizeTrem);
        scanf("%d", &posicao);
    }
    Vagao *vagaoAtual = trem->vagaoInicio;
    if(posicao == 0){
        if(trem->vagaoInicio->prox == NULL){
            trem->vagaoInicio = NULL;
            trem->vagaoFinal = NULL;
        }else{
            vagaoAtual->prox->ant = NULL;
            trem->vagaoInicio = vagaoAtual->prox;
        }
        free(vagaoAtual);
    }else if(posicao == trem->sizeTrem - 1){
        vagaoAtual = trem->vagaoFinal;
        trem->vagaoFinal = vagaoAtual->ant;
        if (trem->vagaoFinal != NULL){
            trem->vagaoFinal->prox = NULL;
        }else{
            trem->vagaoInicio = NULL;
        }
        free(vagaoAtual);
    }else{
        while(vagaoAtual != NULL && vagaoAtual->posicao < posicao){
            vagaoAtual = vagaoAtual->prox;
        }
        vagaoAtual->ant->prox = vagaoAtual->prox;
        vagaoAtual->prox->ant = vagaoAtual->ant;
        free(vagaoAtual);
    }
    trem->sizeTrem--;
    atualizaPosicoes(trem);
}
void removeVariosVagoes(Trem *trem){
    if (trem == NULL || trem->vagaoInicio == NULL) {
        printf("Trem vazio ou inexistente.\n");
        return;
    }
    Vagao *vagaoAtual = trem->vagaoInicio;
    while(vagaoAtual != NULL){
        trem->vagaoInicio = trem->vagaoInicio->prox;
        free(vagaoAtual);
        vagaoAtual = trem->vagaoInicio;
    }
    trem->sizeTrem = 0;
    trem->vagaoInicio = NULL;
    trem->vagaoFinal = NULL;
}

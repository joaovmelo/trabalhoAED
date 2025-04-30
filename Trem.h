#ifndef TREM_H
#define TREM_H

#include <stdlib.h>
#include <stdio.h>

typedef struct _vagoes{
    double capacidadeTotal;
    char tipoCarga[100];
    int posicao;
    struct _vagoes *prox;
    struct _vagoes *ant;
}Vagao;

typedef struct _trem{
    int sizeTrem;
    Vagao *vagaoInicio;
    Vagao *vagaoFinal;
    struct _trem *prox;
}Trem;
Trem *createTrem();
Vagao *createVagao(double capacidade, const char *tipoCarga);
void atualizaPosicoes(Trem *trem);
void insereVagaoMeio(Trem *trem, double capacidade, const char *tipoCarga);
void insereVagaoInicio(Trem *trem, double capacidade, const char *tipoCarga);
void insereVagaoFim(Trem *trem, double capacidade, const char *tipoCarga);
void maiorCapacidadeTotal(Trem *trem);
void vagoesOrdenadosPorTipoCarga(Trem *trem);
void removeUmVagao(Trem *trem);
void removeVariosVagoes(Trem *trem);
void listarVagoes(Trem *trem);
void addTrem(Trem *trem);
void removeTrem(Trem *trem);
int minMax(int posicao, int tamanho);

#endif
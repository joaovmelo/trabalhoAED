#ifndef TREM_H
#define TREM_H

#include "Vagao.h"

struct _trem {
    int sizeTrem;
    Vagao *vagaoInicio;
    Vagao *vagaoFinal;
    struct _trem *prox;
};

Trem* criarTrem();
void destruirTrem(Trem *trem);
void adicionarTrem(Trem **listaTrens);
void removerTrem(Trem **listaTrens);
void listarTrens(Trem *listaTrens);
Trem* selecionarTrem(Trem *listaTrens);
int contarTrens(Trem *listaTrens);
void destruirTodosTrens(Trem *listaTrens);
#endif
#ifndef INTERFACE_H
#define INTERFACE_H

#include "Trem.h"

void mostrarMenuPrincipal();
void menuTrens(Trem **listaTrens);
void menuVagoes(Trem *listaTrens);
void menuOperacoesVagoes(Trem *trem);

#endif
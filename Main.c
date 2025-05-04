#include <stdio.h>
#include <stdlib.h>
#include "Trem.h"
#include "Vagao.h"
#include "Interface.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    Trem *listaTrens = NULL;
    int opcao;
    
    do {
        mostrarMenuPrincipal();
        printf("\nEscolha do menu: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                menuTrens(&listaTrens);
                break;
            case 2:
                menuVagoes(listaTrens);
                break;
            case 0:
                destruirTodosTrens(listaTrens);
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    while (listaTrens != NULL) {
        Trem *prox = listaTrens->prox;
        destruirTrem(listaTrens);
        listaTrens = prox;
    }
    
    return 0;
}
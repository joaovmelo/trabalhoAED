#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Interface.h"
#include "Trem.h"
#include "Vagao.h"
#include <locale.h>

// Funções utilitárias para leitura de dados
static int lerInt(const char *prompt) {
    int valor;
    printf("%s", prompt);
    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida! %s", prompt);
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return valor;
}

static double lerDouble(const char *prompt) {
    double valor;
    printf("%s", prompt);
    while (scanf("%lf", &valor) != 1) {
        printf("Entrada inválida! %s", prompt);
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return valor;
}

static void lerString(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

// Menu principal
void mostrarMenuPrincipal() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    printf("\n=== SISTEMA DE GERENCIAMENTO DE TRENS ===\n");
    printf("1. Gerenciar Trens\n");
    printf("2. Gerenciar Vagoes\n");
    printf("0. Sair\n");
}

// Menu de trens
void menuTrens(Trem **listaTrens) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao;
    do {
        printf("1. Adicionar trem\n");
        printf("2. Remover trem\n");
        printf("3. Listar trens\n");
        printf("0. Sair\n");
        opcao = lerInt("Escolha uma opcao: ");
        switch (opcao) {
            case 1:
                adicionarTrem(listaTrens);
                break;
            case 2:
                removerTrem(listaTrens);
                break;
            case 3:
                listarTrens(*listaTrens);
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida!\n");
        }
    } while (1);
}

// Menu de operações de vagões
void menuOperacoesVagoes(Trem *trem) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao;
    do {
        printf("\n=== GERENCIAMENTO DE VAGOES ===\n");
        printf("Trem com %d vagoes\n", trem->sizeTrem);
        printf("1. Inserir Vagao no inicio\n");
        printf("2. Inserir Vagao em posicao especifica\n");
        printf("3. Inserir Vagao no final\n");
        printf("4. Remover Vagao\n");
        printf("5. Listar Vagoes\n");
        printf("6. Mostrar Vagao com maior Capacidade\n");
        printf("7. Ordenar Vagoes por tipo de carga\n");
        printf("0. Voltar\n");
        opcao = lerInt("Escolha uma opcao: ");
        switch (opcao) {
            case 1: {
                double cap = lerDouble("Capacidade do vagao: ");
                char tipo[100];
                lerString("Tipo de carga: ", tipo, sizeof(tipo));
                inserirVagaoInicio(trem, cap, tipo);
                break;
            }
            case 2: {
                int posicao;
                printf("Em qual posicao deseja inserir o vagao? (0 ate %i)", trem->sizeTrem);
                scanf("%i", &posicao);
                while(posicao < 0 || posicao > trem->sizeTrem) { //verificar depois
                    printf("Erro! Posição invalida\n");
                    printf("Digite uma posicao valida (0 ate %d): ", trem->sizeTrem);
                    scanf("%d", &posicao);
                }
                double cap = lerDouble("Capacidade do vagao: ");
                char tipo[100];
                lerString("Tipo de carga: ", tipo, sizeof(tipo));
                inserirVagaoPosicao(trem, cap, tipo, posicao);
                break;
            }
            case 3: {
                double cap = lerDouble("Capacidade do vagao: ");
                char tipo[100];
                lerString("Tipo de carga: ", tipo, sizeof(tipo));
                inserirVagaoFim(trem, cap, tipo);
                break;
            }
            case 4: {
                int posicao;
                printf("Em qual posicao deseja remover o vagao? (0 ate %i): ", trem->sizeTrem - 1);
                scanf("%i", &posicao);
                while(posicao < 0 || posicao > trem->sizeTrem) { //verificar depois
                    printf("Erro! Posicao invalida\n");
                    printf("Digite uma posicao valida (0 ate %d): ", trem->sizeTrem - 1);
                    scanf("%d", &posicao);
                }
                removerVagaoPosicao(trem, posicao);
                break;
            }
            case 5:
                listarVagoes(trem);
                break;
            case 6:
                maiorCapacidade(trem);
                break;
            case 7:
                ordenarPorTipoCarga(trem);
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida!\n");
        }
    } while (1);
}

// Chama o menu de operações de vagões após selecionar trem
void menuVagoes(Trem *listaTrens) {
    Trem *selecionado = selecionarTrem(listaTrens);
    if (selecionado != NULL) {
        menuOperacoesVagoes(selecionado);
    }else{
        printf("Escolha um trem primeiro.");
    }
}

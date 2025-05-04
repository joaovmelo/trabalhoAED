#ifndef VAGAO_H
#define VAGAO_H

typedef struct _trem Trem;  

typedef struct _vagao {
    double capacidadeTotal;
    char tipoCarga[100];
    int posicao;
    struct _vagao *prox;
    struct _vagao *ant;
} Vagao;

void inserirVagaoInicio(Trem *trem, double capacidade, const char *tipoCarga);
void inserirVagaoPosicao(Trem *trem, double capacidade, const char *tipoCarga, int posicao);
void inserirVagaoFim(Trem *trem, double capacidade, const char *tipoCarga);
void removerVagaoPosicao(Trem *trem, int posicao);
void limparVagoes(Trem *trem);
void listarVagoes(Trem *trem);
void maiorCapacidade(Trem *trem);
void ordenarPorTipoCarga(Trem *trem);
void atualizarPosicoes(Trem *trem);

#endif
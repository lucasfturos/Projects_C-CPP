#include "Dificuldade.h"

void Dificuldade::Jogar(const unique_ptr<Tabuleiro> &tab, int opc) {
    switch (opc) {
    case 1:
        Easy(tab);
        break;
    case 2:
        Hard(tab);
        break;
    default:
        break;
    }
}

void Dificuldade::Easy(const unique_ptr<Tabuleiro> &tab) {
    int linha, coluna;
    do {
        linha = rand() % MAX;
        coluna = rand() % MAX;
    } while (tab->tabuleiro[linha][coluna] != 0);
    tab->tabuleiro[linha][coluna] = -1;
}

void Dificuldade::Hard(const unique_ptr<Tabuleiro> &tab) { Easy(tab); }

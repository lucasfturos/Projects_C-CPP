#include "Jogador.h"

void Jogador::Jogar(const unique_ptr<Tabuleiro> &tab) {
    int pos;
    do {
        std::cout << "\nComo Demonstra o Tabuleiro Acima\nInforme a Posição "
                     "que Deseja :";
        std::cin >> pos;
    } while (pos > 9 || pos < 1);
    Logic(tab, pos);
}

void Jogador::Logic(const unique_ptr<Tabuleiro> &tab, int pos) {
    int linha = (pos - 1) / 3;
    int coluna = (pos - 1) % 3;

    tab->tabuleiro[linha][coluna] = 1;
}
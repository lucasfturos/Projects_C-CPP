#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <iostream>
#include <vector>

#define MAX 3

class Tabuleiro {
  public:
    Tabuleiro();

    std::vector<std::vector<int>> tabuleiro;

    friend class Jogador;
    friend class Computador;

    bool situacao(int player, int vezes);
    void drawBoard();
    void viewPosition();
};

#endif // TABULEIRO_H
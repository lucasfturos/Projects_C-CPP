#ifndef JOGADOR_H
#define JOGADOR_H

#include "../Tabuleiro/Tabuleiro.h"
#include <memory>

using std::unique_ptr;

class Jogador {
  public:
    void Jogar(const unique_ptr<Tabuleiro> &tab);
    void Logic(const unique_ptr<Tabuleiro> &tab, int pos);
};

#endif // JOGADOR_H
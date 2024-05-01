#ifndef COMPUTADOR_H
#define COMPUTADOR_H

#include "../Tabuleiro/Tabuleiro.h"
#include <memory>

using std::unique_ptr;

class Computador {
  public:
    virtual void Jogar(const unique_ptr<Tabuleiro> &tab, int opc) = 0;
};

#endif // COMPUTADOR_H
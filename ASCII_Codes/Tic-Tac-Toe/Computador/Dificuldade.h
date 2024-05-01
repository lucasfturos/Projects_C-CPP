#ifndef DIFICULDADE_H
#define DIFICULDADE_H

#include "Computador.h"

class Dificuldade : public Computador {
  public:
    void Jogar(const unique_ptr<Tabuleiro> &tab, int opc) override;
    void Easy(const unique_ptr<Tabuleiro> &tab);
    void Hard(const unique_ptr<Tabuleiro> &tab);
};

#endif // DIFICULDADE_H
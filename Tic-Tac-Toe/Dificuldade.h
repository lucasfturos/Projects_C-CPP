#ifndef DIFICULDADE_H

class Dificuldade : public Computador {
  public:
    void Jogar(Tabuleiro &tab, int opc) {
        if (opc == 1)
            Easy(tab);
        else if (opc == 2)
            Hard(tab);
    }

    void Easy(Tabuleiro &tab) {
        bool marcou = false;
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (tab.tabuleiro[i][j] != 1 && tab.tabuleiro[i][j] != -1) {
                    if (marcou == false) {
                        tab.tabuleiro[i][j] = -1;
                        marcou = true;
                    }
                }
            }
        }
    }
    void Hard(Tabuleiro &tab) {
        bool marcou = false;
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (tab.tabuleiro[i][j] != 1 && tab.tabuleiro[i][j] != -1) {
                    if (marcou == false) {
                        tab.tabuleiro[i][j] = -1;
                        marcou = true;
                    }
                }
            }
        }
    }
};

#endif

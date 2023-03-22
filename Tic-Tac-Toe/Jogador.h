#ifndef JOGADOR_H

class Jogador {
  public:
    virtual void Jogar(Tabuleiro &tab) {

        int pos;
        do {
            cout << "\nComo Demonstra o Tabuleiro Acima\nInforme a Posição que "
                    "Deseja :";
            cin >> pos;
        } while (pos > 9 || pos < 1);

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (pos == 1 && tab.tabuleiro[0][0] != 1 &&
                    tab.tabuleiro[0][0] != -1)
                    tab.tabuleiro[0][0] = 1;
                else if (pos == 2 && tab.tabuleiro[0][1] != 1 &&
                         tab.tabuleiro[0][1] != -1)
                    tab.tabuleiro[0][1] = 1;
                else if (pos == 3 && tab.tabuleiro[0][2] != 1 &&
                         tab.tabuleiro[0][2] != -1)
                    tab.tabuleiro[0][2] = 1;
                else if (pos == 4 && tab.tabuleiro[1][0] != 1 &&
                         tab.tabuleiro[1][0] != -1)
                    tab.tabuleiro[1][0] = 1;
                else if (pos == 5 && tab.tabuleiro[1][1] != 1 &&
                         tab.tabuleiro[1][1] != -1)
                    tab.tabuleiro[1][1] = 1;
                else if (pos == 6 && tab.tabuleiro[1][2] != 1 &&
                         tab.tabuleiro[1][2] != -1)
                    tab.tabuleiro[1][2] = 1;
                else if (pos == 7 && tab.tabuleiro[2][0] != 1 &&
                         tab.tabuleiro[2][0] != -1)
                    tab.tabuleiro[2][0] = 1;
                else if (pos == 8 && tab.tabuleiro[2][1] != 1 &&
                         tab.tabuleiro[2][1] != -1)
                    tab.tabuleiro[2][1] = 1;
                else if (pos == 9 && tab.tabuleiro[2][2] != 1 &&
                         tab.tabuleiro[2][2] != -1)
                    tab.tabuleiro[2][2] = 1;
            }
        }
    }
};

#endif

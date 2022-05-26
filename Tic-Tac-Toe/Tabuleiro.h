#ifndef TABULEIRO_H

class Tabuleiro {
public:
    int tabuleiro[MAX][MAX] = {};

    friend class Jogador;
    friend class Computador;

    bool situacao(int player, int vezes) {
        if (((tabuleiro[0][0] == player) && (tabuleiro[0][1] == player) && (tabuleiro[0][2] == player))
            || ((tabuleiro[1][0] == player) && (tabuleiro[1][1] == player) && (tabuleiro[1][2] == player))
            || ((tabuleiro[2][0] == player) && (tabuleiro[2][1] == player) && (tabuleiro[2][2] == player))
            || ((tabuleiro[0][0] == player) && (tabuleiro[1][0] == player) && (tabuleiro[2][0] == player))
            || ((tabuleiro[0][1] == player) && (tabuleiro[1][1] == player) && (tabuleiro[2][1] == player))
            || ((tabuleiro[0][2] == player) && (tabuleiro[1][2] == player) && (tabuleiro[2][2] == player))
            || ((tabuleiro[0][0] == player) && (tabuleiro[1][1] == player) && (tabuleiro[2][2] == player))
            || ((tabuleiro[2][0] == player) && (tabuleiro[1][1] == player) && (tabuleiro[0][2] == player))) {
            if (player == 1)
                cout << "\n\nJogador Ganhou";
            else if (player == -1)
                cout << "\n\nComputador Ganhou";
            drawBoard();
            exit(0);
            return true;
        }
        else if (vezes == 9) {
            cout << "Deu Velha!";
            drawBoard();
            exit(0);
            return true;
        }
        else return false;
    }

    void drawBoard() {
        cout << "\n\nTabuleiro\n";
        for (int i = 0; i < MAX; i++) {
            cout << "|";
            for (int j = 0; j < MAX; j++) {
                if (tabuleiro[i][j] == 1)
                    cout << " X ";
                else if (tabuleiro[i][j] == -1)
                    cout << " O ";
                if (tabuleiro[i][j] == 0)
                    cout << " - ";
                if (j == 0 || j == 1)
                    cout << "|";
            }
            cout << "|\n";
        }
    }

    void viewPosition() {
        cout << "\nPosicoes do Tabuleiro\n";
        cout << "\n| 1 | 2 | 3 |\n| 4 | 5 | 6 |\n| 7 | 8 | 9 |\n";
    }
};
#endif
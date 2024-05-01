#include "Tabuleiro.h"

Tabuleiro::Tabuleiro() : tabuleiro(MAX, std::vector<int>(MAX, 0)) {}

bool Tabuleiro::situacao(int player, int vezes) {
    std::vector<std::vector<int>> winCombos = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Linhas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Colunas
        {0, 4, 8}, {2, 4, 6}             // Diagonais
    };

    for (const auto &combo : winCombos) {
        if (tabuleiro[combo[0] / MAX][combo[0] % MAX] == player &&
            tabuleiro[combo[1] / MAX][combo[1] % MAX] == player &&
            tabuleiro[combo[2] / MAX][combo[2] % MAX] == player) {
            std::cout << "\n\n";
            (player == 1) ? std::cout << "Jogador Ganhou!"
                          : std::cout << "Computador Ganhou!";
            drawBoard();
            exit(0);
            return true;
        }
    }

    if (vezes == MAX * MAX) {
        std::cout << "\nDeu Velha!";
        drawBoard();
        exit(0);
        return true;
    }

    return false;
}

void Tabuleiro::drawBoard() {
    std::cout << "\n\nTabuleiro\n";
    for (int i = 0; i < MAX; i++) {
        std::cout << '|';
        for (int j = 0; j < MAX; j++) {
            if (tabuleiro[i][j] == 1)
                std::cout << " X ";
            else if (tabuleiro[i][j] == -1)
                std::cout << " O ";
            if (tabuleiro[i][j] == 0)
                std::cout << " - ";
            if (j == 0 || j == 1)
                std::cout << '|';
        }
        std::cout << "|\n";
    }
}

void Tabuleiro::viewPosition() {
    // std::cout << "\nPosicoes do Tabuleiro\n";
    // std::cout << "\n| 1 | 2 | 3 |\n| 4 | 5 | 6 |\n| 7 | 8 | 9 |\n";
    std::cout << "\nPosicoes do Tabuleiro\n";
    int count = 1;
    for (int i = 0; i < MAX; i++) {
        std::cout << "|";
        for (int j = 0; j < MAX; j++) {
            std::cout << " " << count++ << " ";
            if (j < MAX - 1)
                std::cout << "|";
        }
        std::cout << "|\n";
    }
}
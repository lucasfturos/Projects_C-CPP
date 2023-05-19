#include "termtetris.hpp"

auto TermTetris::scoreLimit() -> std::string {
    setScore();
    switch (score) {
    case 10 ... 99:
        return "\b\b\bSCORE: " + std::to_string(score);
    case 100 ... 999:
        return "\b\b\b\bSCORE: " + std::to_string(score);
    case 1000 ... 9999:
        return "\b\b\b\b\bSCORE: " + std::to_string(score);
    case 10000 ... 99999:
        return "\b\b\b\b\b\bSCORE: " + std::to_string(score);
    case 100000 ... 999999:
        return "\b\b\b\b\b\b\bSCORE: " + std::to_string(score);
    case 1000000 ... 9999999:
        return "\b\b\b\b\b\b\b\bSCORE: " + std::to_string(score);
    case 10000000 ... 99999999:
        return "\b\b\b\b\b\b\b\b\bSCORE: " + std::to_string(score);
    case 100000000 ... 999999999:
        return "\b\b\b\b\b\b\b\b\b\bSCORE: " + std::to_string(score);
    default:
        return "\b\bSCORE: " + std::to_string(score);
    }
}

auto TermTetris::setScore() -> void {
    int match{lines - 1};
    for (auto i = match; i >= 1; --i) {
        bool fullRow = true;
        for (auto j{0}; j < cols; ++j) {
            if (!board[i][j]) {
                fullRow = false;
                break;
            }
        }
        if (fullRow) {
            // Remover a linha completa
            for (auto k = i; k > 0; --k) {
                for (auto j{0}; j < cols; ++j) {
                    board[k][j] = board[k - 1][j];
                }
            }
            // Preencher a primeira linha com espaços vazios
            for (auto j{0}; j < cols; ++j) {
                board[0][j] = false;
            }
            ++score;
            ++match; // Ajustar a posição das linhas acumuladas
        }
    }
}

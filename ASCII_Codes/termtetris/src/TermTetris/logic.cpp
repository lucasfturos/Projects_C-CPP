#include "termtetris.hpp"

auto TermTetris::spawPiece() -> void {
    int number = std::rand() % shapes;
    for (auto i{0}; i < squares; ++i) {
        z[i].x = forms[number][i] % 2;
        z[i].y = (lines - 4) / 2 + forms[number][i] / 2;
    }
}

auto TermTetris::changePosition() -> void {
    if (move_down) {
        for (auto i{0}; i < squares; ++i) {
            ++z[i].x;
        }
    }

    for (auto i{0}; i < squares; ++i) {
        k[i] = z[i];
        z[i].y += diry * 2;
    }

    if (maxLimit()) {
        for (auto i{0}; i < squares; ++i) {
            z[i] = k[i];
        }
    }
}

auto TermTetris::moveToDown() -> void {
    if (timercount < start) {
        for (auto i{0}; i < squares; ++i) {
            ++z[i].x;
        }

        if (maxLimit()) {
            for (auto i{0}; i < squares; ++i) {
                board[z[i].x - 1][z[i].y] = true;
            }

            bool line_cleared = false;
            for (auto i{lines - 2}; i > 0; --i) {
                bool full_line = true;
                for (auto j{1}; j < cols - 1; ++j) {
                    if (!board[i][j]) {
                        full_line = false;
                        break;
                    }
                }

                if (full_line) {
                    line_cleared = true;
                    for (auto k{i}; k > 0; --k) {
                        for (auto j{1}; j < cols - 1; ++j) {
                            board[k][j] = board[k - 1][j];
                        }
                    }
                    for (auto j{1}; j < cols - 1; ++j) {
                        board[0][j] = false;
                    }
                }
            }

            if (line_cleared) {
                score += 10;
            }

            spawPiece();
            checkGameOver(); 
        }
        timercount = 0;
    }
}

auto TermTetris::setRotate() -> void {
    if (rotate) {
        Coords coords = z[1];
        for (auto i{0}; i < squares; ++i) {
            int x = z[i].y - coords.y;
            int y = z[i].x - coords.x;

            z[i].x = coords.x - x;
            z[i].y = coords.y + y;
        }

        if (maxLimit()) {
            for (auto i{0}; i < squares; ++i) {
                z[i] = k[i];
            }
        }
    }
}

auto TermTetris::checkGameOver() -> void {
    for (auto i = 0; i < squares; ++i) {
        if (z[i].y < 1) {
            gameover = true;
            return;
        }
    }
}

#include "termtetris.hpp"

auto TermTetris::events() -> void {
    if (KbhitGetch::kbhit()) {
        switch (KbhitGetch::getch()) {
        case 'w':
            rotate = true;
            break;
        case 'a':
            --diry;
            break;
        case 'd':
            ++diry;
            break;
        case 's':
            move_down = 1;
            break;
        case 'c':
            start++;
            break;
        case 'x':
            gameover = true;
            break;
        default:
            break;
        }
    }
}

auto TermTetris::resetValues() -> void {
    diry = move_down = 0;
    rotate = false;
}

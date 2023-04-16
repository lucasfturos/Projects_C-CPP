#include "termtetris.hpp"

auto TermTetris::logoGameOver() -> void {
    // Site
    // https://patorjk.com/software/taag/#p=display&f=ANSI%20Regular&t=GAME%20OVER
    std::cout << "\033[1;31m"
              << R"(
 ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████  
██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██ 
██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████  
██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██ 
 ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██ 
    )"
              << "\033[0m" << '\n';
}

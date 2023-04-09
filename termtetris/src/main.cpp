#include <TermTetris/termtetris.hpp>

auto main() -> int {
    auto tt{std::make_shared<TermTetris>()};
    tt->run();
}

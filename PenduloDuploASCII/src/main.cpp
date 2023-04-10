#include <pendulo/pendulo.hpp>

int main() {
    auto p{std::make_shared<Pendulo>()};
    // Loop principal
    while (true) {
        std::cout << "\033c";
        p->draw();
    }
}

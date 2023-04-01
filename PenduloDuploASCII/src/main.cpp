#include <pendulo/pendulo.hpp>

int main() {
    Pendulo p;
    // Loop principal
    while (true) {
        std::cout << "\033c";
        p.draw();
    }
}

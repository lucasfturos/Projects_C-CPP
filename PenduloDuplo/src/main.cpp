#include "pendulo/pendulo.hpp"

int main() {
    Pendulo p;
    while (true) {
        p.draw();
        std::printf(p.canvas[0]);
        std::getchar();
    }
}

#include "pendulo/pendulo.hpp"

int main() {
    Pendulo p;
    p.canvasSetup();
    p.traceSetup();
    while (true) {
        p.draw();
    }
    return 0;
}


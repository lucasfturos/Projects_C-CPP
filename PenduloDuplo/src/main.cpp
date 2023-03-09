#include "plot/plot.hpp"
#include "timer/timer.hpp"
#include "pendulo/pendulo.hpp"

int main() {
  Pendulo p;
  // Loop principal
  while (true) {
    system("clear");
    p.draw();
  }
}

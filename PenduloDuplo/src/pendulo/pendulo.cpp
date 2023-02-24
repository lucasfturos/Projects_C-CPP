#include "pendulo.hpp"

void Pendulo::draw() {
    constexpr std::uint32_t WIDTH{d.WIDTH};
    constexpr std::uint32_t HEIGHT{d.HEIGHT};
    constexpr std::uint32_t dW{d.dW};
    constexpr std::uint32_t dH{d.dH};


    std::array<std::array<std::string, HEIGHT / dH>, WIDTH / dW + 1> platno;
    
    for (std::size_t i{}; i < HEIGHT / dH - 1; ++i) {
      platno[i][WIDTH / dW] = "\n";
    }
    
    platno[HEIGHT / dH - 1][WIDTH / dW] = "\0";
  
    for (std::size_t i{}; i < HEIGHT / dH; ++i) {
      for (std::size_t j{}; j < WIDTH / dW; ++j) {
          platno[i][j] = " ";
      }
    }

    std::array<std::array<std::uint32_t, HEIGHT / dH>, WIDTH / dW> trace;
    
    for (std::size_t i{}; i < HEIGHT / dH; i++) {
      for (std::size_t j{}; j < WIDTH / dW; ++j) {
          trace[i][j] = 0;
      }
    }

    // loop 
    while (true) {
      system("clear");
      d.gotoxy(0, 0);


      
    }
}

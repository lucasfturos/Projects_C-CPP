#include "Computador/Dificuldade.h"
#include "Jogador/Jogador.h"

int main() {
    auto tab = std::make_unique<Tabuleiro>();
    auto player = std::make_unique<Jogador>();
    unique_ptr<Computador> pc = std::make_unique<Dificuldade>();

    int opc;
    short rodada = 1;
    bool vez = false;
    do {
        std::cout << "*****Jogo da Velha*****\n\n"
                  << "Jogador: X e Computador : O\n\nEscolha a dificuldade\n"
                  << "Facil: 1 Dificil: 2\n"
                  << '\n';
        std::cin >> opc;
    } while ((opc < 1) || (opc > 2));
    std::cout << "\033c";
    while (true) {
        std::cout << "\n\nRodada: " << rodada << '\n';
        if (vez == false) {
            std::cout << "\nJogador" << '\n';
            tab->viewPosition();
            player->Jogar(tab);
            tab->situacao(1, rodada);
            vez = true;
        }
        rodada += 1;
        std::cout << "\n\nRodada: " << rodada << '\n';
        if (vez == true) {
            std::cout << "\nComputador" << '\n';
            pc->Jogar(tab, opc);
            tab->situacao(-1, rodada);
            tab->drawBoard();
            vez = false;
        }
        rodada += 1;
    }
    return 0;
}

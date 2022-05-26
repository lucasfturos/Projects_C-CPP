#define MAX 3
#include <random>
#include <iostream>
using namespace std;
#include "Tabuleiro.h"
#include "Jogador.h"
#include "Computador.h"
#include "Dificuldade.h"

int main() {
    Tabuleiro tab;
    Jogador player;
    Computador* pc = new Dificuldade();

    int opc;
    short rodada = 0;
    bool vez = false;
    do {
        cout << "*****Jogo da Velha*****\n\n" <<
            "Jogador: X e Computador : O\n\nEscolha a dificuldade\n" <<
            "Facil: 1 Dificil: 2\n" << endl;
        cin >> opc;
    } while ((opc < 1) || (opc > 2));
    system("cls || clear");
    while (true) {
        cout << "\n\nRodada: " << rodada + 1 << endl;
        if (vez == false) {
            cout << "\nJogador" << endl;
            tab.viewPosition();
            player.Jogar(tab);
            if (tab.situacao(1, rodada));
            vez = true;
        }
        if (vez == true) {
            cout << "\nComputador" << endl;
            pc->Jogar(tab, opc);
            if (tab.situacao(-1, rodada));
            tab.drawBoard();
            vez = false;
        }
        rodada += 1;
    }
    return 0;
}

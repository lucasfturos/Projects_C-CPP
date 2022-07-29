//  Natal.C
//  Imprime uma árvore de Natal
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int main() {
    char folha = '#';
    int i, k, j;
    system("clear");
    printf("\n\n"); // Pula 2 linhas antes do inicio do desenho

    for (i = 0; i < 4; i++) {
        for (k = 1; k < 5; k++) {
            for (j = 1; j <= 40 - (2 * i + k); j++)
                printf(" "); // Imprime em branco
            printf("/"); // Delimitador inicial da linha

            for (j = 1; j < (2 * i + k); j++)
                printf("%c", folha); // Até o meio

            for (j = 1; j < (2 * i + k); j++)
                printf("%c", folha); //Meio ao final da linha
            printf("\\\n"); // Delimitador final da linha
        }
    }
    // Desenha o pé da árvore
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 38; j++) printf(" ");
        printf("|  |\n");
    }
    printf("\n");

    for (j = 0; j < 35; j++) printf(" ");
    printf("FELIZ NATAL\n");
    for (j = 0; j < 31; j++) printf(" ");
    printf("E UM PROSPERO ANO!\n");
    return 0;
}
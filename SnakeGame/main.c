#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include "kbhitgetch.h"
#elif _WIN32
#include <conio.h>
#endif
#define w 40
#define h 40

int camp[w][h] = {}, i, j, k, flag, defeat, point;
int x, y, appleX, appleY, tailX[100], tailY[100], nTail;

void setup() {
    point = 0;
    x = w / 2;
    y = h / 2;
    defeat = 0;
    appleX = rand() % w;
    appleY = rand() % h;
}

void clean() {
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            if (i == 0 || i == w - 1 || j == 0 || j == h - 1)
                camp[i][j] = '#';

            else
                camp[i][j] = ' ';

            if (i == y && j == x)
                camp[i][j] = '0';

            else if (j == appleX && i == appleY)
                camp[i][j] = '@';

            else {
                int print = 1;
                for (k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        camp[i][j] = '0';
                        print = 0;
                    }
                }
            }
        }
    }
}

void draw() {
    system("clear || cls");
    printf("\nSnake Game\n\n");
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            printf("%c", camp[i][j]);
        }
        printf("\n");
    }
    printf("\n\nPoints = %d\nClick X to Exit Game\n\n", point);
}

void input() {
    if (kbhit()) {
        switch (getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            defeat = 1;
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (k = 1; k < nTail; k++) {
        prev2X = tailX[k];
        prev2Y = tailY[k];
        tailX[k] = prevX;
        tailY[k] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
    case 1:
        x--;
        break;
    case 2:
        y++;
        break;
    case 3:
        x++;
        break;
    case 4:
        y--;
        break;
    default:
        break;
    }

    if (x < 0 || x > w - 2 || y < 0 || y > h - 2)
        defeat = 1;

    for (k = 0; k < nTail; k++) {
        if (tailX[k] == x && tailY[k] == y)
            defeat = 1;
    }

    if (x == appleX && y == appleY) {
        point += 10;
        appleX = rand() % w;
        appleY = rand() % h;
        nTail++;
    }
}

int main() {
    setup();
    while (!defeat) {
        clean();
        draw();
        input();
        logic();
        usleep(60000);
    }
}

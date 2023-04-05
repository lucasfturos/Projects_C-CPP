#include "main.h"

void setup() {
    score = 0;
    p.x = w / 2;
    p.y = h / 2;
    defeat = 0;
    apple.x = rand() % w;
    apple.y = rand() % h;
}

void clean() {
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            if (i == 0 || i == w - 1 || j == 0 || j == h - 1) {
                camp[i][j] = '#';
            } else {
                camp[i][j] = ' ';
            }
            if (i == p.y && j == p.x) {
                camp[i][j] = '0';
            } else if (j == apple.x && i == apple.y) {
                camp[i][j] = '@';
            } else {
                int print = 1;
                for (k = 0; k < nTail; k++) {
                    if (tail[k].x == j && tail[k].y == i) {
                        camp[i][j] = '0';
                        print = 0;
                    }
                }
            }
        }
    }
}

void draw() {
    printf("\033c");
    printf("\nSnake Game\n\n");
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            printf("%c", camp[i][j]);
        }
        printf("\n");
    }
    printf("\n\nPoints = %d\nClick X to Exit Game\n\n", score);
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
            printf("\033c");
            break;
        }
    }
}

void logic() {
    int prevX = tail[0].x;
    int prevY = tail[0].y;
    int prev2X, prev2Y;

    tail[0].x = p.x;
    tail[0].y = p.y;

    for (k = 1; k < nTail; k++) {
        prev2X = tail[k].x;
        prev2Y = tail[k].y;
        tail[k].x = prevX;
        tail[k].y = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
    case 1:
        p.x--;
        break;
    case 2:
        p.y++;
        break;
    case 3:
        p.x++;
        break;
    case 4:
        p.y--;
        break;
    default:
        break;
    }

    if (p.x < 1 || p.x > w - 2 || p.y < 1 || p.y > h - 2) {
        defeat = 1;
    }

    for (k = 0; k < nTail; k++) {
        if (tail[k].x == p.x && tail[k].y == p.y)
            defeat = 1;
    }

    if (p.x == apple.x && p.y == apple.y) {
        score += 10;
        apple.x = rand() % w;
        apple.y = rand() % h;
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

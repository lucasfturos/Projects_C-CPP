#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include "kbhitgetch.h"
#elif _WIN32
#include <conio.h>
#endif
#define w 20
#define h 50

struct Point {
    int x, y;
};

struct Point tail[100], apple, p;

int nTail, defeat, score;
int camp[w][h] = {}, i, j, k, flag;

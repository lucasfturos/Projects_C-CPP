#define _POSIX_C_SOURCE 199309L

#include "bitmap_cat.h"
#include <stdio.h>
#include <time.h>

#define WIDTH 128
#define HEIGHT 40

void drawBitmap(const u_int8_t *bitmap) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int byte_index = (y * WIDTH + x) / 8;
            int bit_index = 7 - (x % 8);
            (bitmap[byte_index] & (1 << bit_index)) ? printf("█")
                                                    : putchar(' ');
        }
        printf("\n");
    }
}

int main(void) {
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 250000000L};

    while (1) {
        printf("\033c");
        drawBitmap(pawsonair);
        nanosleep(&ts, NULL);

        printf("\033c");
        drawBitmap(rightpawontable);
        nanosleep(&ts, NULL);

        printf("\033c");
        drawBitmap(leftpawontable);
        nanosleep(&ts, NULL);

        printf("\033c");
        drawBitmap(pawsontable);
        nanosleep(&ts, NULL);
    }
    
    return 0;
}
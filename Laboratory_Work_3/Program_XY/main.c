#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 24
#define DELAY_MS 10

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} Arrow;

void delay(void);
void drawChar(int x, int y);
int moveArrow(Arrow *a);
int samePosition(const Arrow *first, const Arrow *second);

int main(void)
{
    Arrow first = {WIDTH, 1, -1, 1};
    Arrow second = {WIDTH, HEIGHT, -1, -1};

    printf("\033[2J\033[H");
    fflush(stdout);

    while (1) {
        if (moveArrow(&first)) break;
        if (samePosition(&first, &second)) {
            drawChar(second.x, second.y);
            break;
    }

        if (moveArrow(&second)) break;
        if (samePosition(&first, &second)) {
            drawChar(first.x, first.y);
            break;
        }
    }

    printf("\033[24;1H");
    getchar();
    return 0;
}


void delay(void)
{
    struct timespec ts = {0, DELAY_MS * 1000000L};
    nanosleep(&ts, NULL);
}


void drawChar(int x, int y)
{
    printf("\033[%d;%dH*", y, x);
    fflush(stdout);
    delay();
}


int moveArrow(Arrow *a)
{
    drawChar(a->x, a->y);

    a->x += a->dx;

    if (a->x < 1 || a->x > WIDTH) {
        a->x -= a->dx;
        a->y += a->dy;
        a->dx = -a->dx;

        // Не виходимо за межі робочої області
        if (a->x < 1 || a->x > WIDTH || a->y < 1 || a->y > HEIGHT) {
            return 1;
        }
    }

    return 0;
}


int samePosition(const Arrow *first, const Arrow *second) {
    return (first->x == second->x && first->y == second->y);
}

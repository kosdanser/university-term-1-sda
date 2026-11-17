#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DELAY_MS 10

typedef struct {
    int row;
    int col;
    int rowStep;
    int colStep;
} Arrow;

char** createMatrix (int rows, int cols);
void drawMatrix (char** matrix, int rows, int cols);
void delay(void);
int moveArrow (char** matrix, Arrow *arrow, int rows, int cols);
int hasCrossed (const Arrow *first, const Arrow *second);
void freeMatrix (char** matrix, int rows);

int main(void) {
    int cols;
    int rows;

    printf("Enter number of columns: ");
    if (scanf("%d", &cols) != 1) {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter number of rows: ");
    if (scanf("%d", &rows) != 1) {
        printf("Invalid input!\n");
        return 1;
    }

    if (cols <= 0 || rows <= 0) {
        printf("Invalid number of columns or rows\n");
        return 1;
    }
    getchar();

    printf("\033[2J\033[H");
    fflush(stdout);

    if (rows == 1) {
        Arrow single = {0, cols - 1, 0, -1};

        char** matrix = createMatrix(rows, cols);
        if (matrix == NULL) {
            return 1;
        }

        drawMatrix(matrix, rows, cols);
        delay();

        matrix[0][cols-1] = '#';
        drawMatrix(matrix, rows, cols);
        delay();

        while (1) {
            if (moveArrow(matrix, &single, rows, cols)) break;
            drawMatrix(matrix, rows, cols);
            delay();
            if (single.col == 0) break;
        }

        freeMatrix (matrix, rows);
        getchar();
        return 0;
    }

    Arrow first = {0, cols - 1, 1, -1};
    Arrow second = {rows - 1, cols - 1, -1, -1};

    //створити матрицю
    char** matrix = createMatrix(rows, cols);
    if (matrix == NULL) {
        return 1;
    }

    //вивести зображення початкової матриці
    drawMatrix(matrix, rows, cols);
    delay();

    //позначення початку стрілок
    matrix[0][cols-1] = '#';
    drawMatrix(matrix, rows, cols);
    delay();
    matrix[rows - 1][cols - 1] = '#';
    drawMatrix(matrix, rows, cols);
    delay();

    while (1) {
        if (moveArrow(matrix, &first, rows, cols)) {
            break;
        }
        if (hasCrossed(&first, &second)) {
            break;
        }
        drawMatrix(matrix, rows, cols);
        delay();

        if (moveArrow(matrix, &second, rows, cols)) {
            break;
        }
        if (hasCrossed(&first, &second)) {
            break;
        }
        drawMatrix(matrix, rows, cols);
        delay();
    }

    //звільнення пам`яті
    freeMatrix (matrix, rows);
    getchar();
    return 0;
}


char** createMatrix (int rows, int cols) {
    char** matrix = malloc(rows * sizeof(char *));
    if (matrix == NULL) {
        printf("Error allocating memory\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(char));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            printf("Error allocating memory\n");
            return NULL;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = '*';
        }
    }

    return matrix;
}


void drawMatrix(char** matrix, int rows, int cols) {
    printf("\033[H");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            putchar(matrix[i][j]);
        }
        if (i < rows - 1) {
            putchar('\n');
        }
    }

    fflush(stdout);
}


void delay(void)
{
    struct timespec ts = {0, DELAY_MS * 1000000L};
    nanosleep(&ts, NULL);
}


int moveArrow (char** matrix, Arrow *arrow, int rows, int cols) {
    arrow->col += arrow->colStep;

    if (arrow->col < 0 || arrow->col > cols - 1) {
        arrow->col -= arrow->colStep;
        arrow->row += arrow->rowStep;
        arrow->colStep = -arrow->colStep;

        if (arrow->row < 0 || arrow->row > rows - 1 || arrow->col < 0 || arrow->col > cols - 1) {
            return 1;
        }
    }

    matrix[arrow->row][arrow->col] = '#';

    return 0;
}

int hasCrossed (const Arrow *first, const Arrow *second) {
    return (first->row > second->row);
}

void freeMatrix (char** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

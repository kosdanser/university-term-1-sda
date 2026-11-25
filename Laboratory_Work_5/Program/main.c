#include <stdio.h>

int main() {
    int n = 10;
    int matrix[10][10] = {
        {12,  5,  8,  3,  17,  6,  9,  2,  14,  7},
        { 4, 15,  1,  11,  8,  19,  5,  13,  6,  10},
        {18,  7,  12,  4,  2,  16,  9,  1,  11,  5},
        { 3, 14,  6,  17,  9,  5,  20,  8,  2,  13},
        {10,  2,  19,  7,  15,  4,  12,  6,  18,  1},
        { 8, 16,  3,  11,  5,  14,  7,  19,  4,  12},
        { 1,  9,  17,  6,  13,  2,  15,  10,  5,  18},
        {14,  4,  10,  19,  7,  12,  3,  16,  8,  2},
        { 6, 18,  5,  13,  1,  9,  11,  4,  17,  15},
        { 9,  3,  14,  2,  16,  8,  18,  5,  10,  7}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 1; i < n; i++) {
        int key = matrix[i][n - 1 - i];
        int j = 0;
        while (j < i && key > matrix[j][n - 1 - j]) {
            j++;
        }
        for (int k = i; k > j; k--) {
            matrix[k][n - 1 - k] = matrix[k - 1][n - k];
        }
        matrix[j][n - 1 - j] = key;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

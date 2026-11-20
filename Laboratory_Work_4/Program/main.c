#include <stdio.h>

int checkLastRowSort(int rows, int cols, double matrix[rows][cols]);
int checkFirstColSort(int rows, int cols, double matrix[rows][cols]);
int searchLastRow(double x, int rows, int cols, double matrix[rows][cols]);
int searchFirstCol(double x, int rows, int cols, double matrix[rows][cols]);

int main() {
    int rows = 7;
    int cols = 7;
    double X;

    printf("Enter number to search: ");
    if (scanf("%lf", &X) != 1) {
        printf("Invalid input!\n");
        return 1;
    };

    double A[7][7] = {
        {1,  8,  3,  6,  4,  9,  2},
        {3,  5,  9,  2,  7,  4,  8},
        {5,  4,  8,  1,  6,  3,  7},
        {7,  9,  2,  5,  3,  8,  4},
        {9,  3,  6,  8,  4,  2,  5},
        {11, 7,  1,  4,  9,  6,  3},
        {13, 15, 17, 19, 21, 23, 25}
    };

    if (checkLastRowSort(rows, cols, A))
    {
        int result = searchLastRow(X, rows, cols, A);

        if (result != -1)
        {
            printf("Number found in the last row at coordinates: (%d, %d)\n",
                   rows, result + 1);
        }
        else
        {
            printf("Number not found in the last row.\n");
        }
    }
    else
    {
        printf("The last row is not sorted!\n");
    }

    if (checkFirstColSort(rows, cols, A))
    {
        int result = searchFirstCol(X, rows, cols, A);

        if (result != -1)
        {
            printf("Number found in the first column at coordinates: (%d, %d)\n",
                   result + 1, 1);
        }
        else
        {
            printf("Number not found in the first column.\n");
        }
    }
    else
    {
        printf("The first column is not sorted!\n");
    }

    return 0;
}

int checkLastRowSort(int rows, int cols, double matrix[rows][cols]) {
    for (int j = 0; j < cols - 1; j++) {
        if (matrix[rows - 1][j] > matrix[rows - 1][j + 1]) {
            return 0;
        }
    }
    return 1;
}

int checkFirstColSort(int rows, int cols, double matrix[rows][cols]) {
    for (int i = 0; i < rows - 1; i++) {
        if (matrix[i][0] > matrix[i + 1][0]) {
            return 0;
        }
    }
    return 1;
}

int searchLastRow(double X, int rows, int cols, double matrix[rows][cols]) {
    int left = 0;
    int right = cols - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (X == matrix[rows - 1][mid]) {
            return mid;
        }
        else if (X > matrix[rows - 1][mid]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

int searchFirstCol(double X, int rows, int cols, double matrix[rows][cols]) {
    int left = 0;
    int right = rows - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (X == matrix[mid][0]) {
            return mid;
        }
        else if (X < matrix[mid][0]) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return -1;
}

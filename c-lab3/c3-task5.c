/*Вводится натуральное число n (n⩽ 20). Заполнить матрицу (двумерный массив) раз-
мера n× n числами от 1 до n2 последовательно по спирали от левого верхнего угла по
часовой стрелке. Красиво выведите полученную таблицу.*/

#include <stdio.h>

void fillSpiral(int n, int matrix[n][n]) {
    int value = 1;
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;

    while (value <= n * n) {
        // Слева направо
        for (int i = left; i <= right; i++) {
            matrix[top][i] = value++;
        }
        top++;

        // Сверху вниз
        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = value++;
        }
        right--;

        // Справа налево
        for (int i = right; i >= left; i--) {
            matrix[bottom][i] = value++;
        }
        bottom--;

        // Снизу вверх
        for (int i = bottom; i >= top; i--) {
            matrix[i][left] = value++;
        }
        left++;
    }
}

void printMatrix(int n, int matrix[n][n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Введите размер матрицы (n <= 20): ");
    scanf("%d", &n);
    if (n <= 0 || n > 20) {
        printf("Некорректное значение\n");
        return 1;
    }

    int matrix[20][20]; // максимум 20×20

    fillSpiral(n, matrix);
    printf("Матрица %d * %d, заполненная по спирали:\n", n, n);
    printMatrix(n, matrix);

    return 0;
}

/*
Напишите функцию, которая принимает двумерный массив вещественных чисел (то
есть указатель типа double** и размеры), индексы i и j двух строк и величину α.
Функция должна прибавлять к i-й строке массива j-ю, умноженную на коэффици-
ент α. С использованием этой функции напишите функцию приведения матрицы к
верхнетреугольной форме. Задание исходного массива можно организовать через ввод
с клавиатуры, через явное присвоение в тексте программы или генерировать случайно
(см. задачи 1 и 4).
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 20
#define MAXM 20
#define EPS 1e-9

void transformMatrix(int n, int m, double A[MAXN][MAXM]) {
    // Найдём первую строку, у которой A[i][0] != 0
    int str = -1;
    for (int i = 0; i < n; ++i) {
        if (fabs(A[i][0]) > EPS) {
            str = i;
            break;
        }
    }


    // Меняем str-строку на первую (если нужно)
    if (str != 0) {
        for (int j = 0; j < m; ++j) {
            double tmp = A[0][j];
            A[0][j] = A[str][j];
            A[str][j] = tmp;
        }
    }

    // Делим первую строку на A[0][0] → чтобы A[0][0] = 1
    double factor = A[0][0];
    for (int j = 0; j < m; ++j) {
        A[0][j] /= factor;
    }

    // Обнуляем остальные элементы в первом столбце
    for (int i = 1; i < n; ++i) {
        double coeff = A[i][0];
        for (int j = 0; j < m; ++j) {
            A[i][j] -= coeff * A[0][j];
        }
    }
}

void printMatrix(int n, int m, double A[MAXN][MAXM]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%8.3f", A[i][j]);
        }
        printf("\n");
    }
}

void toUpperTriangular(int n, int m, double A[MAXN][MAXM]) {
    for (int k = 0; k < n && k < m; ++k) {
        // Ищем ведущий элемент в столбце k на позиции ≥ k
        int str = -1;
        for (int i = k; i < n; ++i) {
            if (fabs(A[i][k]) > EPS) {
                str = i;
                break;
            }
        }

        if (str == -1)
            continue; // Столбец нулевой, пропускаем

        // Меняем str-строку и k-строку местами
        if (str != k) {
            for (int j = 0; j < m; ++j) {
                double tmp = A[k][j];
                A[k][j] = A[str][j];
                A[str][j] = tmp;
            }
        }

        // Нормируем строку: делим на A[k][k]
        double factor = A[k][k];
        for (int j = 0; j < m; ++j) {
            A[k][j] /= factor;
        }

        // Обнуляем все строки ниже
        for (int i = k + 1; i < n; ++i) {
            double coeff = A[i][k];
            for (int j = 0; j < m; ++j) {
                A[i][j] -= coeff * A[k][j];
            }
        }
    }
}
int main() {
    int n, m;
    printf("Введите размеры матрицы n и m (<= 20): ");
    scanf("%d%d", &n, &m);

    double A[MAXN][MAXM];

    printf("Введите элементы матрицы %d × %d:\n", n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%lf", &A[i][j]);

    printf("\nИсходная матрица:\n");
    printMatrix(n, m, A);

    transformMatrix(n, m, A);
    printf("\nПосле приведения первого столбца к [1, 0, 0, ...]:\n");
    printMatrix(n, m, A);

    printf("\nПреобразование к верхнетреугольному виду:\n");
    toUpperTriangular(n, m, A);
    printMatrix(n, m, A);

    return 0;
}

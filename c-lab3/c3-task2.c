/*
Имеется массив типа unsigned char *, элементы которого является числами 1, 2 или 3.
Напишите функцию, сортирующую такой массив, которая изменяет его соответствую-
щим образом. (В таком случае сортировка сводится к подсчёту количеств элементов
каждого типа.) Для генерации используйте функцию, подобную функции из задачи 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char* GroupArray(unsigned char* arr, int n) {
    if (arr == NULL || n <= 0) return NULL;

    int count[4] = {0}; // индексы: 1, 2, 3 (count[0] не используется)

    // Считаем количество 1, 2 и 3
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 1 && arr[i] <= 3)
            count[arr[i]]++;
    }

    // Записываем заново в массив: сначала все 1, затем 2, затем 3
    int idx = 0;
    for (int val = 1; val <= 3; ++val) {
        for (int j = 0; j < count[val]; ++j) {
            arr[idx++] = val;
        }
    }

    return arr;
}

// Функция генерации массива значений 1, 2, 3
unsigned char* Generate123Array(int n) {
    if (n <= 0) return NULL;
    unsigned char* arr = malloc(n * sizeof(unsigned char));
    if (arr == NULL) return NULL;

    for (int i = 0; i < n; ++i) {
        arr[i] = 1 + rand() % 3; // случайное число 1, 2 или 3
    }

    return arr;
}


int main() {
    srand(time(NULL));
    int n = 20;
    unsigned char* arr = Generate123Array(n);

    printf("Исходный массив:\n");
    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
    printf("\n");

    GroupArray(arr, n);

    printf("После группировки:\n");
    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}

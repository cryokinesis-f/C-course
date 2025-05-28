/*
Напишитефункциюint *GenArray (int n, int a, int b),котораявыделяетпамять
под массив из n целых ячеек, заполняет его случайными целыми числами из диапазо-
на от a до b и возвращает результирующий указатель. Считаем, что a ⩽ b. В случае
ошибки выделения памяти верните NULL. Для генерации случайных чисел следует ис-
пользовать функцию rand(), определенную в библиотеке stdlib.h и возвращающую
целое 4-байтное случайное число.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция генерации массива случайных чисел от a до b
int* GenArray(int n, int a, int b) {
    if (a > b || n <= 0) return NULL;

    int* arr = malloc(n * sizeof(int));
    if (arr == NULL) return NULL;

    for (int i = 0; i < n; ++i) {
        arr[i] = a + rand() % (b - a + 1);
    }

    return arr;
}


int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int n = 10, a = 1, b = 100;
    int* arr = GenArray(n, a, b);
    
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr); // Не забываем освободить память
    return 0;
}

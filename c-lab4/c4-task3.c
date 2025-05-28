/*
Напишите функцию filter,которая принимает массив целых и унарную функцию-предикат и 
формирует новый массив из элементов исходного, удовлетворяющих переданному предикату. 
(Предикат возвращает целое число 0, если входное целое этому предикату не удовлетворяет, и не 0, если удовлетворяет. 
Блок под принимающий массив можно отводить с запасом.) 
Используя различные предикаты, отфильтруйте из исходного массива 
а) чётные числа; 
б) числа с нечётной суммой цифр; 
в) простые числа.
*/

#include <stdio.h>
#include <stdlib.h>

int isEven(int x) {
    return x % 2 == 0;
}

int sumDigits(int x) {
    if (x < 0) x = -x;
    int sum = 0;
    while (x) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int hasOddDigitSum(int x) {
    return sumDigits(x) % 2 == 1;
}

int isPrime(int x) {
    if (x < 2) return 0;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return 0;
    }
    return 1;
}


// Тип для предикат-функции
typedef int (*Predicate)(int);

// Функция filter
int* filter(const int* array, int length, Predicate predicate, int* newLength) {
    // Сначала подсчитаем количество подходящих элементов
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (predicate(array[i])) {
            ++count;
        }
    }

    // Выделим память под новый массив
    int* result = malloc(count * sizeof(int));
    if (result == NULL) {
        *newLength = 0;
        return NULL;
    }

    // Заполним результат
    int j = 0;
    for (int i = 0; i < length; ++i) {
        if (predicate(array[i])) {
            result[j++] = array[i];
        }
    }

    *newLength = count;
    return result;
}

int main() {
    int array[] = {10, 15, 22, 31, 7, 13, 28, 39, 41, 44};
    int len = sizeof(array) / sizeof(array[0]);
    int newLen;
    int* result;

    // а) Чётные числа
    result = filter(array, len, isEven, &newLen);
    printf("Чётные числа: ");
    for (int i = 0; i < newLen; ++i)
        printf("%d ", result[i]);
    printf("\n");
    free(result);

    // б) Числа с нечётной суммой цифр
    result = filter(array, len, hasOddDigitSum, &newLen);
    printf("Числа с нечётной суммой цифр: ");
    for (int i = 0; i < newLen; ++i)
        printf("%d ", result[i]);
    printf("\n");
    free(result);

    // в) Простые числа
    result = filter(array, len, isPrime, &newLen);
    printf("Простые числа: ");
    for (int i = 0; i < newLen; ++i)
        printf("%d ", result[i]);
    printf("\n");
    free(result);

    return 0;
}

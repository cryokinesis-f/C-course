/*
Вводятся два массива целых чисел, упорядоченные по возрастанию. Создайте новый
массив нужной длины и заполните его набором чисел из обоих исходных массивов,
также упорядоченным по возрастанию.
*/

#include <stdio.h>
#include <stdlib.h> 

int* merge_sorted_arrays(const int* arr1, int len1, const int* arr2, int len2) {

    // Выделяем память для объединённого массива
    int* merged = malloc((len1 + len2) * sizeof(int));
    
    int i = 0; // индекс для arr1
    int j = 0; // индекс для arr2
    int k = 0; // индекс для merged
    
    // Основной цикл слияния - пока есть элементы в обоих массивах
    while (i < len1 && j < len2) {
        
        // Выбираем меньший элемент из двух массивов
        if (arr1[i] <= arr2[j]) {
            merged[k++] = arr1[i++]; // Берём элемент из первого массива
        } else {
            merged[k++] = arr2[j++]; // Берём элемент из второго массива
        }
    }
    
    // Дописываем оставшиеся элементы из первого массива (если есть)
    while (i < len1) {
        merged[k++] = arr1[i++];
    }
    
    // Дописываем оставшиеся элементы из второго массива (если есть)
    while (j < len2) {
        merged[k++] = arr2[j++];
    }
    
    return merged;
}

int main() {
    int len1, len2;
    
    printf("Enter lengths of two arrays: ");
    scanf("%d %d", &len1, &len2);
    
    // Выделение памяти под массивы
    int* arr1 = malloc(len1 * sizeof(int));
    int* arr2 = malloc(len2 * sizeof(int));
    
    // Ввод первого отсортированного массива
    printf("Enter first sorted array: ");
    for (int i = 0; i < len1; ++i) {
        scanf("%d", &arr1[i]);
    }
    
    // Ввод второго отсортированного массива
    printf("Enter second sorted array: ");
    for (int i = 0; i < len2; ++i) {
        scanf("%d", &arr2[i]);
    }
    
    // Слияние массивов
    int* merged = merge_sorted_arrays(arr1, len1, arr2, len2);
    
    // Вывод результата
    printf("Merged array: ");
    for (int i = 0; i < len1 + len2; ++i) {
        printf("%d ", merged[i]);
    }
    printf("\n");
    
    free(arr1);
    free(arr2);
    free(merged);
    
    return 0;
}
/*
Вводится массив натуральных чисел. Отсортируйте его по возрастанию следующим
алгоритмом: на i-й итерации, 1 ⩽ i ⩽ n, просматриваются ячейки с индексами от 0 до
n−i, среди них находится максимальный элемент и обменивается местами с (n−i)-м
элементом. Выведите отсортированный массив.
*/

#include <stdio.h>
#include <stdlib.h> 


void selection_sort(int* arr, int len) {
    // Внешний цикл проходим по всем элементам, кроме последнего
    for (int i = 0; i < len - 1; ++i) {
        // Предполагаем, что первый элемент - максимальный
        int max_idx = 0;
        
        // Внутренний цикл ищем максимальный элемент в неотсортированной части
        // Неотсортированная часть: от 0 до len-i-1
        for (int j = 1; j < len - i; ++j) {
            // Если текущий элемент больше предполагаемого максимума
            if (arr[j] > arr[max_idx]) {
                max_idx = j; // Обновляем индекс максимального элемента
            }
        }
        
        // Обмен местами найденного максимального элемента 
        // с последним элементом неотсортированной части
        int temp = arr[max_idx];
        arr[max_idx] = arr[len - i - 1]; // len-i-1 - конец неотсортированной части
        arr[len - i - 1] = temp;
    }
}

int main() {
    int len; 
    
    printf("Enter array length: ");
    scanf("%d", &len);
    
    int* arr = malloc(len * sizeof(int));
    
    printf("Enter array elements: ");
    for (int i = 0; i < len; ++i) {
        scanf("%d", &arr[i]);
    }
    
    selection_sort(arr, len);

    printf("Sorted array: ");
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    
    return 0;
}
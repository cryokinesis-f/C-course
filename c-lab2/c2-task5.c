/*
Вводится массив натуральных чисел. Выведите все пары взаимно-простых чисел из
этого массива.
*/


#include <stdio.h>
#include <stdlib.h> 


int gcd(int a, int b) {

    // Алгоритм Евклида:
    while (b != 0) { 
        int temp = b; 
        b = a % b;    
        a = temp;     
    }
    return a; 
}


void print_coprime_pairs(const int* arr, int len) {
    // Перебираем все возможные пары элементов массива
    for (int i = 0; i < len-1; ++i) {         // Первый элемент пары
        for (int j = i + 1; j < len; ++j) { // Второй элемент пары (все элементы после i)
            // Проверяем, являются ли числа взаимно простыми
            if (gcd(arr[i], arr[j]) == 1) {
                // Выводим пару чисел, если их НОД = 1
                printf("(%d, %d)\n", arr[i], arr[j]);
            }
        }
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
    
    print_coprime_pairs(arr, len);
    
    free(arr);
    
    return 0;
}
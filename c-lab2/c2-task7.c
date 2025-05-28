/*
Вводится натуральное число n (n ⩽ 25). Найдите такой непустой набор неповторя-
ющихся натуральных чисел из диапазона от 1 до n, что синус суммы их квадратов
максимален среди всех таких наборов.
*/

#include <stdio.h>
#include <math.h> 

double max_sin = -2.0;    
int best_subset[25] = {0}; 
int best_size = 0;         


void find_max_sin_subset(int n, int current, int* subset, int size) {

    // Когда прошли все числа от 1 до n
    if (current > n) {

        // Пропускаем пустые подмножества 
        if (size == 0) return;
        
        // Вычисляем сумму квадратов элементов подмножества
        double sum_sq = 0.0;
        for (int i = 0; i < size; ++i) {
            sum_sq += subset[i] * subset[i];
        }
        
        // Вычисляем синус суммы квадратов
        double current_sin = sin(sum_sq);
        
        // Если нашли лучшее решение, обновляем глобальные переменные
        if (current_sin > max_sin) {
            max_sin = current_sin;
            best_size = size;
            for (int i = 0; i < size; ++i) {
                best_subset[i] = subset[i];
            }
        }
        return;
    }
    
    // Случай 1: включаем текущее число в подмножество
    subset[size] = current;
    find_max_sin_subset(n, current + 1, subset, size + 1);
    
    // Случай 2: не включаем текущее число 
    find_max_sin_subset(n, current + 1, subset, size);
}

int main() {
    int n;
    printf("Enter n (<= 25): ");
    scanf("%d", &n);
    
    int subset[25] = {0}; // Временный массив для хранения текущего подмножества
    
    find_max_sin_subset(n, 1, subset, 0);
    
    printf("Best subset: ");
    for (int i = 0; i < best_size; ++i) {
        printf("%d ", best_subset[i]);
    }
    printf("\nMax sin(sum of squares) = %lf\n", max_sin);
    
    return 0;
}

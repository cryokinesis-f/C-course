/* 
Напишите программу, которая вводит целое число n и выводит числа Фибоначчи с
номерами от 0 до n. Считаем, что F0 = F1 = 1.
*/

//clang -std=c99 -Wall -Wextra -pedantic c2-task1.c -o c2-task1   

#include <stdio.h>

// Функция для вывода чисел Фибоначчи от F0 до Fn
void print_fibonacci(int n) {

    // Если n отрицательное, ничего не выводим

    if (n < 0) return;
    
    // Выводим F0 (по условию = 1) если n = 0

    printf("F0 = 1\n");
    
    if (n == 0) return;
    
    // Выводим F1 (по условию = 1) если n = 1

    printf("F1 = 1\n");
    
    if (n == 1) return;
    
    // Инициализируем переменные для хранения двух предыдущих чисел Фибоначчи

    long long fib_prev = 1;  // F(i-2)
    long long fib_curr = 1;  // F(i-1)
    
    // Вычисляем и выводим числа от F2 до Fn
    for (int i = 2; i <= n; ++i) {
        // Вычисляем следующее число Фибоначчи и выводим текущее

        long long fib_next = fib_prev + fib_curr;
      
        printf("F%d = %lld\n", i, fib_next);
        
        // Обновляем значения для следующей итерации
        fib_prev = fib_curr;  
        fib_curr = fib_next;  
    }
}

int main() {
    int n;
    
    printf("Enter n: ");
    scanf("%d", &n);
    
    print_fibonacci(n);
    
    return 0;
}
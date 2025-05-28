/*
Вводятся два целых числа n и m (n ̸= m; неизвестно, больше ли n, чем m, или нет!),
а также два вещественных числа a и b. Известно, что a — это n-й член некоторой ариф-
метической прогрессии, бесконечной в обе стороны, а b— m-й член той же прогрессии.
Выведите все члены этой прогрессии, заключённые между a и b (включая эти числа)
в порядке возрастания индексов.
*/

#include <stdio.h>

// Вывод членов арифметической прогрессии между a и b
void print_arithmetic_progression(int n, int m, double a, double b) {

    // Вычисляем разность прогрессии (b - a) / (m - n)
    double d = (b - a) / (m - n);
    
    // Определяем начальный и конечный индексы (от меньшего к большему)
    int start = (n < m) ? n : m;  
    int end = (n < m) ? m : n;    
    
    // Выводим все члены прогрессии от start до end

    for (int i = start; i <= end; ++i) {
        // Вычисляем текущий член прогрессии: a + (i - n) * d
        
        double term = a + (i - n) * d;
        printf("A%d = %lf\n", i, term);  
    }
}

int main() {
    int n, m;     // Индексы известных членов прогрессии
    double a, b;  // Значения известных членов прогрессии
    
    printf("Enter n and m (n != m): ");
    scanf("%d %d", &n, &m);
    printf("Enter a (A%d) and b (A%d): ", n, m);
    scanf("%lf %lf", &a, &b);
    
    // Проверка на равенство индексов (по условию n != m)
    if (n == m) {
        printf("Error: n must not be equal to m\n");
        return 1;
    }

    print_arithmetic_progression(n, m, a, b);
    
    return 0;
}
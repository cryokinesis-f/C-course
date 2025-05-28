/*
Напишите программу, которая вводит вещественное число a и целое число n и, не
используя функций вычисления степени из библиотеки math.h, находит величину an
.
Показатель степени может быть отрицательным!
*/

#include <stdio.h>

int main()
{
    double a;
    int n;
    
    printf("Enter a: ");
    scanf("%lf", &a);

    printf("Enter n: ");
    scanf("%d", &n);
    
    double result = 1.0;
    int abs_n = (n < 0) ? -n : n;
    
    for (int i = 0; i < abs_n; i++) {
        result *= a;
    }
    
    if (n < 0) {
        result = 1.0 / result;
    }
    
    printf("%lf^%d = %lf\n", a, n, result);
    
    return 0;
}
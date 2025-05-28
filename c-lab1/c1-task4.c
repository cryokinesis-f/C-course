/*
Напишите программу, которая вводит вещественное число, находит его абсолютную
величину (не используя функций вычисления модуля числа из библиотеки math.h) и
выводит её.
*/

#include <stdio.h>

int main()
{
    double num;
    
    printf("Enter a number: ");
    scanf("%lf", &num);
    
    double abs_num = (num < 0) ? -num : num;
    printf("Absolute value: %lf\n", abs_num);
    
    return 0;
}
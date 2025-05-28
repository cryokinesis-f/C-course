/*
Напишите программу, вводящую два вещественных числа — начальный член арифме-
тической прогрессии a0 и её разность d— и целое число n— номер члена прогрессии —
и вычисляющую соответствующий член прогрессии. Тут цикл не нужен!
*/


#include <stdio.h>

int main()
{
    double a0, d;
    int n;
    
    printf("Enter a0: ");
    scanf("%lf", &a0);

    printf("Enter d: ");
    scanf("%lf", &d);

    printf("Enter n: ");
    scanf("%d", &n);
    
    double an = a0 + n * d;
    printf("The %d-th term is: %lf\n", n, an);
    
    return 0;
}
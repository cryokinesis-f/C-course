/*
Опишите структуру, описывающее комплексное число с вещественной и мнимой компонентами типа double.
Напишите функции cRead чтения комплексного числа с клавиатуры, 
cPrint вывода комплексного числа на экран, 
cAdd сложения двух комплексных чисел, 
cSub вычитания двух комплексных чисел, 
cMul умножения двух комплексных чисел, 
cDiv деления двух комплексных чисел, 
cReal вычисления вещественной части комплексного числа, 
cImag вычисления мнимой части комплексного числа, 
cConj нахождения комплексно сопряженного числа,
cAbs нахождения модуля комплексного числа, 
cArg нахождения аргумента комплексного числа (в диапазоне (−π,π]).
*/

#include <stdio.h>
#include <math.h>

#define PI acos(-1.0)

typedef struct {
    double re; // Действительная часть
    double im; // Мнимая часть
} Complex;

// Чтение комплексного числа с клавиатуры
Complex cRead() {
    Complex z;
    printf("Введите действительную и мнимую часть (через пробел): ");
    scanf("%lf %lf", &z.re, &z.im);
    return z;
}

// Вывод комплексного числа
void cPrint(Complex z) {
    if (z.im >= 0)
        printf("%.2f + %.2fi\n", z.re, z.im);
    else
        printf("%.2f - %.2fi\n", z.re, -z.im);
}

// Сложение
Complex cAdd(Complex a, Complex b) {
    return (Complex){ a.re + b.re, a.im + b.im };
}

// Вычитание
Complex cSub(Complex a, Complex b) {
    return (Complex){ a.re - b.re, a.im - b.im };
}

// Умножение
Complex cMul(Complex a, Complex b) {
    return (Complex){
        a.re * b.re - a.im * b.im,
        a.re * b.im + a.im * b.re
    };
}

// Деление
Complex cDiv(Complex a, Complex b) {
    double denom = b.re * b.re + b.im * b.im;
    return (Complex){
        (a.re * b.re + a.im * b.im) / denom,
        (a.im * b.re - a.re * b.im) / denom
    };
}

// Вещественная часть
double cReal(Complex z) {
    return z.re;
}

// Мнимая часть
double cImag(Complex z) {
    return z.im;
}

// Комплексно-сопряжённое
Complex cConj(Complex z) {
    return (Complex){ z.re, -z.im };
}

// Модуль комплексного числа
double cAbs(Complex z) {
    return sqrt(z.re * z.re + z.im * z.im);
}

// Аргумент (в радианах, от –π до π)
double cArg(Complex z) {
    return atan2(z.im, z.re); // atan2 сам обеспечивает правильный диапазон
}

int main() {
    Complex z1 = cRead();
    Complex z2 = cRead();

    printf("z1 = "); cPrint(z1);
    printf("z2 = "); cPrint(z2);

    printf("Сумма: "); cPrint(cAdd(z1, z2));
    printf("Разность: "); cPrint(cSub(z1, z2));
    printf("Произведение: "); cPrint(cMul(z1, z2));
    printf("Частное: "); cPrint(cDiv(z1, z2));

    printf("Сопряженное z1: "); cPrint(cConj(z1));
    printf("Модуль z1: %.4f\n", cAbs(z1));
    printf("Аргумент z1 (радианы): %.4f\n", cArg(z1));
    printf("Действительная часть z1: %.4f\n", cReal(z1));
    printf("Мнимая часть z1: %.4f\n", cImag(z1));

    return 0;
}

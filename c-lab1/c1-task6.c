/*
Напишите игру «Угадай число». В тексте программы задаётся положительное целое
число, не превосходящее 100000. Пользователь вводит свою догадку, компьютер выдаёт
информацию о том, больше пользовательская догадка загаданного числа, меньше или
совпадает. Процесс происходит до угадывания загаданного числа.
*/

#include <stdio.h>
#define NUMBER 66  

int main()
{
    int guess;
    printf("Guess the number (1-100000): ");
    do {
        scanf("%d", &guess);
        if (guess < NUMBER) {
            printf("Too low");
        } else if (guess > NUMBER) {
            printf("Too high");
        }
    } while (guess != NUMBER);
    printf("You guessed it!\n");
    return 0;
}
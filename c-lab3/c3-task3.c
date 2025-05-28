/*
Напишите функцию changeStringSize, которая принимает указатель на z-строку и
положительное целое число и формирует новую строку с указанной длиной; если новая
длина меньше старой, строка усекается; если новая длина больше старой, новая строка
есть старая, дополненная нужным количеством символов «*» (звёздочка). Функция
возвращает указатель на буфер новой строки.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* changeStringSize(const char* str, int newLen) {
    if (str == NULL || newLen < 0) return NULL;

    int oldLen = strlen(str);
    char* newStr = malloc((newLen + 1) * sizeof(char));
    if (newStr == NULL) return NULL;

    if (newLen <= oldLen) {
        // Копируем только первые newLen символов
        strncpy(newStr, str, newLen);
    } else {
        // Копируем всю старую строку
        strcpy(newStr, str);
        // Дополняем '*' до нужной длины
        for (int i = oldLen; i < newLen; ++i) {
            newStr[i] = '*';
        }
    }

    newStr[newLen] = '\0'; // z-строка обязательно с '\0'
    return newStr;
}


int main() {
    const char* str = "example";

    char* shorter = changeStringSize(str, 4);
    char* same = changeStringSize(str, strlen(str));
    char* longer = changeStringSize(str, 10);

    printf("Исходная строка: \"%s\"\n", str);
    printf("Усечённая:       \"%s\"\n", shorter);
    printf("Без изменений:   \"%s\"\n", same);
    printf("Дополненная:     \"%s\"\n", longer);

    free(shorter);
    free(same);
    free(longer);

    return 0;
}

/*
Напишите функции code и decode, которые «кодируют» и «декодируют» строку. Про-
цесс кодирования состоит в том, что между каждыми двумя соседними символами ис-
ходной строки вставляются два случайных печатных символа (с кодами из диапазона
от 32 до 127); декодирование, соответственно, состоит в удалении из строки закоди-
рованного сообщения «лишних» символов. Функции получают указатель на z-строку
и возвращают указатель на выделенный буфер, содержащий полученную строку. Для
генерации случайных символов следует использовать функцию rand(), определенную
в библиотеке stdlib.h и возвращающую целое 4-байтное случайное число.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Генерация случайного непечатного символа
char generateNoiseChar() {
    char c;
    while (1) {
        c = rand() % 256;
        if (isprint(c) == NULL) return c;
    }
}

// Кодирование: вставка 2 непечатных символов между каждым
char* code(const char* str) {
    if (str == NULL) return NULL;
    int len = strlen(str);
    int newLen = len + (len - 1) * 2;

    char* result = malloc((newLen + 1) * sizeof(char));
    if (result == NULL) return NULL;

    int j = 0;
    for (int i = 0; i < len; ++i) {
        result[j++] = str[i];
        if (i < len - 1) {
            result[j++] = generateNoiseChar();
            result[j++] = generateNoiseChar();
        }
    }
    result[j] = '\0';
    return result;
}

// Декодирование: удаление лишних символов
char* decode(const char* str) {
    if (str == NULL) return NULL;
    int len = strlen(str);
    int estimatedOriginalLen = (len + 2) / 3;

    char* result = malloc((estimatedOriginalLen + 1) * sizeof(char));
    if (result == NULL) return NULL;

    int j = 0;
    for (int i = 0; i < len; i += 3) {
        result[j++] = str[i];
    }
    result[j] = '\0';
    return result;
}


int main() {
    srand(time(NULL));

    const char* input = "hello!";
    printf("Исходная строка: \"%s\"\n", input);

    char* coded = code(input);
    printf("Закодированная строка:\n");
    for (int i = 0; coded[i] != '\0'; ++i) {
        if (isprint(coded[i]))
            putchar(coded[i]);
        else
            printf("\\x%02X", (unsigned char)coded[i]);
    }
    printf("\n");

    char* decoded = decode(coded);
    printf("Декодированная строка: \"%s\"\n", decoded);

    free(coded);
    free(decoded);

    return 0;
}

/*
Определите структуру Time, содержащую информацию о часе, минуте и секунде мо-
мента времени (час — в диапазоне от 0 до 23, минуты и секунды — в диапазоне от 0
до 59). 
Напишите следующие функции:
void PrintTime (Time time), печатающую переданный ей момент времени в формате
hh: mm: ss;

Time IncTime (Time time, int seconds), увеличивающую заданный момент времени
на указанное количество секунд и возвращающую полученный момент как результат;

int CmpTime (Time time1, Time time2),сравнивающуюдвапереданныхмоментавре-
мени; результат должен быть равен -1, если time1 < time2, быть равен +1, если
time1 >time2, и быть равен 0, если time1= time2;

void SwapTime (Time *time1, Time *time2),меняющую значения двух моментов ре-
мени.
*/
#include <stdio.h>

typedef struct {
    int hour;   // 0–23
    int minute; // 0–59
    int second; // 0–59
} Time;

// 1. Печать времени в формате hh:mm:ss
void PrintTime(Time time) {
    printf("%02d:%02d:%02d\n", time.hour, time.minute, time.second);
}

// 2. Увеличение времени на заданное количество секунд
Time IncTime(Time time, int seconds) {
    time.second += seconds;
    time.minute += time.second / 60;
    time.second %= 60;
    time.hour += time.minute / 60;
    time.minute %= 60;
    time.hour %= 24;
    return time;
}

// 3. Сравнение двух моментов времени
int CmpTime(Time time1, Time time2) {
    if (time1.hour != time2.hour)
        return time1.hour < time2.hour ? -1 : 1;
    if (time1.minute != time2.minute)
        return time1.minute < time2.minute ? -1 : 1;
    if (time1.second != time2.second)
        return time1.second < time2.second ? -1 : 1;
    return 0;
}

// 4. Обмен значений двух переменных типа Time
void SwapTime(Time *time1, Time *time2) {
    Time tmp = *time1;
    *time1 = *time2;
    *time2 = tmp;
}

// Тест main
int main() {
    Time t1 = {14, 45, 30};
    Time t2 = {10, 20, 50};

    printf("Time 1: ");
    PrintTime(t1);

    printf("Time 2: ");
    PrintTime(t2);

    // Увеличим t1 на 5000 секунд
    t1 = IncTime(t1, 5000);
    printf("Time 1 + 5000 sec: ");
    PrintTime(t1);

    // Сравнение
    int cmp = CmpTime(t1, t2);
    if (cmp < 0) printf("t1 < t2\n");
    else if (cmp > 0) printf("t1 > t2\n");
    else printf("t1 == t2\n");

    // Обмен
    SwapTime(&t1, &t2);
    printf("After swap:\n");
    printf("Time 1: "); PrintTime(t1);
    printf("Time 2: "); PrintTime(t2);

    return 0;
}

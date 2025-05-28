/*
Задан набор точек на евклидовой плоскости. 
Найти три разные точки, которые составляют треугольник наибольшего периметра. 
Для описания точки на плоскости через её декартовы координаты определите структуру Point и все необходимые функции,
работающие со структурами такого типа.
*/


#include <stdio.h>
#include <math.h>

#define MAX_POINTS 1000

typedef struct {
    double x;
    double y;
} Point;

// Вычисление расстояния между двумя точками
double Distance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Периметр треугольника по трём точкам
double Perimeter(Point a, Point b, Point c) {
    return Distance(a, b) + Distance(b, c) + Distance(c, a);
}

// Нахождение трёх точек с наибольшим периметром
void FindMaxPerimeterTriangle(Point *points, int n, int *i1, int *i2, int *i3) {
    double maxPerim = -1.0;
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                double p = Perimeter(points[i], points[j], points[k]);
                if (p > maxPerim) {
                    maxPerim = p;
                    *i1 = i;
                    *i2 = j;
                    *i3 = k;
                }
            }
        }
    }
}

// Тест main
int main() {
    Point points[MAX_POINTS];
    int n;

    printf("Введите количество точек (до %d): ", MAX_POINTS);
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        printf("Введите координаты точки %d (x y): ", i + 1);
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    int i1, i2, i3;
    FindMaxPerimeterTriangle(points, n, &i1, &i2, &i3);

    printf("Точки с максимальным периметром:\n");
    printf("A: (%.2lf, %.2lf)\n", points[i1].x, points[i1].y);
    printf("B: (%.2lf, %.2lf)\n", points[i2].x, points[i2].y);
    printf("C: (%.2lf, %.2lf)\n", points[i3].x, points[i3].y);
    printf("Периметр: %.4lf\n", Perimeter(points[i1], points[i2], points[i3]));

    return 0;
}

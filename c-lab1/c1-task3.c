/*
Напишите программу, вводящую два вещественных числа — радиус окружности и угол
(в градусах) 
и вычисляющую длину дуги 
и площадь сегмента (фигуры, ограниченной дугой окружности и стягивающей ее хордой), с
оответствующих введённому углу,в окружности с введённым радиусом. 
Тригонометрические функции принимают углы,
выраженные в радианах!
*/

#include <stdio.h>
#include <math.h>

int main()
{
    double radius, angle_deg;
    
    printf("Enter radius: ");
    scanf("%lf", &radius);

    printf("Enter angle in degrees: ");
    scanf("%lf", &angle_deg);
    
    double angle_rad = angle_deg * M_PI / 180.0;

    double arc_length = radius * angle_rad;
    
    double segment_area = 0.5 * radius * radius * (angle_rad - sin(angle_rad));
    
    printf("Arc length: %lf\n", arc_length);
    printf("Segment area: %lf\n", segment_area);
    
    return 0;
}
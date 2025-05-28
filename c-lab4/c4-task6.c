#include <stdio.h>
#include <complex.h>
#include <math.h>

typedef double complex (*func_t)(double complex);

double complex newton_method(func_t f, func_t df, double complex z0, double eps, int max_iter) {
    double complex z = z0;
    for (int i = 0; i < max_iter; i++) {
        double complex fz = f(z);
        double complex dfz = df(z);
        
        if (cabs(dfz) == 0.0) {
            // Производная равна нулю — деление невозможно
            fprintf(stderr, "Derivative is zero at iteration %d\n", i);
            break;
        }

        double complex z_next = z - fz / dfz;

        if (cabs(f(z_next)) < eps) {
            return z_next;
        }

        z = z_next;
    }
    // Если не сошлось за max_iter итераций, возвращаем последнее приближение
    return z;
}

// Пример функции f(z) = z^2 - 1 и её производной f'(z) = 2z
double complex f(double complex z) {
    return z*z + 1.0 + 0.0*I;
}

double complex df(double complex z) {
    return 2.0*z;
}

int main() {
    double complex z0 = 1.0 + 1.0*I; // начальное приближение
    double eps = 1e-8;
    int max_iter = 1000;

    double complex root = newton_method(f, df, z0, eps, max_iter);
    printf("Approximate root: %.10f + %.10fi\n", creal(root), cimag(root));

    return 0;
}

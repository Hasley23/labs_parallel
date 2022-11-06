#include <stdio.h>

double f(double x)
{
    return (4.0 / (1.0 + x * x));
}

int main()
{
    double x, pi;
    double sum = 0.0;

    int n;
    scanf("%d", &n);

    double dx = 1.0 / n;

    #pragma omp parallel for private(x) shared(dx) reduction(+: sum)
    for (int i = 0; i < n; ++i)
    {
        x = dx * (i + 0.5);
        sum += f(x);
    }
    pi = dx * sum;
    printf("pi = %.8lf\n", pi);
}
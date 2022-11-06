#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    double start_time, end_time, tick;
    start_time = omp_get_wtime();
    end_time = omp_get_wtime();
    tick = omp_get_wtick();
    printf("Время на замер времени %.9lf с\n", end_time-start_time);
    printf("Точность таймера %.9lf с\n", tick);
}

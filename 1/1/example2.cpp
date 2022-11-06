#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
    double start_time, end_time, tick;
    start_time = omp_get_wtime();
    end_time = omp_get_wtime();
    tick = omp_get_wtick();
    printf("Время на замер времени: %.3lf нс\n", (end_time-start_time) * 1'000'000'000);
    printf("Точность таймера: %.3lf нс\n", tick * 1'000'000'000);
}
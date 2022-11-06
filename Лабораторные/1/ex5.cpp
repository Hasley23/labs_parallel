#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
    double start_time, end_time, tick, time;
    start_time = omp_get_wtime();
    time = omp_get_wtime();
    end_time = omp_get_wtime();
    time = end_time-start_time;
    start_time = omp_get_wtime();
    tick = omp_get_wtick();
    end_time = omp_get_wtime();
    printf("Время, необходимое для работы функции omp_get_wtick(): %.3lf мкс\n", (end_time-start_time-time) * 1'000'000);
}
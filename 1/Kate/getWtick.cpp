#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
    // определяем переменные
    double start_time, end_time, tick, time;
    
    // начальное время
    start_time = omp_get_wtime();
    
    // выполняем функцию
    tick = omp_get_wtick();
    
    // конечное время
    end_time = omp_get_wtime();
    
    // время работы omp_get_wtime()
    time = end_time-start_time;
 
    printf("Время omp_get_wtick(): %.9lf с\n", time);
    printf("Точность: %.9lf с\n", tick);
}

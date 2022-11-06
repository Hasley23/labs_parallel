#include <stdio.h>
#include <omp.h>

int main() {

    printf("Количество доступных процессоров: %d\n", omp_get_num_procs());

    #pragma omp parallel num_threads(4)
    {
        int mult = 1;
        #pragma omp master
        for(int i = 0; i < 900000000; ++i)
            mult *= i;

        printf("Количество доступных процессоров: %d\n", omp_get_num_procs());
    }

    return 0;
}
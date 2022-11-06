#include <stdio.h>
#include <omp.h>

int main() {

    printf("Количество доступных процессоров (потоков): %d\n", omp_get_num_procs());

    return 0;
}

// #include <stdio.h>
// #include <omp.h>

// int main() {

//     printf("Максимально допустимое число нитей: %d\n", omp_get_max_threads());

//     return 0;
// }

#include <stdio.h>
#include <omp.h>

int main() {


    printf("Количество потоков: %d\n", omp_get_max_threads());

    #pragma omp parallel num_threads(17321)
    {
        // int mult = 1;
        // for(int i = 0; i < 900000000; ++i)
        //     mult *= i;

        #pragma omp master
        printf("Количество потоков: %d\n", omp_get_num_threads());
    }

    return 0;
}
#include <stdio.h>
#include <omp.h>

int main() {

    omp_set_num_threads(2);

    printf("Да будет вложенный параллелизм!\n");
    omp_set_nested(1);
    #pragma omp parallel
    {
        printf("1 уровень вложенности\n");
        #pragma omp parallel
        {
            printf("2 уровень вложенности\n");
            #pragma omp parallel
                printf("3 уровень вложенности\n");
        }

    }

    printf("Отставить вложенный параллелизм!\n");
    omp_set_nested(0);
    #pragma omp parallel
    {
        printf("1 уровень вложенности\n");
        #pragma omp parallel
        {
            printf("2 уровень вложенности\n");
            #pragma omp parallel
                printf("3 уровень вложенности\n");
        }

    }

    return 0;
}
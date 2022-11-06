#include <stdio.h>
#include <omp.h>

int main() {
	
    // по умолчанию 2 потока
    omp_set_num_threads(2);
	
    // на каждом уровне по 2 потока
    printf("Вложенный параллелизм вкючен:\n");
    omp_set_nested(1);
    #pragma omp parallel
    {
        printf("1 уровень\n");
        #pragma omp parallel
        {
            printf("2 уровень\n");
            #pragma omp parallel
                printf("3 уровень\n");
        }

    }
	
    // всего 2 потока
    printf("Вложенный параллелизм выключен:\n");
    omp_set_nested(0);
    #pragma omp parallel
    {
        printf("1 уровень\n");
        #pragma omp parallel
        {
            printf("2 уровень\n");
            #pragma omp parallel
                printf("3 уровень\n");
        }

    }

    return 0;
}

#include <stdio.h>
#include <omp.h>
int n;
#pragma omp threadprivate(n)

int main()
{
    n=1;
    printf("Значение n в начале: %d\n", n);
    #pragma omp parallel copyin(n)
    {
        int num=omp_get_thread_num();
        printf("Значение n на нити %d (на входе): %d\n", num, n);
        /* Присвоим переменной n номер текущей нити */
        n=omp_get_thread_num();
        printf("Значение n на нити %d (на выходе): %d\n", num, n);
    }
    // значение нити master
    printf("Значение n в конце: %d\n", n);
}



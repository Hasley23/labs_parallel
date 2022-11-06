#include <stdio.h>
#include <omp.h>

int main() {
    int n=1;
    printf("Значение n в начале: %d\n", n);
    #pragma omp parallel firstprivate(n)
    {
        int num=omp_get_thread_num();
        printf("Значение n на нити %d (на входе): %d\n", num, n);
        /* Присвоим переменной n номер текущей нити */
        n=omp_get_thread_num() + 3;
        printf("Значение n на нити %d (на выходе): %d\n", num, n);
    }
    printf("Значение n в конце: %d\n", n);
}
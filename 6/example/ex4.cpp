#include <stdio.h>
#include <omp.h>

int main()
{
    int count = 0;
    #pragma omp parallel
    {
        #pragma omp atomic
            count++;
    }
    printf("Число нитей: %d\n", count);
}
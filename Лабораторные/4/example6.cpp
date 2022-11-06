#include <stdio.h>
#include <omp.h>

int main()
{
    int n=0;
    #pragma omp parallel private(n)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                n=1;
            }
            #pragma omp section
            {
                n=2;
            }
            #pragma omp section
            {
                n=3;
            }
        }
        printf("Значение n на нити %d: %d\n", omp_get_thread_num(), n);
    }
    printf("Значение n в последовательной области: %d\n", n);
}
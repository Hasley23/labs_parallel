#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        printf("Сообщение 1\n");
        printf("Сообщение 2\n");
        #pragma omp barrier
            printf("Сообщение 3\n");
    }
}
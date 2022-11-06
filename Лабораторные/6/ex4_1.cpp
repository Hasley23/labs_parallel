#include <stdio.h>
#include <omp.h>

int main()
{
    omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel
    {
        printf("Сообщение 1\n");
        printf("Сообщение 2\n");
        #pragma omp single
            omp_set_lock(&lock);
        omp_unset_lock(&lock);
        // #pragma omp barrier
            printf("Сообщение 3\n");
    }
    omp_destroy_lock(&lock);
}
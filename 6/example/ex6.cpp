#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{
    omp_lock_t lock;
    int n;
    omp_init_lock(&lock);
    #pragma omp parallel private(n)
    {
        n = omp_get_thread_num();
        while (!omp_test_lock(&lock))
        {
            printf("Секция закрыта, нить %d\n", n);
            usleep(2);
        }
        printf("Начало закрытой секции, нить %d\n", n);
        usleep(5);
        printf("Конец закрытой секции, нить %d\n", n);
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
}
#include <stdio.h>
#include <omp.h>

int main()
{
    omp_lock_t lock;
    omp_init_lock(&lock);
	int n;
    #pragma omp parallel
    {
        // #pragma omp critical
		// {
		// 	n = omp_get_thread_num();
        //     printf("Нить %d\n", n);
		// }
        omp_set_lock(&lock);
            n = omp_get_thread_num();
            printf("Нить %d\n", n);
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
}
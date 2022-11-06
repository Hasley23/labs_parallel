#include <stdio.h>
#include <omp.h>

int main()
{
	int k, N;
    int sum = 0;
	double start_time, end_time;

    scanf("%d%d", &k, &N);

	// reduction
	start_time = omp_get_wtime();
	#pragma omp parallel num_threads(k) reduction(+: sum)
	{
		#pragma omp for
		for (int i = 1; i <= N; ++i)
			sum += i;
	}
	end_time = omp_get_wtime();
    printf("Sum = %d\n", sum);
	printf("Время работы reduction = %f\n\n", end_time - start_time);

	sum = 0;

	// atomic
	start_time = omp_get_wtime();
	#pragma omp parallel num_threads(k)
	{
		#pragma omp for
		for (int i = 1; i <= N; ++i)
		{
			#pragma omp atomic
			sum+=i;
		}
	}
	end_time = omp_get_wtime();
    printf("Sum = %d\n", sum);
	printf("Время работы atomic = %f\n\n", end_time - start_time);

	sum = 0;

	// critical
	start_time = omp_get_wtime();
	#pragma omp parallel num_threads(k)
	{
		#pragma omp for
		for (int i = 1; i <= N; ++i)
		{
			#pragma omp critical
			sum+=i;
		}
	}
	end_time = omp_get_wtime();
    printf("Sum = %d\n", sum);
	printf("Время работы critical = %f\n\n", end_time - start_time);
	
	sum = 0;

	// lock
	start_time = omp_get_wtime();
	omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel num_threads(N)
    {
        omp_set_lock(&lock);
            sum += omp_get_thread_num() + 1;
        omp_unset_lock(&lock);
    }
	end_time = omp_get_wtime();
	omp_destroy_lock(&lock);
    printf("Sum = %d\n", sum);
	printf("Время работы lock = %f\n\n", end_time - start_time);
}
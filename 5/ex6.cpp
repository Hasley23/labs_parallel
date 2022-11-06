#include <stdio.h>
#include <omp.h>

int main()
{
	int k, N;
    int sum = 0;

    scanf("%d%d", &k, &N);

	#pragma omp parallel num_threads(k) reduction(+: sum)
	{
		#pragma omp for
		for (int i = 1; i <= N; ++i)
			sum += i;
		printf("[%d]: Sum = %d\n", omp_get_thread_num(), sum);
	}
    printf("Sum = %d\n", sum);
}

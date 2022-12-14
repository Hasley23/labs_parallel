#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int i;
	#pragma omp parallel private(i)
	{
		// #pragma omp for schedule (static)
		// #pragma omp for schedule (static, 1)
		// #pragma omp for schedule(static, 2)
		// #pragma omp for schedule (dynamic)
		// #pragma omp for schedule (dynamic, 2)
		// #pragma omp for schedule (guided)
		#pragma omp for schedule (guided, 2)
		for (i = 0; i < 10; i++)
		{
			printf("Нить %d выполнила итерацию %d\n", omp_get_thread_num(), i);
			usleep(1);
		}
	}
}
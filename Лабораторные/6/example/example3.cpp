#include <stdio.h>
#include <omp.h>

int main()
{
	int n;
    #pragma omp parallel
	{
    	#pragma omp critical
		{
			n = omp_get_thread_num();
			printf("Нить %d\n", n);
		}
	}
}
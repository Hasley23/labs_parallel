#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int i;
	int choice = 0;
    double start_time, end_time, time;
    
    printf("0 - последовательная версия | !0 - параллельная\n");
   
   	// выбор между последовательной и параллельной версией
   	scanf("%d", &choice);
   	if (choice == 0)
   		omp_set_num_threads(0);
   		
   	
    // время начала работы параллельного блока
    start_time = omp_get_wtime();		
	#pragma omp parallel private(i)
	{
		#pragma omp for schedule (static)
		//#pragma omp for schedule (static, 1)
		//#pragma omp for schedule(static, 2)
		//#pragma omp for schedule (dynamic)
		//#pragma omp for schedule (dynamic, 2)
		//#pragma omp for schedule (guided)
		//#pragma omp for schedule (guided, 2)
		for (i = 0; i < 10; i++)
		{
			printf("Нить %d выполнила итерацию %d\n", omp_get_thread_num(), i);
			sleep(1);
		}
	}
	// время окончания работы параллельной секции
    end_time = omp_get_wtime();
    // время работы параллельной секции
    time = end_time-start_time;
    printf("Время работы параллельной секции: %f\n", time);
}

#include <stdio.h>
#include <omp.h>

int main() {
    // по умолчанию использовать 2 потока
    omp_set_num_threads(2);
    
    printf("Сейчас параллельная область будет использовать 3 потока:\n");
    #pragma omp parallel num_threads(3)
        printf("Параллельная область 1\n");
   
    #pragma omp master
    	printf("\nСейчас параллельная область будет использовать 2 потока:\n");
	
    #pragma omp parallel
        printf("Параллельная область 2\n");
}

#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

// замеры
double time(bool parallel, int n, int threads)
{
	if (threads <= omp_get_max_threads())
	{
		omp_set_num_threads(threads);
	}
    double start_time, end_time;
    int *A = static_cast<int *>(malloc(n * sizeof(int)));
	int *B = static_cast<int *>(malloc(n * sizeof(int)));
	int *C = static_cast<int *>(malloc(n * sizeof(int)));
		
	for (int i = 0; i < n; ++i)
	{
		A[i] = i;
		B[i] = 2 * i;
		C[i] = 0;
	}

    start_time = omp_get_wtime();
    #pragma omp parallel for shared(A, B, C) if(parallel)
		for (int i = 0; i < n; ++i)
			C[i] = A[i] * B[i];
    end_time = omp_get_wtime();

	free(A);
	free(B);
	free(C);
    return (end_time-start_time) * 1'000'000 ; // мкс
}

// вывод на экран времени
void print_time(int n, int threads)
{
    cout << left << fixed << setprecision(3)
        << setw(22) << n << setw(22) << time(0, n, threads) << setw(16) << time(1, n, threads) << setw(16) << endl;
}

// точка входа
int main()
{
	#ifdef _OPENMP
		cout << "4 потока:\n";
		cout << setw(22) << "Количество элементов  " << setw(13) << "Последовательно, мкс  " << setw(16) << "Параллельно, мкс" << endl;
		print_time(50, 4);
    	print_time(100, 4);
    	print_time(500, 4);
    	print_time(1000, 4);
    	print_time(5000, 4);
    	print_time(15000, 4);
    	print_time(30000, 4);
		print_time(50000, 4);
		print_time(100000, 4);
		print_time(1000000, 4);
		cout << "\n6 потоков:\n";
		cout << setw(22) << "Количество элементов  " << setw(13) << "Последовательно, мкс  " << setw(16) << "Параллельно, мкс" << endl;
		print_time(50, 6);
    	print_time(100, 6);
    	print_time(500, 6);
    	print_time(1000, 6);
    	print_time(5000, 6);
    	print_time(15000, 6);
    	print_time(30000, 6);
		print_time(50000, 6);
		print_time(100000, 6);
		print_time(1000000, 6);
		cout << "\n12 потоков:\n";
		cout << setw(22) << "Количество элементов  " << setw(13) << "Последовательно, мкс  " << setw(16) << "Параллельно, мкс" << endl;
		print_time(50, 12);
    	print_time(100, 12);
    	print_time(500, 12);
    	print_time(1000, 12);
    	print_time(5000, 12);
    	print_time(15000, 12);
    	print_time(30000, 12);
		print_time(50000, 12);
		print_time(100000, 12);
		print_time(1000000, 12);
	#else
		printf ("Последовательная версия, демонстрация параллелизма невозможна\n");	
	#endif
}

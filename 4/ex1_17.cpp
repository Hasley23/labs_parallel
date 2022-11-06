#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <omp.h>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1,20);

double time(bool parallel, int n)
{
    double start_time, end_time, tick;
    int *A, *B, *C;
    A = new int[n];
    B = new int[n];
    C = new int[n];

	for (int i = 0; i < n; ++i)
	{
		A[i] = dist(gen);
		B[i] = dist(gen);
	}

    start_time = omp_get_wtime();
    #pragma omp parallel for shared(A, B, C) if(parallel)
		for (int i = 0; i < n; ++i)
			C[i] = A[i] * B[i];
    end_time = omp_get_wtime();


    return (end_time-start_time) * 1'000'000;
}

void time_chunk(int n)
{
    cout << left << fixed << setprecision(3) << setw(22) << n << setw(21) << setw(16) << time(1, n) << endl;
}

int main()
{
	int count, num;
	double start_time, end_time, time;
    start_time = omp_get_wtime();
    cout << setw(22) << "Кол-во элементов " << setw(21)  << "Последовательно, мкс " << setw(16) << "Параллельно, мкс" << endl;
    time_chunk(10);
    #pragma omp parallel
    {
        count=omp_get_num_threads();
		num=omp_get_thread_num();
		if (num == 0) printf("Всего нитей: %d\n", count);
		else printf("Нить номер %d\n", num);
    }
    // время окончания работы параллельной секции
    end_time = omp_get_wtime();
    // время работы параллельной секции
    time = end_time-start_time;
    printf("Время работы параллельной секции: %f\n", time);	
}


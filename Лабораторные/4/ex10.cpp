#include <stdio.h>
#include <omp.h>
#include <random>
#include <iostream>
#include <iomanip>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1,20);

void print(int* array, int n)
{
    for(int i = 0; i < n; ++i)
        printf("%d\t", array[i]);
    printf("\n");
}

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

    // print(A, n);
    // print(B, n);

    start_time = omp_get_wtime();
    #pragma omp parallel for shared(A, B, C) if(parallel)
		for (int i = 0; i < n; ++i)
			C[i] = A[i] * B[i];
    end_time = omp_get_wtime();

    // print(C, n);
    return (end_time-start_time) * 1'000'000;
}

void print_time(int n)
{
    cout << left << fixed << setprecision(3)
        << setw(22) << n << setw(21) << time(0, n) << setw(16) << time(1, n) << endl;
}

int main()
{
    cout << setw(22) << "Количество элементов  " << setw(21) << "Последовательно, мкс  " << setw(16) << "Параллельно, мкс" << endl;
    print_time(10);
    print_time(50);
    print_time(100);
    print_time(500);
    print_time(1000);
    print_time(5000);
    print_time(10000);
    print_time(20000);
}

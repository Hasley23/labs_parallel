#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

// Хранение результатов сложения
int sequental_res = 0, parallel_res = 0;

double time(bool parallel, int k, int n)
{
    // Для замеров скорости
	double start_time, end_time;

	// объявим переменные результатов сложения
	int res = 0;
	int res_omp = 0;
	
	// последовательно сложим
	start_time = omp_get_wtime();

    for (int i = 1; i <= n; ++i)
		res += i;
	
	end_time = omp_get_wtime();

	sequental_res = res;

	// параллельно умножим
	start_time = omp_get_wtime();
	
    // используем parallel for
	#pragma omp parallel for num_threads(k) reduction(+: res_omp) if(parallel)
    //#pragma omp parallel for schedule (static, 1) num_threads(k) reduction(+: res_omp) if(parallel)
    //#pragma omp parallel for schedule (static, 2) num_threads(k) reduction(+: res_omp) if(parallel)
    //#pragma omp parallel for schedule (dynamic) num_threads(k) reduction(+: res_omp) if(parallel)
    //#pragma omp parallel for schedule (dynamic, 2) num_threads(k) reduction(+: res_omp) if(parallel)
    //#pragma omp parallel for schedule (guided) num_threads(k) reduction(+: res_omp) if(parallel)
    //#pragma omp parallel for schedule (guided, 2) num_threads(k) reduction(+: res_omp) if(parallel)
    //#pragma omp parallel for schedule (static) num_threads(k) reduction(+: res_omp) if(parallel)
    	for (int i = 1; i <= n; ++i)
			res_omp += i;
	
    end_time = omp_get_wtime();
	
	parallel_res = res_omp;

    return (end_time-start_time) * 1'000'000 ; // мкс
}

// вывод на экран времени
void print_time(int n, int k)
{	
    // func format is (bool parallel, int k, int N)
	// Time table
    cout << left << fixed << setprecision(3)
        << setw(10) << n << setw(17) << time(0, k, n) << setw(18) 
		<< time(1, k, n) << setw(18) << sequental_res << setw(15) << parallel_res << endl;
}

// точка входа
int main(int argc, char* argv[])
{
	cout << "Кащенко В. А. ПрИб-181\n\"Сложение чисел\" (параллельная версия)\n\n4 потока:\n" <<
	setw(10) << "Кол-во    " << setw(20) << "Послед-но, мкс   " << setw(20) << "Паралл-но, мкс " << setw(22) <<
	"   Р-ат послед-но " << setw(15) << "   Р-ат паралл-но " << endl;
	
    
    int threads = 4;
	print_time(50, threads);
    print_time(100, threads);
    print_time(500, threads);
    print_time(1000, threads);
    print_time(5000, threads);
    print_time(15000, threads);
    print_time(30000, threads);
	print_time(50000, threads);
	print_time(100000, threads);
	print_time(1000000, threads);

	cout << "\n6 потоков:\n" <<
	setw(10) << "Кол-во    " << setw(20) << "Послед-но, мкс   " << setw(20) << "Паралл-но, мкс " << setw(22) <<
	"   Р-ат послед-но " << setw(15) << "   Р-ат паралл-но " << endl;
	
	threads = 6;
	print_time(50, threads);
    print_time(100, threads);
    print_time(500, threads);
    print_time(1000, threads);
    print_time(5000, threads);
    print_time(15000, threads);
    print_time(30000, threads);
	print_time(50000, threads);
	print_time(100000, threads);
	print_time(1000000, threads);

	cout << "\n12 потоков:\n" <<
	setw(10) << "Кол-во    " << setw(20) << "Послед-но, мкс   " << setw(20) << "Паралл-но, мкс " << setw(22) <<
	"   Р-ат послед-но " << setw(15) << "   Р-ат паралл-но " << endl;

	threads = 12;
	print_time(50, threads);
    print_time(100, threads);
    print_time(500, threads);
    print_time(1000, threads);
    print_time(5000, threads);
    print_time(15000, threads);
    print_time(30000, threads);
	print_time(50000, threads);
	print_time(100000, threads);
	print_time(1000000, threads);
}

#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

// Хранение результатов 
double sequental_res, parallel_res;

// Часть вычисления Pi
double f(double x)
{
    return (4.0 / (1.0 + x * x));
}

double time(bool parallel, int k, int N)
{
	double x = 0, pi = 0;

    // Для замеров скорости
	double start_time, end_time;

	// объявим переменные результатов
	double res = 0;
	double res_omp = 0;
	
    double dx = 1.0 / (double)N;
	


	// последовательно сложим
	start_time = omp_get_wtime();
	for (int i = 0; i < N; ++i)
    {
    	x = dx * (i + 0.5);
    	res += f(x);
    }
	end_time = omp_get_wtime();
	sequental_res = res * dx;

	
	
	// параллельно умножим
	if (parallel)
		start_time = omp_get_wtime();

	// используем parallel for с опцией reduction
	#pragma omp parallel for private(x) shared(dx) num_threads(k) reduction(+: res_omp) if(parallel)
    for (int i = 0; i < N; ++i)
    {
        x = dx * (i + 0.5);
        res_omp += f(x);
    }

	if (parallel)
		end_time = omp_get_wtime();
	parallel_res = res_omp * dx;

    return end_time-start_time;
}

// вывод на экран времени
void print_time(int n, int k)
{	
    // func format is (bool parallel, int k, int N)
	// Time table
    cout << left << fixed << setprecision(8)
        << setw(11) << n << setw(12) << time(0, k, n) << setw(15) 
		<< time(1, k, n) << setw(18) << sequental_res << setw(15) << parallel_res << endl;
}

// точка входа
int main(int argc, char* argv[])
{
	cout << "Кащенко В. А. ПрИб-181\n\"Число Pi\" (параллельная версия)\n\n" <<
	setw(11) << "Кол-во    " << setw(20) << " Послед-но   " << setw(20) << "Паралл-но   " << setw(22) <<
	"   Р-ат послед-но " << setw(15) << "   Р-ат паралл-но " << endl;

	cout << "2 потока:" << endl;
	print_time(1000000000, 2);
	cout << "4 потока:" << endl;
	print_time(1000000000, 4);
	cout << "6 потоков:" << endl;
    print_time(1000000000, 6);
	cout << "8 потоков:" << endl;
	print_time(1000000000, 8);
	cout << "10 потоков:" << endl;
	print_time(1000000000, 10);
	cout << "12 потоков:" << endl;
	print_time(1000000000, 12);
}

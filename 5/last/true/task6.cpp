#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

// Хранение результатов сложения
int sequental_res, parallel_res;

double time(bool parallel, int k, int N)
{
    // Для замеров скорости
	double start_time, end_time;

	// объявим переменные результатов сложения
	int res = 0;
	int res_omp = 0;
	
	// последовательно сложим
	start_time = omp_get_wtime();

    for (int i = 1; i <= N; ++i)
		res += i;
	
	end_time = omp_get_wtime();

	sequental_res = res;

	// параллельно умножим
	start_time = omp_get_wtime();
	
    // используем parallel for с опцией reduction (суммирование в res_omp)
	#pragma omp parallel for num_threads(k) if(parallel)
    for (int i = 1; i <= N; ++i)
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
		<< time(0, k, n) << setw(18) << sequental_res << setw(15) << parallel_res << endl;
}

// точка входа
int main(int argc, char* argv[])
{
	cout << "Кащенко В. А. ПрИб-181\n\"Сложение чисел\" (параллельная версия)\n\n4 потока:\n" <<
	setw(10) << "Кол-во    " << setw(20) << "Послед-но, мкс   " << setw(20) << "Паралл-но, мкс " << setw(22) <<
	"   Р-ат послед-но " << setw(15) << "   Р-ат паралл-но " << endl;
	
    // func format is (int k, int n)

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

	cout << "\n6 потоков:\n" <<
	setw(10) << "Кол-во    " << setw(20) << "Послед-но, мкс   " << setw(20) << "Паралл-но, мкс " << setw(22) <<
	"   Р-ат послед-но " << setw(15) << "   Р-ат паралл-но " << endl;

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

	cout << "\n12 потоков:\n" <<
	setw(10) << "Кол-во    " << setw(20) << "Послед-но, мкс   " << setw(20) << "Паралл-но, мкс " << setw(22) <<
	"   Р-ат послед-но " << setw(15) << "   Р-ат паралл-но " << endl;

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
}

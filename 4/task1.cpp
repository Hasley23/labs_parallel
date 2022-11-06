#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//  Создание векторов для скалярного произведения
vector<int> randVec(size_t size)
{
	vector<int> v(size);
	// генератор true-random-number
	random_device r;
	// используем лямда-функцию generate()
	// & фиксирует ссылку на локальный объект, чтобы видеть актуальное значение
	generate(v.begin(), v.end(), [&] {return r();});
	return v;
}

// Хранение результатов сложения
int sequental_res, parallel_res;

// замеры
double time(bool parallel, int n, int threads)
{
	double start_time, end_time;

	// создание векторов
	vector<int> v(randVec(n));
	vector<int> v1(randVec(n));

	// объявим переменные результатов произведения
	int res = 0;
	int res_omp = 0;
	
	// последовательно умножим
	start_time = omp_get_wtime();

	for (int i = 0; i < n; i++)
	{
		res += v[i] * v1[i];
	}
	end_time = omp_get_wtime();

	sequental_res = res;

	// параллельно умножим
	start_time = omp_get_wtime();

	// используем parallel for с опцией reduction (суммирование в res_omp)
	#pragma omp parallel for reduction(+:res_omp) if(parallel)
	for (int i = 0; i < n; i++)
	{
		res_omp += v[i] * v1[i];
	}
	end_time = omp_get_wtime();
	
	parallel_res = res_omp;

    return (end_time-start_time) * 1'000'000 ; // мкс
}

// вывод на экран времени
void print_time(int n, int threads)
{	
	// Time table
    cout << left << fixed << setprecision(3)
        << setw(10) << n << setw(17) << time(0, n, threads) << setw(18) 
		<< time(1, n, threads) << setw(18) << sequental_res << setw(15) << parallel_res << endl;
}

// точка входа
int main(int argc, char* argv[])
{
	cout << "Кащенко В. А. ПрИб-181\nСкалярное произведение векторов (параллельная версия)\n\n4 потока:\n" <<
	setw(10) << "Кол-во    " << setw(20) << "Послед-но, мкс   " << setw(20) << "Паралл-но, мкс " << setw(22) <<
	"   Р-ат послед-но " << setw(15) << "   Р-ат паралл-но " << endl;
	
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

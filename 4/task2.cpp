// time table
#include <stdio.h>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//  Создание векторов для поиска
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
    
    // i - итератор
    int i;

    // создание векторов
    vector<int> v(randVec(n));

    //начальные значения векторов
    int count = v[0];
    int count1 = v[0];

    // последовательный поиск
    start_time = omp_get_wtime();
    for (i = 1; i < n; i++)
    {
        if (v[i] > count)
        count = v[i];
    }
    end_time = omp_get_wtime();
    sequental_res = count;

    // параллельный поиск
    start_time = omp_get_wtime();
    // общее - v; локальные - i, n
    #pragma omp parallel shared(v) private(i, n)
    {
        /* номер текущей нити */
        n = omp_get_thread_num();
        // параллельный поиск
        #pragma omp for
        for (i = 1; i < n; i++)
        {
            if (v[i] > count1)
            count1 = v[i];
        }
    }
    end_time = omp_get_wtime();
    parallel_res = count1;

    return (end_time-start_time) * 1'000'000 ; // мкс
}

// вывод на экран времени
void print_time(int n, int threads)
{	
	// Time table
    cout << left << fixed << setprecision(3)
        << setw(10) << n << setw(17) << time(0, n, threads) << setw(18) 
		<< time(1, n, threads) << setw(18) << sequental_res << setw(15) << sequental_res << endl;
}

// точка входа
int main(int argc, char* argv[])
{
    cout << "Кащенко В. А. ПрИб-181\nПоиск вектора (параллельная версия)\n\n4 потока:\n" <<
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
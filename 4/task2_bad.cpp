// classic
#include <stdio.h>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

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

int main(int argc, char* argv[])
{
    double start_time, end_time;
    
    // фиксируем ввод (подходящее для замера скорости значение)
    int input = 10000000;
    
    // создание векторов
    vector<int> v(randVec(input));

    //начальные значения векторов
    int count = v[0];
    int count1 = v[0];
    
    // n - поток, i - итератор
    int n,i;
    
    // последовательный поиск
    start_time = omp_get_wtime();
    for (i = 1; i < input; i++)
    {
        if (v[i] > count)
        count = v[i];
    }
    end_time = omp_get_wtime();

    // *** Out (последовательный)
    printf("\nПоследовательная версия:\n");
    printf("Время на поиск = %f\n", end_time - start_time);
    printf("Максимальное значение = %d\n", count);
    // ***

    start_time = omp_get_wtime();
    // общее - v; локальные - i, n
    #pragma omp parallel shared(v) private(i, n)
    {
        /* номер текущей нити */
        n = omp_get_thread_num();
        // параллельный поиск
        #pragma omp for
        for (i = 1; i < input; i++)
        {
            if (v[i] > count1)
            count1 = v[i];
        }
    }
    end_time = omp_get_wtime();
    
    // *** Out (параллельный)
    printf("\n\nПараллельная версия:\n");
    printf("Время на поиск = %f\n", end_time - start_time);
    printf("Максимальное значение = %d\n", count1);
    // ***
}
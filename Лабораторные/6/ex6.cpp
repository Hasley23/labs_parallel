#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <omp.h>

using namespace std;

#define eps 0.00001

double *gauss(double **A, double *B, int n, int num_threads_) // метод Гаусса, возвращает массив решений X
{
    
    double** a = new double *[n];
    double* b = new double[n];
    #pragma omp parallel if(num_threads_ > 0) num_threads(num_threads_)
    #pragma omp for
    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; j++)
            a[i][j] = A[i][j];
        b[i] = B[i];
    }
    int count_zero;
    for (int k = 0; k < n; k++)
    {
        count_zero = 0;
        for (int i = 0; i < n; i++)
            if (abs(a[i][k]) < eps)
                ++count_zero;
        if (count_zero == n)
        {
            cout << "Решение получить невозможно из-за нулевого столбца " << k << " матрицы A." << endl;
            return NULL;
        }
    }

    double temp, *x = new double[n];
    #pragma omp parallel if(num_threads_ > 0) num_threads(num_threads_)
    //  приведение матрицы для получения решения
    #pragma omp for collapse(2)
        for (int k = 0; k < n; k++)
        {
            // Поиск строки с максимальным a[i][k]
            int index = k;

            for (int i = k + 1; i < n; i++)
                if (abs(a[i][k]) > abs(a[index][k]))
                    index = i;
            #pragma omp barrier
            temp = b[k], b[k] = b[index], b[index] = temp;
            #pragma omp for
            for (int j = 0; j < n; j++)
                temp = a[k][j], a[k][j] = a[index][j], a[index][j] = temp;

            // Нормализация уравнений (1 по главной диагонали)
            #pragma omp for
            for (int i = k; i < n; i++)
            {
                if (abs(a[i][k]) < eps)
                    continue; // для нулевого коэффициента пропустить

                b[i] /= a[i][k];
                for (int j = n - 1; j >= k; j--)
                    a[i][j] /= a[i][k];

                if (i == k)
                    continue; // уравнение не вычитать само из себя

                b[i] -= b[k];
                for (int j = 0; j < n; j++)
                    a[i][j] -= a[k][j];
            }
        }

        //  получение решения
        #pragma omp for
        for (int k = n - 1; k >= 0; k--) // обратная подстановка
        {
            x[k] = b[k];
            for (int i = 0; i < k; i++)
                b[i] -= a[i][k] * x[k];
        }
    return x;
}

double round(double x) { return (x - (int)x) < eps ? (int)x : x; }

void print_start_file(double** a, double* b, int n, ofstream& out) {
    out << "System:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            out << setw(8) << a[i][j];
        out << " |" << setw(9) << b[i] << endl;
    }
}

void print_end_file(double* x, int n, ofstream& out) {
    if (x)
    {
        out << "Roots:\n";

        for (int i = 0; i < n; i++)
            out << setw(8) << round(x[i]); // чтобы выводило 0

        out << "\nFinished.";
    }
    else
        out << "Impossible to find exact system solution.";
}

int main()
{
    double start_time, end_time;

    ifstream in("slau.txt"); //  файл с матрицей
    ofstream out_0("out_0.txt"); //  файл с ответом (в виде из задания)
    ofstream out_1("out_1.txt"); //  файл с ответом (в виде из задания)
    double **a, *b, *x_0, *x_1;
    int n;
    char c;

    in >> n;
    a = new double *[n];
    b = new double[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; j++)
            in >> a[i][j];
        in >> c >> b[i];
    }

    print_start_file(a, b, n, out_0);
    print_start_file(a, b, n, out_1);

    start_time = omp_get_wtime();
    x_0 = gauss(a, b, n, 0); // решение
    end_time = omp_get_wtime();
    cout << "Время работы последовательного алгоритма:" << (end_time-start_time) * 1'000'000 << endl;

    start_time = omp_get_wtime();
    x_1 = gauss(a, b, n, 4); // решение
    end_time = omp_get_wtime();
    cout << "Время работы параллельного алгоритма:" << (end_time-start_time) * 1'000'000 << endl;

    print_end_file(x_0, n, out_0);
    print_end_file(x_1, n, out_1);

    in.close();
    out_0.close();
    out_1.close();

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    delete[] b;
    delete[] x_0;
    delete[] x_1;

    return 0;
}
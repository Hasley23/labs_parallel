#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

#define eps 0.00001

double *gauss(double **a, double *b, int n, int num_threads_) // метод Гаусса, возвращает массив решений X
{
    double temp, *x = new double[n];
    #pragma omp parallel if(num_threads_ > 0) num_threads(num_threads_)
    {
    //  приведение матрицы для получения решения
        for (int k = 0; k < n; k++)
        {
            // Поиск строки с максимальным a[i][k]
            int index = k;

            for (int i = k + 1; i < n; i++)
                if (abs(a[i][k]) > abs(a[index][k]))
                    index = i;

            if (abs(a[index][k]) < eps)
            {
                cout << "Решение получить невозможно из-за нулевого столбца " << index << " матрицы A." << endl;
            }

            // Здесь можно распараллелить
            temp = b[k], b[k] = b[index], b[index] = temp;
            for (int j = 0; j < n; j++)
                temp = a[k][j], a[k][j] = a[index][j], a[index][j] = temp;

            // Нормализация уравнений (1 по главной диагонали)
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

        // Здесь можно распараллелить
        //  получение решения
        for (int k = n - 1; k >= 0; k--) // обратная подстановка
        {
            x[k] = b[k];
            for (int i = 0; i < k; i++)
                b[i] -= a[i][k] * x[k];
        }
    }
    return x;
}

int main()
{
    ifstream in("slau.txt"); //  файл с матрицей
    ofstream out("out.txt"); //  файл с ответом (в виде из задания)
    double **a, *b, *x;
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

    out << "Numerical mathematics\nGauss method for systems of linear equations.\nSystem:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            out << setw(8) << a[i][j];
        out << " |" << setw(9) << b[i] << endl;
    }

    x = gauss(a, b, n, 0); // решение

    if (x)
    {
        out << "Roots:\n";

        for (int i = 0; i < n; i++)
            out << setw(8) << (x[i] - (int)x[i] < eps ? (int)x[i] : x[i]); // чтобы выводило 0

        out << "\nFinished.";
    }
    else
        out << "Impossible to find exact system solution.";

    in.close();
    out.close();

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    delete[] b;
    delete[] x;

    return 0;
}

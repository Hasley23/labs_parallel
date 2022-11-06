#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <omp.h>

using namespace std;

#define eps 0.00001 // эпсилон точности
#define BUFFER_SIZE 1000

int threads = 1;

double *gauss(double **a, double *b, int n, int num_threads_) // метод Гаусса, возвращает массив решений X
{
    double temp, *x = new double[n];
    double start_time = omp_get_wtime();
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

        //  получение решения
        for (int k = n - 1; k >= 0; k--) // обратная подстановка
        {
            x[k] = b[k];
            for (int i = 0; i < k; i++)
                b[i] -= a[i][k] * x[k];
        }
    }
    double end_time = omp_get_wtime();
    cout << "Время решения на " << threads << " потоках: " << (end_time - start_time) * 1'000'000 << " мкс" << endl;
    return x;
}

int main()
{
    // определение входного потока
    cout << "0 - slau0 - 3 | 1 - slau1 - 4 | 2 - slau2 - 6" << endl;
    int choice;
    cin >> choice;
    string filename = "";
    if (choice == 0)
        filename = "slau0.txt";
    else if (choice == 1)
        filename = "slau1.txt";
    else if (choice == 2)
        filename = "slau2.txt";
    ifstream in(filename); //  файл с матрицей
    
    // определение выходного потока
    ofstream out("out.txt"); //  файл с ответом (форматированный)
    double **a, *b, *x;
    int n;
    char c;

    in >> n;
    a = new double *[n];
    b = new double[n];

    cout << endl << "Ожидаю ввода числа потоков: ";
    cin >> threads;

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

    x = gauss(a, b, n, threads); // решение

    if (x)
    {
        out << "Roots:\n";

        for (int i = 0; i < n; i++)
            out << setw(8) << (x[i] - (int)x[i] < eps ? (int)x[i] : x[i]); // чтобы выводило 0

        out << "\nFinished.\n";
    }
    else
        out << "Impossible to find exact system solution.";

    cout << "Решение в директории программы, out.txt" << endl << endl << "out.txt:" << endl;
    in.close();
    out.close();
    
    FILE *fp;
    char buffer[BUFFER_SIZE];

    fp = popen("cat out.txt", "r");
    if (fp != NULL)
    {
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
            printf("%s", buffer);
        pclose(fp);
    }

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    delete[] b;
    delete[] x;

    return 0;
}

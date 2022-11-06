#include <cstdlib>
#include <vector>
#include <omp.h>
#include <random>
#include <iostream>
#include <iomanip>

#define EPS 0.00000001

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1, 20);

using namespace std;

void composition(vector<double> &i, vector<double> &j, double k)
{
    if (i.size() != j.size())
        throw "Ошибка! Несоответсивие размеров двух векторов!";

    for (int d = 0; d < i.size(); ++d)
        i[d] += j[d] * k;
}

void divStr(vector<double> &d, double k)
{
    if (abs(k) < EPS)
        throw "Ошибка! На 0 делить нельзя!";

    for (int i = 0; i < d.size(); ++i)
    {
        d[i] /= k;
    }
}

vector<vector<double>> triangulation(vector<vector<double>> &a, int _num_threads)
{
    int size = a.size();
    for (int k = 0; k < size; ++k)
    {
        if (abs(a[k][k]) < EPS)
        {
            for (int i = k + 1; i < size; ++i)
            {
                if (a[i][k] > EPS)
                {
                    swap(a[i], a[k]);
                    break;
                }
            }
        }

        if (a[k][k] < 1 - EPS || a[k][k] > 1 + EPS)
        {
            divStr(a[k], a[k][k]);
        }

        #pragma omp parallel for num_threads(_num_threads) schedule(dynamic)
        for (int i = k + 1; i < size; ++i)
        {
            composition(a[i], a[k], -a[i][k]);
        }
    }

    return a;
}

vector<double> gauss_solving(vector<vector<double>> &matrix,
                                vector<double> &free_term_column, int _num_threads)
{
    int size = matrix.size();
    vector<double> solution(size);
    for (int i = 0; i < size; ++i)
    {
        matrix[i].push_back(free_term_column[i]);
    }
    triangulation(matrix, _num_threads);
    for (int i = size - 1; i >= 0; --i)
    {
        if (abs(matrix[i][i]) < EPS)
            throw "Нет решения!";
        for (int j = i + 1; j < size; ++j)
            matrix[i][size] -= matrix[i][j] * solution[j];
        solution[i] = matrix[i][size] / matrix[i][i];
    }
    return solution;
}

int main(int argc, char **argv)
{
    double start_time, end_time;
    int size = 500;
    vector<vector<double>> a(size);
    vector<double> x;
    vector<double> b;
    for (int i = 0; i < size; ++i)
    {
        x.push_back(dist(gen));
        for (int j = 0; j < size; ++j)
        {
            a[i].push_back(double(dist(gen)));
        }
    }
    for (int i = 0; i < size; ++i)
    {
        int temp_b = 0;
        for (int j = 0; j < size; ++j)
        {
            temp_b += a[i][j] * x[j];
        }
        b.push_back(temp_b);
    }
    vector<vector<double>> a_2(a);
    vector<double> x_2(x);
    vector<double> b_2(b);

    start_time = omp_get_wtime();
    vector<double> solution;
    try
    {
        solution = gauss_solving(a, b, 1);
    }
    catch (char const *err)
    {
        cout << err << endl;
        return 1;
    }
    end_time = omp_get_wtime();
    bool correct = true;
    for(int i = 0; i < size; ++i)
        correct *= abs(x[i] - solution[i]) < EPS;
    // for(int i = 0; i < size; ++i)
    //     cout << x[i] << " " << solution[i] << endl;

    cout << fixed << "Последовательно: " << correct << " " << (end_time-start_time) * 1'000 << " мкс" << endl;

    start_time = omp_get_wtime();
    try
    {
        solution = gauss_solving(a_2, b_2, 12);
    }
    catch (char const *err)
    {
        cout << err << endl;
        return 1;
    }
    end_time = omp_get_wtime();
    correct = true;
    for(int i = 0; i < size; ++i)
        correct *= abs(x_2[i] - solution[i]) < EPS;
    // for(int i = 0; i < size; ++i)
    //     cout << x[i] << " " << solution[i] << endl;

    cout << fixed << "Параллельно:     " << correct << " " << (end_time-start_time) * 1'000 << " мкс" << endl;

    // for (int i = 0; i < size; ++i)
    // {
    //     for (int j = 0; j < size + 1; ++j)
    //         cout << a[i][j] << " ";
    //         // ( abs(a[i][j]) < EPS ? "0" : "1" ) << " ";

    //     cout << endl;
    // }

    return 0;
}
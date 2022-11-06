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

// typedef vector<double> Array;
// typedef vector<Array>  Matrix;

using Array  = vector<double>;
using Matrix = vector<Array>;


bool isZero(double x) { return abs(x) < EPS; }

bool checkSolution(Array x, Array s) {
    bool result = true;
    for(int i = 0; i < x.size(); ++i)
        result *= isZero(x[i] - s[i]);
    return result;
}

Array generateArray(int size) {
    Array result;
    for (int i = 0; i < size; ++i)
        result.push_back(dist(gen));
    return result;
}

Matrix generateMatrix(int size) {
    Matrix result(size);
    for (int i = 0; i < size; ++i)
        result[i] = generateArray(size);
    return result;
}

double calcSum(Array coefficient, Array x) {
    double result = 0;
    for (int i = 0; i < x.size(); ++i)
        result += coefficient[i] * x[i];
    return result;
}



void composition(Array &i, Array &j, double k) {
    if (i.size() != j.size())
        throw "Ошибка! Несоответствие размеров двух векторов!";

    for (int d = 0; d < i.size(); ++d)
        i[d] += j[d] * k;
}

void divStr(Array &d, double k) {
    if (abs(k) < EPS)
        throw "Ошибка! На 0 делить нельзя!";

    for (int i = 0; i < d.size(); ++i)
        d[i] /= k;
}

Matrix triangulation(Matrix &a, int _num_threads) {
    int size = a.size();

    for (int k = 0; k < size; ++k)
    {
        if (abs(a[k][k]) < EPS)
            for (int i = k + 1; i < size; ++i)
                if (a[i][k] > EPS)
                {
                    swap(a[i], a[k]);
                    break;
                }

        if (a[k][k] < 1 - EPS || a[k][k] > 1 + EPS)
            divStr(a[k], a[k][k]);

        #pragma omp parallel for num_threads(_num_threads) schedule(dynamic)
        for (int i = k + 1; i < size; ++i)
            composition(a[i], a[k], -a[i][k]);
    }

    return a;
}

Array gauss_solving(Matrix &a, Array &b, int _num_threads) {
    Matrix matrix(a);

    int size = matrix.size();

    Array solution(size);

    for (int i = 0; i < size; ++i)
        matrix[i].push_back(b[i]);

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

void printArray(Array x, string s) {
    cout << defaultfloat << s << " ";
    for(int i = 0; i < x.size(); ++i)
        cout << x[i] << " ";
    cout << endl;
}

int main() {
    double start_time, end_time;
    int size = 100;

    Array x = generateArray(size);

    Matrix a = generateMatrix(size);

    Array b;
    for (int i = 0; i < size; ++i)
        b.push_back(calcSum(a[i], x));

    Array solution;
    start_time = omp_get_wtime();
    try {
        solution = gauss_solving(a, b, 1);
    }
    catch (char const *err) {
        cout << err << endl;
        return 1;
    }
    end_time = omp_get_wtime();

    bool correct = checkSolution(x, solution);

    cout << fixed << "Последовательно: " << correct << " " << (end_time-start_time) * 1'000 << " мкс" << endl;

    Array solution_2;
    start_time = omp_get_wtime();
    try {
        solution_2 = gauss_solving(a, b, 6);
    }
    catch (char const *err) {
        cout << err << endl;
        return 1;
    }
    end_time = omp_get_wtime();

    bool correct_2 = checkSolution(x, solution_2);

    cout << fixed << "Параллельно:     " << correct_2 << " " << (end_time-start_time) * 1'000 << " мкс" << endl;


    printArray(x,          "Корни:                  ");
    printArray(solution,   "Решение последовательно:");
    printArray(solution_2, "Решение параллельно:    ");

    return 0;
}

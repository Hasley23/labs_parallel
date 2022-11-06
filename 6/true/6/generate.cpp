#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#define EPS 0.00000001

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(-20, 20);

using Array  = vector<double>;
using Matrix = vector<Array>;

// Заполняем случайными числами массив (вектор)
Array generateArray(int size) {
    Array result;
    for (int i = 0; i < size; ++i)
        result.push_back(dist(gen));
    return result;
}

// Заполняем случайными числами матрицу
Matrix generateMatrix(int size) {
    Matrix result(size);
    for (int i = 0; i < size; ++i)
        result[i] = generateArray(size);
    return result;
}

// Считаем свободный член СЛАУ (сумма произведений соответствующих элементов двух векторов)
double calcSum(Array x, Array y) {
    double result = 0;
    for (int i = 0; i < x.size(); ++i)
        result += x[i] * y[i];
    return result;
}

// Считаем все свободные члены СЛАУ
Array calcFreeColumn(Matrix a, Array x) {
    Array result;
    for (int i = 0; i < x.size(); ++i)
        result.push_back(calcSum(a[i], x));
    return result;
}

// Выводим в файл массив
void printArray(ofstream &out, Array x) {
    for(int i = 0; i < x.size(); ++i)
        out << setw(8) << x[i];
}

// Выводим в файл параметры СЛАУ (коэффициенты и свободные члены)
void printSLAU(ofstream &out, Matrix a, Array b) {
    for (int i = 0; i < b.size(); i++)
    {
        printArray(out, a[i]);
        out << " |" << setw(9) << b[i] << endl;
    }
}

// Генерируем задачу СЛАУ и выводим в файл условие и ответ
void generateSLAU(int size) {
    Array x = generateArray(size);
    Matrix a = generateMatrix(size);
    Array b = calcFreeColumn(a, x);

    string size_str = to_string(size);

    ofstream task("slau_" + size_str + ".txt");
    task << size << endl;
    printSLAU(task, a, b);

    ofstream solution("solution_" + size_str + ".txt");
    solution << "Numerical mathematics\nGauss method for systems of linear equations.\nSystem:\n";
    printSLAU(solution, a, b);
    solution << "Roots:" << endl;
    printArray(solution, x);
    solution << endl << "Finished.";
}

int main() {
    int size;

    cout << "Введите размер СЛАУ:\t";
    cin >> size;

    generateSLAU(size);

    return 0;
}
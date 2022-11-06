#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <omp.h>

#define EPS 0.00000001

using namespace std;

using Array  = vector<double>;
using Matrix = vector<Array>;

bool isZero(double x) { return abs(x) < EPS; }
bool isInt(double x) { return isZero(x - int(x)); }
double round(double x) { return isInt(x) ? (int)x : x; }

class Gauss {
    int size;
    Matrix slau;
    Array roots;

    int threads = 0;

    double time_start = 0;
    double time_end = 0;


    // Прибавляем к строке другую строку, домноженную на число
    void composition(Array &x, Array &y, double k) {
        for (int i = 0; i < x.size(); ++i)
            x[i] += y[i] * k;
    }

    // Деление всех элементов строки на число
    void divStr(Array &d, double k) {
        if (isZero(k))
            throw "Ошибка! На 0 делить нельзя!";

        for (int i = 0; i < d.size(); ++i)
            d[i] /= k;
    }

    // Приведение матрицы к треугольному виду (на главной диагонали 1, а ниже 0)
    void triangulation() {
        for (int k = 0; k < size; ++k) {
            // Если диагональный элемент строки 0, меняем строку с нижестоящей, где у данного элемента не 0
            if (isZero(slau[k][k]))
                for (int i = k + 1; i < size; ++i)
                    if (slau[i][k] > EPS) {
                        swap(slau[i], slau[k]);
                        break;
                    }

            // Если диагональный элемент строки не 1, делим всю строку на этот элемент
            if (!isZero(slau[k][k] - 1))
                divStr(slau[k], slau[k][k]);

            // Обнуляем нижестоящие в данном столбце элементы (вычитанием текущей строки)
            #pragma omp parallel for if(threads) num_threads(threads) schedule(dynamic)
            for (int i = k + 1; i < size; ++i)
                composition(slau[i], slau[k], -slau[i][k]);
        }
    }

    // Обратный ход метода Гаусса (находим корни)
    Array calcRoots() {
        Array solution(size);

        for (int i = size - 1; i >= 0; --i) {
            if (isZero(slau[i][i]))
                throw "Нет решения!";

            double sum = 0;
            #pragma omp parallel for if(threads) num_threads(threads) reduction(+: sum)
            for (int j = i + 1; j < size; ++j)
                sum += slau[i][j] * solution[j];
            solution[i] = slau[i][size] - sum;
        }

        return solution;
    }

    public:
        Gauss(Matrix &m, int t=1): slau(m), threads(t), size(m.size()) { }

        // Решаем задачу СЛАУ методом Гаусса и засекаем затраченное на решение время
        void solve() {
            try {
                time_start = omp_get_wtime();
                triangulation();
                roots = calcRoots();
                time_end = omp_get_wtime();
            }
            catch (char const *err) {
                cout << err << endl;
            }
        }

        // Выводим время, затраченное на решение задачи
        void printTime() {
            string s = threads > 1 ? "Параллельно:     " : "Последовательно: ";
            cout << fixed << s << (time_end-time_start) * 1'000 << " мкс" << endl << defaultfloat;
        }

        // Выводим на экран полученные корни
        void printRoots() {
            string s = threads > 1 ?  "параллельного" : "последовательного";
            cout <<  "Корни " << s << " решения:" << endl;
            for(int i = 0; i < size; ++i)
                cout << setw(8) << round(roots[i]);
            cout << endl;
        }
};

// Чтение задачи из файла
Matrix readSLAU(string fname) {
    char c;

    //  Файл с матрицей
    ifstream in(fname);

    int size;
    in >> size;

    Matrix result(size);

    for (int i = 0; i < size; ++i) {
        result[i].resize(size + 1);
        for (int j = 0; j < size; ++j)
            in >> result[i][j];
        in >> c >> result[i][size];
    }
    return result;
}

int main(int argc, char *argv[]) {
    string inFileName;
    // cout << argc << " " << argv[1] << endl;
    if(argc > 1)
        inFileName = argv[1];
    else {
        cout << "Введите название файла с условием: ";
        cin >> inFileName;
    }

    Matrix slau = readSLAU(inFileName);

    Gauss serial(slau, 1);
    serial.solve();
    serial.printTime();

    Gauss parallel(slau, 4);
    parallel.solve();
    parallel.printTime();

    serial.printRoots();
    parallel.printRoots();

    return 0;
}
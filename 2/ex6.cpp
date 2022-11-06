#include <stdio.h>
#include <omp.h>

int main() {
    // Пример 6 демонстрирует применение функций omp_set_dynamic() и omp_get_dynamic(). (динамическое изменение нитей)
    printf("Значение OMP_DYNAMIC: %d\n", omp_get_dynamic());
    #pragma omp parallel num_threads(128)
    #pragma omp master
        printf("Параллельная область, %d нитей\n", omp_get_num_threads());

    omp_set_dynamic(1);
    printf("Значение OMP_DYNAMIC: %d\n", omp_get_dynamic());
    #pragma omp parallel num_threads(128)
    #pragma omp master
        printf("Параллельная область, %d нитей\n", omp_get_num_threads());
}

#include <stdio.h>
#include <omp.h>

void mode() {
    if(omp_in_parallel())
        printf("Параллельная область\n");
    else
        printf("Последовательная область\n");
}

int main() {
    // Пример 8 иллюстрирует применение функции omp_in_parallel().
    mode();
    #pragma omp parallel
    // используем нить master для предотвращения множественного вывода
    #pragma omp master
        mode();
}
